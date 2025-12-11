/**
 * @file mensaje.cc
 * @brief Contiene la implementacion de la clase mensaje.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

 #include "mensaje.h"


 Mensaje::Mensaje(const Estudiante& usuario1, const Tutor& usuario2, const std::string& contenido, const std::time_t fecha_envio){
    usuario1_=usuario1;
    usuario2_=usuario2;
    contenido_=contenido;
    fecha_envio_=fecha_envio;
 }
