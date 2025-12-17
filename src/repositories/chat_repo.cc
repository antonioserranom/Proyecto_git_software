#include "chat_repo.h"

static int callback_chats(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Chat>*>(listaPtr);
    int id = std::stoi(argv[0]);
    Chat c(
        id, 
        argv[1] ? argv[1] : "", 
        argv[2] ? argv[2] : "", 
        argv[3] ? argv[3] : ""  
    );
    lista->push_back(c);
    return 0;
}

static int callback_mensajes(void* listaPtr, int argc, char** argv, char** azColName) {
    auto* lista = static_cast<std::vector<Mensaje>*>(listaPtr);
    int id = std::stoi(argv[0]);
    int id_chat = std::stoi(argv[1]);
    Mensaje m(
        id,
        id_chat,
        argv[2] ? argv[2] : "", 
        argv[3] ? argv[3] : "", 
        argv[4] ? argv[4] : ""  
    );
    lista->push_back(m);
    return 0;
}

std::vector<Chat> ChatRepository::obtenerChatsPorEstudiante(std::string idEstudiante) {
    std::vector<Chat> listaResultado;
    std::string sql = "SELECT * FROM CHAT WHERE id_estudiante = '" + idEstudiante + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_chats, &listaResultado);
    return listaResultado;
}

std::vector<Chat> ChatRepository::obtenerChatsPorTutor(std::string idTutor) {
    std::vector<Chat> listaResultado;
    std::string sql = "SELECT * FROM CHAT WHERE id_tutor = '" + idTutor + "';";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_chats, &listaResultado);
    return listaResultado;
}

bool ChatRepository::crearChat(Chat chat) {
    std::string sql = "INSERT INTO CHAT (id_estudiante, id_tutor) VALUES ('" + 
                      chat.GetIdEstudiante() + "', '" + 
                      chat.GetIdTutor() + "');";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}

std::vector<Mensaje> ChatRepository::obtenerMensajes(int idChat) {
    std::vector<Mensaje> listaResultado;
    std::string sql = "SELECT * FROM MENSAJE WHERE id_chat = " + std::to_string(idChat) + " ORDER BY fecha_envio ASC;";
    BaseDatos::getInstancia()->ejecutarSQL(sql, callback_mensajes, &listaResultado);
    return listaResultado;
}

bool ChatRepository::enviarMensaje(Mensaje msg) {
    std::string sql = "INSERT INTO MENSAJE (id_chat, id_emisor, contenido) VALUES (" + 
                      std::to_string(msg.GetIdChat()) + ", '" + 
                      msg.GetRemitente() + "', '" + 
                      msg.GetContenido() + "');";
    return BaseDatos::getInstancia()->ejecutarSQL(sql);
}