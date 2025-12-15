#include <QApplication>
#include <iostream>
#include "src/views/login_window.h"
#include "src/infrastructure/basedatos.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    if (!BaseDatos::getInstancia()->abrirConexion("../data/sitapi.db")) {
        if (!BaseDatos::getInstancia()->abrirConexion("sitapi.db")) {
            return 1;
        }
    }

    BaseDatos::getInstancia()->inicializarEsquema();

    if (BaseDatos::getInstancia()->estaVacia()) {
        BaseDatos::getInstancia()->importarDesdeArchivo("../data/inserciones.sql");
    }

    LoginWindow loginWindow;
    loginWindow.show();

    int result = app.exec();

    BaseDatos::getInstancia()->cerrarConexion();

    return result;
}
