#include "basedatos.h"
#include <iostream>

BaseDatos* BaseDatos::instancia_ = nullptr;

BaseDatos::BaseDatos() {
    db_ = nullptr;
}

BaseDatos::~BaseDatos() {
    cerrarConexion();
}

BaseDatos* BaseDatos::getInstancia() {
    if (instancia_ == nullptr) {
        instancia_ = new BaseDatos();
    }
    return instancia_;
}

bool BaseDatos::abrirConexion() {
    if (db_ != nullptr) return true;

    int resultado = sqlite3_open("../data/sitapi.db", &db_);
    
    if (resultado != SQLITE_OK) {
        return false;
    }
    
    return true;
}

void BaseDatos::cerrarConexion() {
    if (db_ != nullptr) {
        sqlite3_close(db_);
        db_ = nullptr;
    }
}

sqlite3* BaseDatos::getDB() const {
    return db_;
}

bool BaseDatos::ejecutarSQL(std::string sql, int (*callback)(void*, int, char**, char**), void* data){
    char* errorMsg = nullptr;
    int resultado = sqlite3_exec(db_, sql.c_str(), callback, data, &errorMsg);

    if (resultado != SQLITE_OK) {
        sqlite3_free(errorMsg);
        return false;
    }
    return true;
}