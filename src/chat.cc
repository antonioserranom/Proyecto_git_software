/**
 * @file chat.cc
 * @brief Contiene la implementacion de la clase chat.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

#include "chat.h"

 chat::chat(const Usuario& remitente, const Usuario& destinatario){
 
    remitente_=remitente;
    destinatario_=destinatario;
}

void chat::EnviarMensaje(const mensaje& mensaje) {
    
    mensajes_.push_back(mensaje);
}
