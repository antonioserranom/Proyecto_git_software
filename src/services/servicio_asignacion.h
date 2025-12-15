#ifndef ASSIGNMENT_SERVICE_H
#define ASSIGNMENT_SERVICE_H

#include <vector>
#include <string>
#include "../repositories/estudiante_repo.h"
#include "../repositories/tutor_repo.h"
#include "../repositories/asignacion_repo.h"

class AssignmentService {
private:
    EstudianteRepository repoEstudiantes;
    TutorRepository repoTutores;
    AsignacionRepository repoAsignaciones;

public:
    bool RealizarAsignacionAutomatica();
    std::vector<Asignacion> VerHistorialDeEstudiante(std::string idEstudiante);
    std::vector<Estudiante> GetAlumnosDeTutor(std::string idTutor);
    std::string GetTutorDeEstudiante(std::string idEstudiante);
    std::vector<Asignacion> ConsultarTodasLasAsignaciones();
};

#endif