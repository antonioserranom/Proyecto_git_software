/**
 * @file chat.h
 * @brief Contiene la implementacion de la clase chat.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

#ifndef CHAT_H
#define CHAT_H

#include "usuario.h"
#include <vector>

class chat{

private:

    Usuario remitente_;
    Usuario destinatario_;
    std::vector<mensaje> mensajes_;

public:
    chat(const Usuario& remitente, const Usuario& destinatario);
    Usuario GetRemitente()const{return remitente_;}
    Usuario GetDestinatario()const{return destinatario_;}
    std::vector<mensaje> GetMensajes(){return mensajes_;}
    void EnviarMensaje(const mensaje& mensaje);};








#endif