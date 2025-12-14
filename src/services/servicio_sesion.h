#ifndef SERVICIO_SESION_H
#define SERVICIO_SESION_H

#include <string>
#include "../repositories/estudiante_repo.h"
#include "../repositories/tutor_repo.h"
#include "../repositories/coordinador_repo.h"

class SessionService{
private:
    EstudianteRepository repoEstudiantes;
    TutorRepository repoTutores;
    CoordinadorRepository repoCoordinadores;

public:
    std::string Autenticar(std::string id);
};

#endif