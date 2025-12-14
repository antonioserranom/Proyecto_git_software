#include "servicio_chat.h"

int ChatService::IniciarChat(std::string idEstudiante, std::string idTutor) {
    std::vector<Chat> chatsExistentes = repoChat.obtenerChatsPorEstudiante(idEstudiante);
    
    for (const auto& c : chatsExistentes) {
        if (c.GetIdTutor() == idTutor) {
            return c.GetId();
        }
    }

    Chat nuevoChat(0, idEstudiante, idTutor, ""); 
    if (repoChat.crearChat(nuevoChat)) {
        chatsExistentes = repoChat.obtenerChatsPorEstudiante(idEstudiante);
        for (const auto& c : chatsExistentes) {
            if (c.GetIdTutor() == idTutor) {
                return c.GetId();
            }
        }
    }

    return -1;
}

std::vector<Chat> ChatService::ObtenerChatsDeEstudiante(std::string idEstudiante) {
    return repoChat.obtenerChatsPorEstudiante(idEstudiante);
}

std::vector<Chat> ChatService::ObtenerChatsDeTutor(std::string idTutor) {
    return repoChat.obtenerChatsPorTutor(idTutor);
}

std::vector<Mensaje> ChatService::LeerConversacion(int idChat) {
    return repoChat.obtenerMensajes(idChat);
}

bool ChatService::EnviarMensaje(int idChat, std::string idEmisor, std::string contenido) {
    if (contenido.empty()) {
        return false;
    }

    Mensaje msg(0, idChat, idEmisor, contenido, "");
    return repoChat.enviarMensaje(msg);
}