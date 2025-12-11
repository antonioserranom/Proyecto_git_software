/**
 * @file mensaje.h
 * @brief Contiene la implementacion de la clase mensaje.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */
#ifndef MENSAJE_H
#define MENSAJE_H

#include "usuario.h"

class mensaje{

private:
    Usuario remitente_;
    Usuario destinatario_;
    std::string contenido_;
    std::time_t fecha_envio_;
public:
    mensaje(const Usuario& remitente, const Usuario& destinatario, const std::string& contenido, const std::time_t fecha_envio);
    Usuario GetRemitente()const{return remitente_;}
    Usuario GetDestinatario()const{return destinatario_;}
    std::string GetContenido()const{return contenido_;}
    std::time_t GetFecha_envio()const{return fecha_envio_;}
};












#endif