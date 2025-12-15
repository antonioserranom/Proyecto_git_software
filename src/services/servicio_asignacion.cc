#include "servicio_asignacion.h"
#include <map>

const int MAX_ALUMNOS_POR_TUTOR = 10;

bool AssignmentService::RealizarAsignacionAutomatica() {
    std::vector<Tutor> tutores = repoTutores.obtenerTodos();
    std::vector<Estudiante> estudiantes = repoEstudiantes.obtenerTodos();
    
    if (tutores.empty() || estudiantes.empty()) {
        return false;
    }

    std::map<std::string, int> cargaTrabajo;
    for (auto& t : tutores) {
        cargaTrabajo[t.GetId()] = 0;
    }

    for (auto& est : estudiantes) {
        std::string idTutor = est.GetIdTutor();
        if (!idTutor.empty() && idTutor != "NULL") {
            cargaTrabajo[idTutor]++;
        }
    }

    bool cambiosRealizados = false;

    for (auto& est : estudiantes) {
        if (est.GetIdTutor().empty() || est.GetIdTutor() == "NULL") {
            
            std::string mejorTutorId = "";
            int mejorPuntuacion = -9999; 
            
            for (auto& t : tutores) {
                if (cargaTrabajo[t.GetId()] >= MAX_ALUMNOS_POR_TUTOR) {
                    continue;
                }

                int puntuacion = 0;
                puntuacion -= (cargaTrabajo[t.GetId()] * 10);

                std::string infoEst = est.GetInfo();
                std::string areaTut = t.GetAreaConocimiento();

                if (!areaTut.empty() && infoEst.find(areaTut) != std::string::npos) {
                    puntuacion += 1000;
                }

                if (puntuacion > mejorPuntuacion) {
                    mejorPuntuacion = puntuacion;
                    mejorTutorId = t.GetId();
                }
            }

            if (!mejorTutorId.empty()) {
                est.SetIdTutor(mejorTutorId);
                repoEstudiantes.actualizar(est);

                std::string motivo = "Asignacion Automatica";
                if (mejorPuntuacion >= 1000) {
                    motivo += " (Por Compatibilidad)";
                } else {
                    motivo += " (Por Disponibilidad)";
                }

                Asignacion nuevaAsignacion(0, est.GetId(), mejorTutorId, motivo, "", "");
                repoAsignaciones.guardar(nuevaAsignacion);

                cargaTrabajo[mejorTutorId]++;
                cambiosRealizados = true;
            }
        }
    }

    return cambiosRealizados;
}

std::vector<Asignacion> AssignmentService::VerHistorialDeEstudiante(std::string idEstudiante) {
    return repoAsignaciones.obtenerPorEstudiante(idEstudiante);
}

std::vector<Estudiante> AssignmentService::GetAlumnosDeTutor(std::string idTutor) {
    return repoEstudiantes.obtenerPorTutor(idTutor);
}

std::string AssignmentService::GetTutorDeEstudiante(std::string idEstudiante) {
    auto estudianteOpt = repoEstudiantes.buscarPorId(idEstudiante);
    if (estudianteOpt.has_value()) {
        std::string idTutor = estudianteOpt->GetIdTutor();
        if (idTutor != "Unknown" && idTutor != "NULL" && !idTutor.empty()) {
            return idTutor;
        }
    }
    return "";
}

std::vector<Asignacion> AssignmentService::ConsultarTodasLasAsignaciones(){
    return repoAsignaciones.obtenerTodas();
}