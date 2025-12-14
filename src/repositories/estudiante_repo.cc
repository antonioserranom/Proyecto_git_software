#include "estudiante_repo.h"

static int callback_estudiantes(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Estudiante>*>(listaPtr);
    
    Estudiante est(
        argv[0] ? argv[0] : "", 
        argv[1] ? argv[1] : "", 
        argv[2] ? argv[2] : "", 
        argv[3] ? argv[3] : "", 
        argv[4] ? argv[4] : "", 
        argv[5] ? argv[5] : "",
        argv[6] ? argv[6] : ""  
    );

    lista->push_back(est);
    return 0;
}

std::vector<Estudiante> EstudianteRepository::obtenerTodos() {
    std::vector<Estudiante> listaResultado;
    std::string sql = "SELECT * FROM Estudiante;";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_estudiantes, &listaResultado);
    return listaResultado;
}

std::optional<Estudiante> EstudianteRepository::buscarPorId(std::string id) {
    std::vector<Estudiante> listaResultado;
    std::string sql = "SELECT * FROM Estudiante WHERE id = '" + id + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_estudiantes, &listaResultado);
    
    if (listaResultado.empty()) {
        return std::nullopt;
    }
    return listaResultado[0];
}

bool EstudianteRepository::guardar(Estudiante est) {
    std::string tutorSql = est.GetIdTutor().empty() ? "NULL" : "'" + est.GetIdTutor() + "'";
    
    std::string sql = "INSERT INTO Estudiante (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES ('" + 
                      est.GetId() + "', '" + 
                      est.GetNombre() + "', '" + 
                      est.GetEmail() + "', '" + 
                      est.GetInfo() + "', '" + 
                      est.GetAlojamiento() + "', '" + 
                      est.GetProgreso() + "', " + 
                      tutorSql + ");";
    
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool EstudianteRepository::actualizar(Estudiante est) {
    std::string tutorSql = est.GetIdTutor().empty() ? "NULL" : "'" + est.GetIdTutor() + "'";
    
    std::string sql = "UPDATE Estudiante SET "
                      "nombre = '" + est.GetNombre() + "', "
                      "email = '" + est.GetEmail() + "', "
                      "informacion_academica = '" + est.GetInfo() + "', "
                      "alojamiento = '" + est.GetAlojamiento() + "', "
                      "progreso = '" + est.GetProgreso() + "', "
                      "id_tutor = " + tutorSql + " "
                      "WHERE id = '" + est.GetId() + "';";
                      
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool EstudianteRepository::eliminar(std::string id) {
    std::string sql = "DELETE FROM Estudiante WHERE id = '" + id + "';";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}