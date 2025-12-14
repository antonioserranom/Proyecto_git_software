#ifndef ASIGNACION_REPO_H
#define ASIGNACION_REPO_H

#include <vector>
#include <string>
#include "../models/asignacion.h"
#include "../infrastructure/basedatos.h"

class AsignacionRepository {
public:
    std::vector<Asignacion> obtenerTodas();
    std::vector<Asignacion> obtenerPorEstudiante(std::string idEstudiante);
    bool guardar(Asignacion asig);
};

#endif