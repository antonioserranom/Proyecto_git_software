#ifndef ESTUDIANTE_REPO_H
#define ESTUDIANTE_REPO_H

#include <vector>
#include <string>
#include <optional>
#include "../models/usuario.h"
#include "../infrastructure/basedatos.h"

class EstudianteRepository {
public:
    std::vector<Estudiante> obtenerTodos();
    std::vector<Estudiante> obtenerPorTutor(std::string idTutor);
    std::optional<Estudiante> buscarPorId(std::string id);
    bool guardar(Estudiante est);
    bool actualizar(Estudiante est);
    bool eliminar(std::string id);
};

#endif