/**
 * @file usuario.cc
 * @brief Contiene la implementacion de la clase Usuario y derivadas.
 * @author Antonio Serrano Maldonado
 * @date 26/11/25
 */
#include "usuario.h"
#include <cctype>

bool Usuario::SetId(const std::string& id){
	bool flag = false;
	if(!es_id_valido(id)){
		id_="Unknown";
		return flag;
	}else{
		id_=id;
		return !flag;
	}
}

bool Usuario::SetNombre(const std::string& nombre){
	bool flag = false;
	if(nombre == ""){
		nombre_="Unknown";
		return flag;
	}else{
		nombre_=nombre;
		return !flag;
	}
}

bool Usuario::SetEmail(const std::string& email){
	bool flag = false;
	if(email == ""){
		email_="Unknown";
		return flag;
	}else{
		email_=email;
		return !flag;
	}
}

Usuario::Usuario(const std::string& id, const std::string& nombre, const std::string& email){
	SetId(id);
	SetNombre(nombre);
	SetEmail(email);
}

bool Estudiante::SetInformacionAcademica(const std::string& informacion_academica){
	bool flag = false;
	if(informacion_academica == ""){
		informacion_academica_ = "Unknown";
		return flag;
	}else{
		informacion_academica_=informacion_academica;
		return !flag;
	}
}

bool Estudiante::SetAlojamiento(const std::string& alojamiento){
	bool flag = false;
	if(alojamiento == ""){
		alojamiento_ = "Unknown";
		return flag;
	}else{
		alojamiento_=alojamiento;
		return !flag;
	}
}

bool Estudiante::SetIdTutor(const std::string& id_tutor){
	id_tutor_asignado_ = id_tutor;
	return true;
}

bool Estudiante::SetProgreso(const std::string& progreso){
	bool flag = false;
	if(progreso == ""){
		progreso_ = "Unknown";
		return flag;
	}else{
		progreso_=progreso;
		return !flag;
	}
}

Estudiante::Estudiante(const std::string& id, const std::string& nombre, const std::string& email, const std::string& informacion_academica, const std::string& alojamiento, const std::string& progreso, const std::string& id_tutor)
 : Usuario(id, nombre, email){
	SetInformacionAcademica(informacion_academica);
	SetAlojamiento(alojamiento);
	SetProgreso(progreso);
	SetIdTutor(id_tutor);
}

bool Tutor::SetFacultad(const std::string& facultad){
	bool flag = false;
	if(facultad == ""){
		facultad_ = "Unknown";
		return flag;
	}else{
		facultad_=facultad;
		return !flag;
	}
}
bool Tutor::SetHorario(const std::string& horario){
	bool flag = false;
	if(horario == ""){
		horario_ = "Unknown";
		return flag;
	}else{
		horario_=horario;
		return !flag;
	}
}
bool Tutor::SetAreaConocimiento(const std::string& area_conocimiento){
	bool flag = false;
	if(area_conocimiento == ""){
		area_conocimiento_ = "Unknown";
		return flag;
	}else{
		area_conocimiento_=area_conocimiento;
		return !flag;
	}
}

Tutor::Tutor(const std::string& id, const std::string& nombre, const std::string& email, const std::string& facultad, const std::string& horario, const std::string& area_conocimiento) : Usuario(id, nombre, email){
	SetFacultad(facultad);
	SetHorario(horario);
	SetAreaConocimiento(area_conocimiento);
}

bool Coordinador::SetFacultad(const std::string& facultad){
	bool flag = false;
	if(facultad == ""){
		facultad_ = "Unknown";
		return flag;
	}else{
		facultad_=facultad;
		return !flag;
	}
}
bool Coordinador::SetResponsabilidades(const std::string& responsabilidades){
	bool flag = false;
	if(responsabilidades == ""){
		responsabilidades_ = "Unknown";
		return flag;
	}else{
		responsabilidades_=responsabilidades;
		return !flag;
	}
}

Coordinador::Coordinador(const std::string& id, const std::string& nombre, const std::string& email, const std::string& facultad, const std::string& responsabilidades) : Usuario(id, nombre, email){
	SetFacultad(facultad);
	SetResponsabilidades(responsabilidades);
}




bool es_id_valido(const std::string& id) {
    const std::string LETRAS_ID = "TRWAGMYFPDXBNJZSQVHLCKE";

    if (id.length() != 9) return false;

    std::string numero_str = id.substr(0, 8);
    char letra_recibida = std::toupper(id[8]);

    for (char c : numero_str) {
        if (!std::isdigit(c)) return false;
    }

    try {
        int numero_dni = std::stoi(numero_str);
        char letra_calculada = LETRAS_ID[numero_dni % 23];
        return (letra_recibida == letra_calculada);
    } catch (const std::exception& e) {
        return false;
    }
}
