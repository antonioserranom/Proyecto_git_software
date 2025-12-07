/**
 * @file alerta.h
 * @brief Contiene la definicion de la clase alerta.
 * @author Adrian Sanchez Prieto
 * @date 25/11/25
 */
#ifndef ALERTA_H
#define ALERTA_H

#include "usuario.h"

class alerta{

private:
	Estudiante estudiante_;
	std::string motivo_;
	std::time_t fecha_;
	std::string estado_;
	std::string comentarios_;
	void SetMotivo(const std::string& motivo);
	void SetFecha(std::time_t fecha);
	void SetEstado(const std::string& estado);
	void SetComentarios(const std::string& comentarios);

public:
		alerta(const Estudiante& estudiante, const std::string& motivo);
		std::string GetMotivo()const{return motivo_;}
	    std::time_t GetFecha()const{return fecha_;}
	    std::string GetEstado()const{return estado_;}
	    std::string GetComentarios()const{return comentarios_;}
	    friend class Tutor;
	    friend class Coordinador;

};

#endif
