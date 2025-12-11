/**
 * @file mensaje.cc
 * @brief Contiene la implementacion de la clase mensaje.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

 #include "mensaje.h"


 mensaje::mensaje(const Usuario& remitente, const Usuario& destinatario, const std::string& contenido, const std::time_t fecha_envio){
    remitente_=remitente;
    destinatario_=destinatario;
    contenido_=contenido;
    fecha_envio_=fecha_envio;
 }
