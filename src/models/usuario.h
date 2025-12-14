/**
 * @file usuario.h
 * @brief Contiene la definición de la clase Usuario y derivadas.
 * @author Antonio Serrano Maldonado
 * @date 26/11/25
 */
#ifndef USER_H
#define USER_H


#include <string>
#include <list>
#include <ctime>

class Alerta;
class Mensaje;
class Asignacion;

class Usuario{
protected:
	std::string id_, nombre_, email_;

public:
	Usuario(const std::string& id, const std::string& nombre, const std::string& email);
	virtual ~Usuario() {}
	std::string GetId(){return id_;}
	std::string GetNombre(){return nombre_;}
	std::string GetEmail(){return email_;}
	bool SetId(const std::string& id);
	bool SetNombre(const std::string& nombre);
	bool SetEmail(const std::string& nombre);
};

class Estudiante : public Usuario{

private:
	std::string informacion_academica_, alojamiento_, progreso_, id_tutor_asignado_;

public:
	Estudiante(const std::string& id, const std::string& nombre, const std::string& email, const std::string& informacion_academica, const std::string& alojamiento, const std::string& progreso, const std::string& id_tutor);
	std::string GetInfo(){return informacion_academica_;}
	std::string GetAlojamiento(){return alojamiento_;}
	std::string GetIdTutor(){return id_tutor_asignado_;}
	std::string GetProgreso(){return progreso_;}

	bool SetInformacionAcademica(const std::string& informacion_academica);
	bool SetAlojamiento(const std::string& alojamiento);
	bool SetIdTutor(const std::string& id_tutor);
	bool SetProgreso(const std::string& progeso);

};

class Tutor : public Usuario{
private:
	std::string facultad_, horario_, area_conocimiento_;

public:
	Tutor(const std::string& id, const std::string& nombre, const std::string& email, const std::string& facultad, const std::string& horario, const std::string& area_conocimiento);
	std::string GetFacultad(){return facultad_;}
	std::string GetHorario(){return horario_;}
	std::string GetAreaConocimiento(){return area_conocimiento_;}
	bool SetFacultad(const std::string& facultad);
	bool SetHorario(const std::string& horario);
	bool SetAreaConocimiento(const std::string& area_conocimiento);


};

class Coordinador : public Usuario{
private:
	std::string facultad_, responsabilidades_;

public:
	Coordinador(const std::string& id, const std::string& nombre, const std::string& email, const std::string& facultad, const std::string& responsabilidades);
	std::string GetFacultad(){return facultad_;}
	std::string GetResponsabilidades(){return responsabilidades_;}
	bool SetFacultad(const std::string& facultad);
	bool SetResponsabilidades(const std::string& responsabilidades);
};

bool es_id_valido(const std::string& id);
#endif
