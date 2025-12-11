/**
 * @file mensaje.h
 * @brief Contiene la implementacion de la clase mensaje.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */
#ifndef MENSAJE_H
#define MENSAJE_H

#include "usuario.h"

class Mensaje{

private:
    Estudiante usuario1_;
    Tutor usuario2_;
    std::string contenido_;
    std::time_t fecha_envio_;
public:
    Mensaje(const Estudiante& usuario1, const Tutor& Usuario2, const std::string& contenido, const std::time_t fecha_envio);
    Estudiante GetRemitente()const{return usuario1_;}
    Tutor GetDestinatario()const{return usuario2_;}
    std::string GetContenido()const{return contenido_;}
    std::time_t GetFecha_envio()const{return fecha_envio_;}
};












#endif