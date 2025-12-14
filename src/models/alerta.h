/**
 * @file alerta.h
 * @brief Contiene la definicion de la clase alerta.
 * @author Adrian Sanchez Prieto
 * @date 25/11/25
 */
#ifndef ALERTA_H
#define ALERTA_H

#include <string>
#include <ctime>

class Alerta{

private:
	int id_;
	std::string id_estudiante_, motivo_, fecha_, estado_, comentarios_;

	public:
	
	Alerta(int id, std::string idEstudiante, std::string motivo, 
               std::string fecha, std::string estado, std::string comentarios);
	int GetId()const{return id_;}
	std::string GetIdEstudiante(){return id_estudiante_;}
	std::string GetMotivo()const{return motivo_;}
	std::string GetFecha()const{return fecha_;}
	std::string GetEstado()const{return estado_;}
	std::string GetComentarios()const{return comentarios_;}
	void SetEstado(const std::string& estado);
	void SetComentarios(const std::string& comentarios);
	void SetFecha(const std::string& fecha);
	
};

#endif
