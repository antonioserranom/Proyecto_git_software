#ifndef BASEDATOS_H
#define BASEDATOS_H

#include <sqlite3.h>
#include <string>
#include <fstream>
#include <sstream>

class BaseDatos {
private:
    sqlite3* db_;
    static BaseDatos* instancia_;
    
    BaseDatos(); 

public:
    ~BaseDatos();
    static BaseDatos* getInstancia();
    bool abrirConexion(std::string ruta);
    void cerrarConexion();
    sqlite3* getDB() const;
    bool inicializarEsquema();
    bool estaVacia();
    bool importarDesdeArchivo(std::string rutaArchivo);
    bool ejecutarSQL(std::string sql, int (*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
};

#endif