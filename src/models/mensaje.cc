/**
 * @file mensaje.cc
 * @brief Contiene la implementacion de la clase mensaje.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

 #include "mensaje.h"


Mensaje::Mensaje(const int& id, const int& id_chat, const std::string& id_remitente, const std::string& contenido, const std::string& fecha){
    id_mensaje_ = id;
    id_chat_ = id_chat;
    id_remitente_ = id_remitente;
    contenido_ = contenido;
    if (fecha.empty()) {
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        fecha_envio_ = buf;
    } else {
        fecha_envio_ = fecha;
    }
}
