#include "alarm.h"

alarma::alarma(const Estudiante& estudiante, const std::string& motivo){
	estudiante_=estudiante;
	Motivo_=motivo;
	Estado_="Pendiente";
	Comentarios_="";
	Fecha_=std::time(nullptr);
	}

void alarma::SetMotivo(const std::string& motivo){
	Motivo_=motivo;
}

void alarma::SetEstado(const std::string& estado){
	if (estado == "Pendiente" || estado == "En seguimiento" || estado == "Resuelta") {
	        Estado_ = estado;
	    } else {
	        Estado_ = "Pendiente";
	    }
}

void alarma::SetComentarios(const std::string& comentarios){
	Comentarios_=comentarios;
}

void alarma::SetFecha(const std::time_t fecha){
	Fecha_=fecha;
}



