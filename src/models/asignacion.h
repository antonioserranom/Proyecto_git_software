/**
 * @file asignacion.h
 * @brief Contiene la definición de la clase Asignacion.
 * @author Antonio Serrano Maldonado
 * @date 07/12/25
 */
#ifndef ASIGNACION_H
#define ASIGNACION_H


#include <string>
#include <ctime>
#include <list>

class Asignacion{
    private:
        int id_;
        std::string id_estudiante_, id_tutor_, criterios_, fecha_, modificaciones_;

    public:

    Asignacion(const int& id, const std::string& id_estudiante, const std::string& id_tutor, const std::string& criterios, const std::string& fecha, const std::string& modificiaciones);
    int GetId(){return id_;}
    std::string GetIdEstudiante(){return id_estudiante_;}
    std::string GetIdTutor(){return id_tutor_;}
    std::string GetCriterios(){return criterios_;}
    std::string GetFecha(){return fecha_;}
    std::string GetModificaciones(){return modificaciones_;}
};


#endif
