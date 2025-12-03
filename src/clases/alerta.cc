/**
 * @file alerta.cc
 * @brief Contiene la implementacion de la clase alerta.
 * @author Adrian Sanchez Prieto
 * @date 25/11/25
 */
#include "alerta.h"

alerta::alerta(const Estudiante& estudiante, const std::string& motivo){
	estudiante_=estudiante;
	Motivo_=motivo;
	Estado_="Pendiente";
	Comentarios_="";
	Fecha_=std::time(nullptr);
	}

void alerta::SetMotivo(const std::string& motivo){
	Motivo_=motivo;
}

void alerta::SetEstado(const std::string& estado){
	if (estado == "Pendiente" || estado == "En seguimiento" || estado == "Resuelta") {
	        Estado_ = estado;
	    } else {
	        Estado_ = "Pendiente";
	    }
}

void alerta::SetComentarios(const std::string& comentarios){
	Comentarios_=comentarios;
}

void alerta::SetFecha(const std::time_t fecha){
	Fecha_=fecha;
}



