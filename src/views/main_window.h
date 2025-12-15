#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QHeaderView>
#include "../services/servicio_sesion.h"
#include "../services/servicio_chat.h"
#include "../services/servicio_asignacion.h"
#include "../services/servicio_alerta.h"
#include "chat_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QString idUsuario, QString rol, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAsignarAuto_clicked();
    void refrescarVistaCoordinador();

    void on_btnAbrirChat_clicked();
    void on_btnGenerarAlerta_clicked();
    void on_btnEditarAlerta_clicked(); 
    void refrescarTablaAlertas();
    void refrescarListaEstudiantes();

private:
    QString currentUserId;
    QString currentUserRole;
    
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *welcomeLabel;
    QTabWidget *tabs;

    QWidget *tabCoordinador;
    QPushButton *btnAsignarAuto;
    QTableWidget *coordTablaAlertas;
    QTableWidget *coordTablaAsignaciones;

    QWidget *tabGestion;
    QListWidget *listaPersonas;
    QPushButton *btnAbrirChat;
    QPushButton *btnGenerarAlerta;
    
    QTableWidget *tablaAlertas;
    QPushButton *btnRefrescarAlertas;
    QPushButton *btnEditarAlerta; 

    SessionService sessionService;
    ChatService chatService;
    AssignmentService assignmentService;
    AlertService alertService;

    void setupUi();
    void setupCoordinatorView();
    void setupTutorView();
    void setupStudentView();
};

#endif