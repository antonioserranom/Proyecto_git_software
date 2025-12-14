#include "asignacion_repo.h"

static int callback_asignacion(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Asignacion>*>(listaPtr);
    int id = std::stoi(argv[0]);
    Asignacion a(
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

std::vector<Asignacion> AsignacionRepository::obtenerTodas() {
    std::vector<Asignacion> listaResultado;
    std::string sql = "SELECT * FROM ASIGNACIONES;"; 
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_asignacion, &listaResultado);
    return listaResultado;
}

std::vector<Asignacion> AsignacionRepository::obtenerPorEstudiante(std::string idEstudiante) {
    std::vector<Asignacion> listaResultado;
    std::string sql = "SELECT * FROM ASIGNACIONES WHERE estudiante_id = '" + idEstudiante + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_asignacion, &listaResultado);
    return listaResultado;
}

bool AsignacionRepository::guardar(Asignacion a) {
    std::string sql = "INSERT INTO ASIGNACIONES (estudiante_id, tutor_id, criterios, modificaciones) VALUES ('" + 
                      a.GetIdEstudiante() + "', '" + 
                      a.GetIdTutor() + "', '" + 
                      a.GetCriterios() + "', '" + 
                      a.GetModificaciones() + "');";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}