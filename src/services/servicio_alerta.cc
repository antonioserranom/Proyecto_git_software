#include "servicio_alerta.h"

bool AlertService::GenerarAlerta(std::string idEstudiante, std::string motivo) {
    if (idEstudiante.empty() || motivo.empty()) {
        return false;
    }
    
    Alerta nuevaAlerta(0, idEstudiante, motivo, "", "Pendiente", ""); 
    return repoAlertas.guardar(nuevaAlerta);
}

bool AlertService::ActualizarEstadoAlerta(int idAlerta, std::string nuevoEstado, std::string comentarios) {
    std::string idStr = std::to_string(idAlerta);
    
    Alerta alerta = repoAlertas.buscarPorId(idStr);
    
    if (alerta.GetIdEstudiante().empty()) { 
        return false;
    }

    return repoAlertas.actualizarEstado(idStr, nuevoEstado, comentarios);
}

std::vector<Alerta> AlertService::ConsultarAlertasPorEstudiante(std::string idEstudiante) {
    return repoAlertas.obtenerPorEstudiante(idEstudiante);
}

std::vector<Alerta> AlertService::ConsultarTodasLasAlertas() {
    return repoAlertas.obtenerTodas();
}