#include "coordinador_repo.h"

static int callback_coordinador(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Coordinador>*>(listaPtr);
    Coordinador c(
        argv[0] ? argv[0] : "",
        argv[1] ? argv[1] : "",
        argv[2] ? argv[2] : "",
        argv[3] ? argv[3] : "",
        argv[4] ? argv[4] : ""
    );
    lista->push_back(c);
    return 0;
}

std::vector<Coordinador> CoordinadorRepository::obtenerTodos() {
    std::vector<Coordinador> listaResultado;
    std::string sql = "SELECT * FROM Coordinador;";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_coordinador, &listaResultado);
    return listaResultado;
}

Coordinador CoordinadorRepository::buscarPorId(std::string id) {
    std::vector<Coordinador> listaResultado;
    std::string sql = "SELECT * FROM Coordinador WHERE id = '" + id + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_coordinador, &listaResultado);
    
    if (listaResultado.empty()) {
        return Coordinador("", "", "", "", "");
    }
    return listaResultado[0];
}

bool CoordinadorRepository::guardar(Coordinador c) {
    std::string sql = "INSERT INTO Coordinador (id, nombre, email, facultad, responsabilidades) VALUES ('" + 
                      c.GetId() + "', '" + 
                      c.GetNombre() + "', '" + 
                      c.GetEmail() + "', '" + 
                      c.GetFacultad() + "', '" + 
                      c.GetResponsabilidades() + "');";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool CoordinadorRepository::actualizar(Coordinador c) {
    std::string sql = "UPDATE Coordinador SET "
                      "nombre = '" + c.GetNombre() + "', "
                      "email = '" + c.GetEmail() + "', "
                      "facultad = '" + c.GetFacultad() + "', "
                      "responsabilidades = '" + c.GetResponsabilidades() + "' "
                      "WHERE id = '" + c.GetId() + "';";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

bool CoordinadorRepository::eliminar(std::string id) {
    std::string sql = "DELETE FROM Coordinador WHERE id = '" + id + "';";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}