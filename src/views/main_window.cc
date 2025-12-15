#include "main_window.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <iostream>

MainWindow::MainWindow(QString idUsuario, QString rol, QWidget *parent)
    : QMainWindow(parent), currentUserId(idUsuario), currentUserRole(rol) {
    
    setWindowTitle("SITAPI - Panel Principal (" + rol + ")");
    resize(900, 600);
    setupUi();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUi() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    welcomeLabel = new QLabel("Bienvenido, usuario: " + currentUserId + " [" + currentUserRole + "]");
    welcomeLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
    mainLayout->addWidget(welcomeLabel);

    tabs = new QTabWidget(centralWidget);
    mainLayout->addWidget(tabs);

    if (currentUserRole == "COORDINADOR") {
        setupCoordinatorView();
    } else if (currentUserRole == "TUTOR") {
        setupTutorView();
    } else if (currentUserRole == "ESTUDIANTE") {
        setupStudentView();
    }
}

void MainWindow::setupCoordinatorView() {
    tabCoordinador = new QWidget();
    QVBoxLayout *coordLayout = new QVBoxLayout(tabCoordinador);

    QLabel *info = new QLabel("Gestión de Asignaciones");
    btnAsignarAuto = new QPushButton("Ejecutar Asignación Automática");
    btnAsignarAuto->setMinimumHeight(50);
    
    coordLayout->addWidget(info);
    coordLayout->addWidget(btnAsignarAuto);
    coordLayout->addStretch();

    connect(btnAsignarAuto, &QPushButton::clicked, this, &MainWindow::on_btnAsignarAuto_clicked);
    
    tabs->addTab(tabCoordinador, "Coordinación");
}

void MainWindow::setupTutorView() {
    tabGestion = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tabGestion);

    QTabWidget *subTabs = new QTabWidget();
    
    QWidget *tabAlumnos = new QWidget();
    QVBoxLayout *alumnosLayout = new QVBoxLayout(tabAlumnos);

    alumnosLayout->addWidget(new QLabel("Mis Estudiantes Asignados:"));
    listaPersonas = new QListWidget();
    alumnosLayout->addWidget(listaPersonas);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnAbrirChat = new QPushButton("Abrir Chat");
    btnGenerarAlerta = new QPushButton("Generar Alerta");
    btnLayout->addWidget(btnAbrirChat);
    btnLayout->addWidget(btnGenerarAlerta);
    alumnosLayout->addLayout(btnLayout);
    
    subTabs->addTab(tabAlumnos, "Mis Alumnos");

    QWidget *tabAlertas = new QWidget();
    QVBoxLayout *alertasLayout = new QVBoxLayout(tabAlertas);
    
    tablaAlertas = new QTableWidget();
    tablaAlertas->setColumnCount(4);
    tablaAlertas->setHorizontalHeaderLabels({"ID Alerta", "Alumno", "Motivo", "Estado"});
    tablaAlertas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    btnRefrescarAlertas = new QPushButton("Actualizar Alertas");
    connect(btnRefrescarAlertas, &QPushButton::clicked, this, &MainWindow::refrescarTablaAlertas);

    alertasLayout->addWidget(new QLabel("Monitor de Alertas:"));
    alertasLayout->addWidget(tablaAlertas);
    alertasLayout->addWidget(btnRefrescarAlertas);
    
    subTabs->addTab(tabAlertas, "Alertas");

    layout->addWidget(subTabs);
    
    connect(btnAbrirChat, &QPushButton::clicked, this, &MainWindow::on_btnAbrirChat_clicked);
    connect(btnGenerarAlerta, &QPushButton::clicked, this, &MainWindow::on_btnGenerarAlerta_clicked);

    tabs->addTab(tabGestion, "Gestión Tutor");
    
    refrescarListaEstudiantes();
    refrescarTablaAlertas();
}

void MainWindow::setupStudentView() {
    tabGestion = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tabGestion);

    layout->addWidget(new QLabel("Mi Tutor:"));
    listaPersonas = new QListWidget();
    layout->addWidget(listaPersonas);

    btnAbrirChat = new QPushButton("Chatear con Tutor");
    layout->addWidget(btnAbrirChat);

    connect(btnAbrirChat, &QPushButton::clicked, this, &MainWindow::on_btnAbrirChat_clicked);

    tabs->addTab(tabGestion, "Mi Tutoría");
    
    std::string idTutor = assignmentService.GetTutorDeEstudiante(currentUserId.toStdString());
    if (!idTutor.empty()) {
        listaPersonas->addItem(QString::fromStdString(idTutor));
    } else {
        listaPersonas->addItem("Pendiente de Asignación");
        btnAbrirChat->setEnabled(false);
    }
}

void MainWindow::refrescarListaEstudiantes() {
    if (currentUserRole != "TUTOR") return;

    listaPersonas->clear();
    std::vector<Estudiante> misAlumnos = assignmentService.GetAlumnosDeTutor(currentUserId.toStdString());
    
    if (misAlumnos.empty()) {
        listaPersonas->addItem("No hay estudiantes asignados.");
        return;
    }

    for (auto& est : misAlumnos) {
        QString itemText = QString::fromStdString(est.GetId()) + " - " + QString::fromStdString(est.GetNombre());
        listaPersonas->addItem(itemText);
    }
}

void MainWindow::refrescarTablaAlertas() {
    if (!tablaAlertas) return;
    
    tablaAlertas->setRowCount(0);
    std::vector<Estudiante> misAlumnos = assignmentService.GetAlumnosDeTutor(currentUserId.toStdString());
    
    for (auto& alumno : misAlumnos) {
        std::vector<Alerta> alertasAlumno = alertService.ConsultarAlertasPorEstudiante(alumno.GetId());
        
        for (auto& a : alertasAlumno) {
            int row = tablaAlertas->rowCount();
            tablaAlertas->insertRow(row);
            tablaAlertas->setItem(row, 0, new QTableWidgetItem(QString::number(a.GetId())));
            tablaAlertas->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.GetIdEstudiante())));
            tablaAlertas->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.GetMotivo())));
            tablaAlertas->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.GetEstado())));
        }
    }
}

void MainWindow::on_btnAsignarAuto_clicked() {
    bool resultado = assignmentService.RealizarAsignacionAutomatica();
    if (resultado) {
        QMessageBox::information(this, "Asignación", "Proceso completado con éxito.");
    } else {
        QMessageBox::warning(this, "Asignación", "No se realizaron cambios.");
    }
}

void MainWindow::on_btnAbrirChat_clicked() {
    QListWidgetItem *item = listaPersonas->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Error", "Selecciona una persona de la lista primero.");
        return;
    }

    QString textoItem = item->text();
    if (textoItem.contains("No hay") || textoItem.contains("Pendiente")) return;

    QString targetIdQ = textoItem.split(" ")[0];
    std::string targetId = targetIdQ.toStdString();
    
    std::string idEst = (currentUserRole == "ESTUDIANTE") ? currentUserId.toStdString() : targetId;
    std::string idTut = (currentUserRole == "TUTOR") ? currentUserId.toStdString() : targetId;

    int chatId = chatService.IniciarChat(idEst, idTut);
    
    if (chatId != -1) {
        ChatWindow *chatWin = new ChatWindow(chatId, currentUserId.toStdString(), targetId);
        chatWin->show();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo iniciar el chat.");
    }
}

void MainWindow::on_btnGenerarAlerta_clicked() {
    QListWidgetItem *item = listaPersonas->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Aviso", "Selecciona un estudiante.");
        return;
    }
    
    QString textoItem = item->text();
    if (textoItem.contains("No hay") || textoItem.contains("Pendiente")) return;

    std::string idEst = textoItem.split(" ")[0].toStdString();

    if (alertService.GenerarAlerta(idEst, "Alerta Manual generada por Tutor")) {
        QMessageBox::information(this, "Éxito", "Alerta generada correctamente.");
        refrescarTablaAlertas();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo generar la alerta.");
    }
}