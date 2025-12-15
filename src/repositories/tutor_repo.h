#ifndef TUTOR_REPO_H
#define TUTOR_REPO_H

#include <vector>
#include <string>
#include <optional>
#include "../models/usuario.h"
#include "../infrastructure/basedatos.h"

class TutorRepository {
public:
    std::vector<Tutor> obtenerTodos();
    std::optional<Tutor> buscarPorId(std::string id);
    bool guardar(Tutor tutor);
    bool actualizar(Tutor tutor);
    bool eliminar(std::string id);
};

#endif