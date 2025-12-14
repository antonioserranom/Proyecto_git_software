#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "src/views/login_window.h"
#include "src/infrastructure/basedatos.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    if (!BaseDatos::getInstancia()->abrirConexion()) {
        QMessageBox::critical(nullptr, "Error de Sistema", "No se pudo conectar a la base de datos.");
        return 1;
    }

    LoginWindow loginWindow;
    loginWindow.show();
    
    int result = app.exec();
    
    BaseDatos::getInstancia()->cerrarConexion();
    
    return result;
}
