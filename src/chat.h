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

class Chat{

private:

    Estudiante usuario1_;
    Tutor usuario2_;
    std::vector<Mensaje> mensajes_;

public:
    Chat(const Estudiante& usuario1, const Tutor& usuario2);
    Estudiante GetRemitente()const{return usuario1_;}
    Tutor GetDestinatario()const{return usuario2_;}
    std::vector<Mensaje> GetMensajes(){return mensajes_;}
};








#endif