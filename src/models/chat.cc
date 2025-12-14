/**
 * @file chat.cc
 * @brief Contiene la implementacion de la clase chat.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

#include "chat.h"

Chat::Chat(const int& id, const std::string& id_estudiante, const std::string& id_tutor, const std::string& fecha){
    id_chat_ = id;
    id_estudiante_ = id_estudiante;
    id_tutor_ = id_tutor;
    if (fecha.empty()) {
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        fecha_creacion_ = buf;
    } else {
        fecha_creacion_ = fecha;
    }
}

