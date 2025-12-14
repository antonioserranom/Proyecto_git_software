#ifndef ALERT_SERVICE_H
#define ALERT_SERVICE_H

#include <vector>
#include <string>
#include "../repositories/alerta_repo.h"

class AlertService {
private:
    AlertaRepository repoAlertas;

public:
    bool GenerarAlerta(std::string idEstudiante, std::string motivo);
    bool ActualizarEstadoAlerta(int idAlerta, std::string nuevoEstado, std::string comentarios);
    std::vector<Alerta> ConsultarAlertasPorEstudiante(std::string idEstudiante);
    std::vector<Alerta> ConsultarTodasLasAlertas();
};

#endif