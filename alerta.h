#ifndef ALARM_H
#define ALARM_H

#include <ctime>

#include "usuario.h"

class alarma{

private:
	Estudiante estudiante_;
	std::string Motivo_;
	std::time_t Fecha_;
	std::string Estado_;
	std::string Comentarios_;
	void SetMotivo(const std::string& motivo);
	void SetFecha(std::time_t fecha);
	void SetEstado(const std::string& estado);
	void SetComentarios(const std::string& comentarios);

public:
		alarma(const Estudiante& estudiante, const std::string& motivo);
		std::string GetMotivo()const{return Motivo_;}
	    std::time_t GetFecha()const{return Fecha_;}
	    std::string GetEstado()const{return Estado_;}
	    std::string GetComentarios()const{return Comentarios_;}
	    friend class Tutor;
	    friend class Coordinador;

};

#endif
