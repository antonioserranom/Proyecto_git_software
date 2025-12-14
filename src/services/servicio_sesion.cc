#include "servicio_sesion.h"

std::string SessionService::Autenticar(std::string id) {
    if (!repoEstudiantes.buscarPorId(id).has_value()) {
        return "ESTUDIANTE";
    }

    if (!repoTutores.buscarPorId(id).GetId().empty()) {
        return "TUTOR";
    }

    if (!repoCoordinadores.buscarPorId(id).GetId().empty()) {
        return "COORDINADOR";
    }

    return "ERROR";
}
