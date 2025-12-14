/**
 * @file mensaje.h
 * @brief Contiene la definición de la clase mensaje.
 * @author Adrian Sanchez Prieto
 * @date 11/12/25
 */
#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include <ctime>

class Mensaje{
private:
    int id_mensaje_, id_chat_;
    std::string id_remitente_, contenido_, fecha_envio_;

public:
    Mensaje(const int& id, const int& id_chat, const std::string& id_remitente, const std::string& contenido, const std::string& fecha);
    std::string GetRemitente() const {return id_remitente_;}
    std::string GetContenido() const {return contenido_;}
    std::string GetFechaEnvio() const {return fecha_envio_;}
    int GetIdChat() const {return id_chat_;}
};

#endif