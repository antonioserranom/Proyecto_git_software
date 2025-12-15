#include "tutor_repo.h"

static int callback_tutor(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Tutor>*>(listaPtr);
    Tutor t(
        argv[0] ? argv[0] : "",
        argv[1] ? argv[1] : "",
        argv[2] ? argv[2] : "",
        argv[3] ? argv[3] : "",
        argv[4] ? argv[4] : "",
        argv[5] ? argv[5] : ""
    );
    lista->push_back(t);
    return 0;
}

std::vector<Tutor> TutorRepository::obtenerTodos() {
    std::vector<Tutor> listaResultado;
    std::string sql = "SELECT * FROM Tutor;";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_tutor, &listaResultado);
    return listaResultado;
}

std::optional<Tutor> TutorRepository::buscarPorId(std::string id) {
    std::vector<Tutor> listaResultado;
    std::string sql = "SELECT * FROM Tutor WHERE id = '" + id + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_tutor, &listaResultado);
    
    if (listaResultado.empty()) {
        return std::nullopt;
    }
    return listaResultado[0];
}

bool TutorRepository::guardar(Tutor t) {
    std::string sql = "INSERT INTO Tutor (id, nombre, email, horario, area_conocimiento, facultad) VALUES ('" + 
                      t.GetId() + "', '" + 
                      t.GetNombre() + "', '" + 
                      t.GetEmail() + "', '" + 
                      t.GetHorario() + "', '" + 
                      t.GetAreaConocimiento() + "', '" + 
                      t.GetFacultad() + "');";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool TutorRepository::actualizar(Tutor t) {
    std::string sql = "UPDATE Tutor SET "
                      "nombre = '" + t.GetNombre() + "', "
                      "email = '" + t.GetEmail() + "', "
                      "horario = '" + t.GetHorario() + "', "
                      "area_conocimiento = '" + t.GetAreaConocimiento() + "', "
                      "facultad = '" + t.GetFacultad() + "' "
                      "WHERE id = '" + t.GetId() + "';";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool TutorRepository::eliminar(std::string id) {
    std::string sql = "DELETE FROM Tutor WHERE id = '" + id + "';";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}