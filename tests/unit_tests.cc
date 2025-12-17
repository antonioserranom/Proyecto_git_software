#include <gtest/gtest.h>
#include <cstdio>
#include <string>
#include "../src/infrastructure/basedatos.h"
#include "../src/services/servicio_chat.h"
#include "../src/services/servicio_asignacion.h"
#include "../src/services/servicio_alerta.h"
#include "../src/models/usuario.h"

class SitapiTest : public ::testing::Test {
protected:
    void SetUp() override {
        BaseDatos::getInstancia()->abrirConexion("test_sitapi.db");
        BaseDatos::getInstancia()->inicializarEsquema();
    }

    void TearDown() override {
        BaseDatos::getInstancia()->cerrarConexion();
        std::remove("test_sitapi.db");
    }

   void InsertarTutor(std::string id, std::string area, int carga) {
        std::string sql = "INSERT INTO TUTOR (id, nombre, email, horario, area_conocimiento, facultad) VALUES ('" + 
                          id + "', 'Tutor " + id + "', 't@u.co', 'Mañana', '" + area + "', 'Facultad X');";
        
        bool exitoTutor = BaseDatos::getInstancia()->ejecutarSQL(sql);
        if (!exitoTutor) printf("FALLO AL INSERTAR TUTOR %s\n", id.c_str());

        for(int i=0; i<carga; i++) {
            std::string idEst = id + "_S" + std::to_string(i);
            std::string sqlSt = "INSERT INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) "
                                "VALUES ('" + idEst + "', 'EstCarga', 'e@test.com', 'Info', 'Aloj', 'Prog', '" + id + "');";
            BaseDatos::getInstancia()->ejecutarSQL(sqlSt);
        }

    }

    void InsertarEstudianteSinTutor(std::string id, std::string info) {
        std::string sql = "INSERT INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) "
                          "VALUES ('" + id + "', 'Est " + id + "', 'alumno@test.com', '" + info + "', 'Residencia', 'Adecuado', NULL);";
        
        bool exitoEst = BaseDatos::getInstancia()->ejecutarSQL(sql);
        if (!exitoEst) printf("FALLO AL INSERTAR ESTUDIANTE %s\n", id.c_str());
    }
};

TEST_F(SitapiTest, Chat_EnviarMensajeCorrectamente) {
    ChatService chatService;
    std::string sqlE = "INSERT INTO ESTUDIANTE (id) VALUES ('E01');";
    std::string sqlT = "INSERT INTO TUTOR (id) VALUES ('T01');";
    BaseDatos::getInstancia()->ejecutarSQL(sqlE);
    BaseDatos::getInstancia()->ejecutarSQL(sqlT);

    int idChat = chatService.IniciarChat("E01", "T01");
    bool enviado = chatService.EnviarMensaje(idChat, "E01", "Hola Tutor");

    EXPECT_TRUE(enviado);
    auto mensajes = chatService.LeerConversacion(idChat);
    ASSERT_EQ(mensajes.size(), 1);
    EXPECT_EQ(mensajes[0].GetContenido(), "Hola Tutor");
}

TEST_F(SitapiTest, Chat_RecuperarHistorial) {
    ChatService chatService;
    BaseDatos::getInstancia()->ejecutarSQL("INSERT INTO ESTUDIANTE (id) VALUES ('E01');");
    BaseDatos::getInstancia()->ejecutarSQL("INSERT INTO TUTOR (id) VALUES ('T01');");

    int idChat = chatService.IniciarChat("E01", "T01");
    chatService.EnviarMensaje(idChat, "E01", "Msg 1");
    chatService.EnviarMensaje(idChat, "T01", "Msg 2");

    auto historial = chatService.LeerConversacion(idChat);
    EXPECT_EQ(historial.size(), 2);
    EXPECT_EQ(historial[1].GetContenido(), "Msg 2");
}

TEST_F(SitapiTest, Asignacion_Automatica_PrioridadAfinidad) {
    AssignmentService asignacionService;
    
    InsertarTutor("T_IA", "Inteligencia Artificial", 0);
    InsertarTutor("T_RED", "Redes", 0);
    InsertarEstudianteSinTutor("E_IA", "Inteligencia Artificial");

    bool cambios = asignacionService.RealizarAsignacionAutomatica();

    EXPECT_TRUE(cambios);
    std::string idTutorAsignado = asignacionService.GetTutorDeEstudiante("E_IA");
    EXPECT_EQ(idTutorAsignado, "T_IA");
}

TEST_F(SitapiTest, Asignacion_Automatica_BalanceoCarga) {
    AssignmentService asignacionService;

    InsertarTutor("T_OCUPADO", "General", 5);
    InsertarTutor("T_LIBRE", "General", 0);
    InsertarEstudianteSinTutor("E_NUEVO", "General");

    bool cambios = asignacionService.RealizarAsignacionAutomatica();

    EXPECT_TRUE(cambios);
    std::string idTutorAsignado = asignacionService.GetTutorDeEstudiante("E_NUEVO");
    EXPECT_EQ(idTutorAsignado, "T_LIBRE");
}

TEST_F(SitapiTest, Alerta_GenerarNueva) {
    AlertService alertaService;
    BaseDatos::getInstancia()->ejecutarSQL("INSERT INTO ESTUDIANTE (id) VALUES ('E01');");

    bool resultado = alertaService.GenerarAlerta("E01", "Faltas de asistencia");
    
    EXPECT_TRUE(resultado);
    auto alertas = alertaService.ConsultarAlertasPorEstudiante("E01");
    ASSERT_FALSE(alertas.empty());
    EXPECT_EQ(alertas[0].GetMotivo(), "Faltas de asistencia");
}

TEST_F(SitapiTest, Alerta_ActualizarEstado) {
    AlertService alertaService;
    BaseDatos::getInstancia()->ejecutarSQL("INSERT INTO ESTUDIANTE (id) VALUES ('E01');");
    alertaService.GenerarAlerta("E01", "Problema X");
    
    auto alertas = alertaService.ConsultarAlertasPorEstudiante("E01");
    int idAlerta = alertas[0].GetId();

    bool actualizado = alertaService.ActualizarEstadoAlerta(idAlerta, "Resuelta", "Hablado con alumno");

    EXPECT_TRUE(actualizado);
    auto alertasActualizadas = alertaService.ConsultarAlertasPorEstudiante("E01");
    EXPECT_EQ(alertasActualizadas[0].GetEstado(), "Resuelta");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}