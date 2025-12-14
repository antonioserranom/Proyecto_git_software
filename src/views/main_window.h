#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QTabWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QString>
#include <vector>

#include "../services/servicio_asignacion.h"
#include "../services/servicio_alerta.h"
#include "../services/servicio_chat.h"
#include "chat_window.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QString idUsuario, QString rol, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAsignarAuto_clicked();
    void on_btnAbrirChat_clicked();
    void on_btnGenerarAlerta_clicked();
    void refrescarListaEstudiantes();
    void refrescarTablaAlertas();

private:
    QString currentUserId;
    QString currentUserRole;

    AssignmentService assignmentService;
    AlertService alertService;
    ChatService chatService;

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *welcomeLabel;
    QTabWidget *tabs;

    QWidget *tabCoordinador;
    QPushButton *btnAsignarAuto;
    
    QWidget *tabGestion;
    QListWidget *listaPersonas;
    QPushButton *btnAbrirChat;
    QPushButton *btnGenerarAlerta;
    
    QTableWidget *tablaAlertas;
    QPushButton *btnRefrescarAlertas;

    void setupUi();
    void setupCoordinatorView();
    void setupTutorView();
    void setupStudentView();
};

#endif