#ifndef COORDINADOR_REPO_H
#define COORDINADOR_REPO_H

#include <vector>
#include <string>
#include <optional>
#include "../models/usuario.h"
#include "../infrastructure/basedatos.h"

class CoordinadorRepository {
public:
    std::vector<Coordinador> obtenerTodos();
    std::optional<Coordinador> buscarPorId(std::string id);
    bool guardar(Coordinador c);
    bool actualizar(Coordinador c);
    bool eliminar(std::string id);
};

#endif