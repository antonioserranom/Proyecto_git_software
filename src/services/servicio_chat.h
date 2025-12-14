#ifndef CHAT_SERVICE_H
#define CHAT_SERVICE_H

#include <vector>
#include <string>
#include "../repositories/chat_repo.h"

class ChatService {
private:
    ChatRepository repoChat;

public:
    int IniciarChat(std::string idEstudiante, std::string idTutor);
    std::vector<Chat> ObtenerChatsDeEstudiante(std::string idEstudiante);
    std::vector<Chat> ObtenerChatsDeTutor(std::string idTutor);
    std::vector<Mensaje> LeerConversacion(int idChat);
    bool EnviarMensaje(int idChat, std::string idEmisor, std::string contenido);
};

#endif