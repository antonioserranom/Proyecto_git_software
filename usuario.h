#ifndef USER_H
#define USER_H

#include "alerta.h"
#include "mensaje.h"
#include "asignacion.h"
#include <string>
#include <list>

class Usuario{
private:
	std::string Id_, nombre_, email_;

public:
	Usuario(const std::string& id, const std::string& nombre, const std::string& email);
	bool Autentificar();
	std::string GetId(){return Id_;}
	std::string GetNombre(){return nombre_;}
	std::string GetEmail(){return email_;}
	bool SetId(const std::string& id);
	bool SetNombre(const std::string& nombre);
	bool SetEmail(const std::string& nombre);
};

class Estudiante : public Usuario{
private:
	std::string informacion_academica_, alojamiento_, progreso_;
	Tutor tutor_asignado_;
	std::list<Alerta> alertas_registradas;

public:
	Estudiante(const std::string& id, const std::string& nombre, const std::string& email, const std::string& informacion_academica, const std::string& alojamiento, const std::string& progreso);
	std::string GetInformacionAcademica(){return informacion_academica_;}
	std::string GetAlojamineto(){return alojamiento_;}
	Tutor GetTutor(){return Tutor;}
	std::list<Alerta> GetAlertasRegistradas(){return alertas_registradas;}
	std::string GetProgreso(){return progreso_;}

	bool SetInformacionAcademica(const std::string& informacion_academica);
	bool SetAlojamiento(const std::string& alojamiento);
	bool SetTutor(const Tutor& tutor);
	bool SetProgreso(const std::string& progeso);


	Mensaje EnviarMensaje(const Tutor& tutor);

};

class Tutor : public Usuario{
private:
	std::string facultad_, horario_;

public:
	Tutor(const std::string& id, const std::string& nombre, const std::string& email, const std::string& facultad, const std::string& horario);
	std::string GetFacultad(){return facultad_;}
	std::string GetHorario(){return horario_;}
	bool SetFacultad(const std::string& facultad);
	bool SetHorario(const std::string& horario);

	Mensaje EnviarMensaje(const Estudiante& estudiante);
	void GestionarAlerta(const Alerta& alerta);

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
	std::list<Asignacion> EjecutarAsignacionAutomatica();
};


#endif
