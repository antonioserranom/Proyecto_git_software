/**
 * @file alerta.cc
 * @brief Contiene la implementacion de la clase alerta.
 * @author Adrian Sanchez Prieto
 * @date 25/11/25
 */
#include "alerta.h"

Alerta::Alerta(int id, std::string idEstudiante, std::string motivo, 
               std::string fecha, std::string estado, std::string comentarios){
    id_ = id;
    id_estudiante_ = idEstudiante;
    motivo_ = motivo;
    estado_ = estado;
    comentarios_ = comentarios;

    if (fecha.empty()) {
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        fecha_ = buf;
    } else {
        fecha_ = fecha;
    }
}
void Alerta::SetEstado(const std::string& estado){
	if (estado == "Pendiente" || estado == "En seguimiento" || estado == "Resuelta") {
	        estado_ = estado;
	    } else {
	        estado_ = "Pendiente";
	    }
}

void Alerta::SetComentarios(const std::string& comentarios){
	comentarios_=comentarios;
}

void Alerta::SetFecha(const std::string& fecha){
	fecha_=fecha;
}



