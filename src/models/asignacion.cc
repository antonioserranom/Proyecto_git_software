/**
 * @file asignacion.cc
 * @brief Contiene la implementación de la clase Asignacion.
 * @author Antonio Serrano Maldonado
 * @date 07/12/25
 */

#include "asignacion.h"

Asignacion::Asignacion(const int& id, const std::string& id_estudiante, const std::string& id_tutor, const std::string& criterios, const std::string& fecha, const std::string& modificaciones){
    id_ = id;
    id_estudiante_ = id_estudiante;
    id_tutor_ = id_tutor;
    if (fecha.empty()) {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    fecha_ = buf;
    } else {
        fecha_ = fecha;
    }
    criterios_ = criterios;
    modificaciones_=modificaciones;
}