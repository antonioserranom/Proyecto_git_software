/**
 * @file asignacion.cc
 * @brief Contiene la implementación de la clase Asignacion.
 * @author Antonio Serrano Maldonado
 * @date 07/12/25
 */

#include "asignacion.h"

void Asignacion::SetEstudiante(const Estudiante& estudiante){
    estudiante_=estudiante;
}

void Asignacion::SetTutor(const Tutor& tutor){
    tutor_=tutor;
}

void Asignacion::SetCriterios(const std::string& criterios){
    criterios_=criterios;
}
void Asignacion::SetFecha(const std::time_t& fecha){
    fecha_=fecha;
}
void Asignacion::AddModificacion(const std::string& modificacion){
    modificaciones_.insert(modificacion);
}

Asignacion::Asignacion(const Estudiante& estudiante, const Tutor& tutor){
    SetEstudiante(estudiante);
    SetTutor(tutor);
    SetFecha(time(NULL));
    SetCriterios("Asignacion realizada automáticamente");
}