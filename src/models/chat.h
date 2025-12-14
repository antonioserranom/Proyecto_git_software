/**
 * @file chat.h
 * @brief Contiene la definicion de la clase chat.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */

#ifndef CHAT_H
#define CHAT_H

#include "usuario.h"
#include <string>
#include <ctime>

class Chat{

private:
    int id_chat_;
    std::string id_estudiante_, id_tutor_, fecha_creacion_;

public:
    Chat(const int& id, const std::string& id_estudiante, const std::string& id_tutor, const std::string& fecha);
    int GetId() const { return id_chat_; }
    std::string GetIdEstudiante() const { return id_estudiante_; }
    std::string GetIdTutor() const { return id_tutor_; }
    std::string GetFechaCreacion() const {return fecha_creacion_;}
};








#endif