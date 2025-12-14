#ifndef ALERTA_REPO_H
#define ALERTA_REPO_H

#include <vector>
#include <string>
#include "../models/alerta.h"
#include "../infrastructure/basedatos.h"

class AlertaRepository{
public:
    Alerta buscarPorId(std::string id);
    std::vector<Alerta> obtenerTodas();
    std::vector<Alerta> obtenerPorEstudiante(std::string idEstudiante);
    bool guardar(Alerta a);
    bool actualizarEstado(std::string id, std::string nuevoEstado, std::string comentarios);
};

#endif