#ifndef CHAT_REPO_H
#define CHAT_REPO_H

#include <vector>
#include <string>
#include "../models/chat.h"
#include "../models/mensaje.h" 
#include "../infrastructure/basedatos.h"

class ChatRepository {
public:
    std::vector<Chat> obtenerChatsPorEstudiante(std::string idEstudiante);
    std::vector<Chat> obtenerChatsPorTutor(std::string idTutor);
    bool crearChat(Chat chat);
    
    std::vector<Mensaje> obtenerMensajes(int idChat);
    bool enviarMensaje(Mensaje msg); 
};

#endif