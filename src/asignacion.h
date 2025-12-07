/**
 * @file asignacion.h
 * @brief Contiene la definición de la clase Asignacion.
 * @author Antonio Serrano Maldonado
 * @date 07/12/25
 */
#ifndef ASIGNACION_H
#define ASIGNACION_H


#include "usuario.h"

class Asignacion{
    private:

    Estudiante estudiante_;
    Tutor tutor_;
    std::string criterios_;
    std::time_t fecha_;
    std::list<std::string> modificaciones_;

    void SetEstudiante(const Estudiante& estudiante);
    void SetTutor(const Tutor& tutor);
    void SetCriterios(const std::string& criterios);
    void SetFecha(const std::time_t& fecha);
    void AddModificacion(const std::string& modificacion);

    public:

    Asignacion(const Estudiante& estudiante, const Tutor& tutor);
    Estudiante GetEstudiante(){return estudiante_;}
    Tutor GetTutor(){return tutor_;}
    std::string GetCriterios(){return criterios_;}
    std::time_t GetFecha(){return fecha_;}
    std::list<std::string> GetModificaciones(){return modificaciones_;}

    friend class Coordinador
}


#endif
