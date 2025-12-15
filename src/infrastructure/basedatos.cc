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

bool BaseDatos::abrirConexion(std::string ruta) {
if (db_!= nullptr) return true;

    int resultado = sqlite3_open(ruta.c_str(), &db_);
    
    if (resultado == SQLITE_OK) {
        ejecutarSQL("PRAGMA foreign_keys = ON;");
        return true;
    } else {
        std::cerr << "Error al abrir DB: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }
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

bool BaseDatos::inicializarEsquema(){
    std::string sql = R"(
        BEGIN TRANSACTION;

        CREATE TABLE IF NOT EXISTS TUTOR (
            id VARCHAR(9) PRIMARY KEY,
            nombre VARCHAR(100) NOT NULL,
            email VARCHAR(100) NOT NULL,
            horario VARCHAR(50),
            area_conocimiento VARCHAR(100),
            facultad VARCHAR(100)
        );

        CREATE TABLE IF NOT EXISTS ESTUDIANTE (
            id VARCHAR(9) PRIMARY KEY,
            nombre VARCHAR(100),
            email VARCHAR(100),
            informacion_academica VARCHAR(255),
            alojamiento VARCHAR(100),
            progreso VARCHAR(50),
            id_tutor VARCHAR(9),
            FOREIGN KEY (id_tutor) REFERENCES TUTOR(id)
        );

        CREATE TABLE IF NOT EXISTS COORDINADOR (
            id VARCHAR(9) PRIMARY KEY,
            nombre VARCHAR(100),
            email VARCHAR(100),
            facultad VARCHAR(100),
            responsabilidades VARCHAR(255)
        );

        CREATE TABLE IF NOT EXISTS ALERTA (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            id_estudiante VARCHAR(9) NOT NULL,
            motivo VARCHAR(255),
            fecha DATETIME DEFAULT CURRENT_TIMESTAMP,
            Estado VARCHAR(20) DEFAULT 'Pendiente',
            Comentarios VARCHAR(255),
            FOREIGN KEY (id_estudiante) REFERENCES ESTUDIANTE(id)
        );

        CREATE TABLE IF NOT EXISTS CHAT (
            id_chat INTEGER PRIMARY KEY AUTOINCREMENT,
            id_estudiante VARCHAR(9) NOT NULL,
            id_tutor VARCHAR(9) NOT NULL,
            fecha_creacion DATETIME DEFAULT CURRENT_TIMESTAMP,
            UNIQUE(id_estudiante, id_tutor),
            FOREIGN KEY (id_estudiante) REFERENCES ESTUDIANTE(id),
            FOREIGN KEY (id_tutor) REFERENCES TUTOR(id)
        );

        CREATE TABLE IF NOT EXISTS MENSAJE (
            id_mensaje INTEGER PRIMARY KEY AUTOINCREMENT,
            id_chat INTEGER NOT NULL,
            id_emisor VARCHAR(9) NOT NULL,
            contenido TEXT NOT NULL,
            fecha_envio DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (id_chat) REFERENCES CHAT(id_chat) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS ASIGNACIONES (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            estudiante_id VARCHAR(9) NOT NULL,
            tutor_id VARCHAR(9) NOT NULL,
            criterios TEXT,
            fecha_asignacion DATETIME DEFAULT CURRENT_TIMESTAMP,
            modificaciones TEXT,
            FOREIGN KEY (estudiante_id) REFERENCES ESTUDIANTE(id),
            FOREIGN KEY (tutor_id) REFERENCES TUTOR(id)
        );

        COMMIT;
    )";

    return ejecutarSQL(sql);
}

static int callback_count(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    *count = std::stoi(argv[0]);
    return 0;
}

bool BaseDatos::estaVacia() {
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM COORDINADOR;";
    ejecutarSQL(sql, callback_count, &count);
    return count == 0;
}

bool BaseDatos::importarDesdeArchivo(std::string rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo SQL: " << rutaArchivo << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string sqlCompleto = buffer.str();
    
    return ejecutarSQL(sqlCompleto);
}