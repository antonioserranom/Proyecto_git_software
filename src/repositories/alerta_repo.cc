#include "alerta_repo.h"

static int callback_alerta(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Alerta>*>(listaPtr);
    int id = std::stoi(argv[0]);
    Alerta a(
        id, 
        argv[1] ? argv[1] : "", 
        argv[2] ? argv[2] : "",
        argv[3] ? argv[3] : "",
        argv[4] ? argv[4] : "",
        argv[5] ? argv[5] : ""
    );
    lista->push_back(a);
    return 0;
}

Alerta AlertaRepository::buscarPorId(std::string id){
    std::vector<Alerta> listaResultado;
    std::string sql = "SELECT * FROM ALERTA WHERE id = " + id + ";";

    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_alerta, &listaResultado);

    if(listaResultado.empty()){
        return Alerta(0, "", "", "", "", "");
    }
    return listaResultado[0];
}

std::vector<Alerta> AlertaRepository::obtenerTodas() {
    std::vector<Alerta> listaResultado;
    std::string sql = "SELECT * FROM ALERTA;";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_alerta, &listaResultado);
    return listaResultado;
}

std::vector<Alerta> AlertaRepository::obtenerPorEstudiante(std::string idEstudiante) {
    std::vector<Alerta> listaResultado;
    std::string sql = "SELECT * FROM ALERTA WHERE id_estudiante = '" + idEstudiante + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_alerta, &listaResultado);
    return listaResultado;
}

bool AlertaRepository::guardar(Alerta a) {
    std::string sql = "INSERT INTO ALERTA (id_estudiante, motivo, Estado, Comentarios) VALUES ('" + 
                      a.GetIdEstudiante() + "', '" + 
                      a.GetMotivo() + "', '" + 
                      a.GetEstado() + "', '" + 
                      a.GetComentarios() + "');";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool AlertaRepository::actualizarEstado(std::string id, std::string nuevoEstado, std::string comentarios) {
    std::string sql = "UPDATE ALERTA SET Estado = '" + nuevoEstado + "', Comentarios = '" + comentarios + "' WHERE id = " + id + ";";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}