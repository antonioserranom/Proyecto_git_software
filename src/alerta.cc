/**
 * @file alerta.cc
 * @brief Contiene la implementacion de la clase alerta.
 * @author Adrian Sanchez Prieto
 * @date 25/11/25
 */
#include "alerta.h"

alerta::alerta(const Estudiante& estudiante, const std::string& motivo){
	estudiante_=estudiante;
	motivo_=motivo;
	estado_="Pendiente";
	comentarios_="";
	fecha_=std::time(nullptr);
	}

void alerta::SetMotivo(const std::string& motivo){
	motivo_=motivo;
}

void alerta::SetEstado(const std::string& estado){
	if (estado == "Pendiente" || estado == "En seguimiento" || estado == "Resuelta") {
	        estado_ = estado;
	    } else {
	        estado_ = "Pendiente";
	    }
}

void alerta::SetComentarios(const std::string& comentarios){
	comentarios_=comentarios;
}

void alerta::SetFecha(const std::time_t fecha){
	fecha_=fecha;
}



