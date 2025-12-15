#include "main_window.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <iostream>
#include <QDialog>
#include <QComboBox>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

MainWindow::MainWindow(QString idUsuario, QString rol, QWidget *parent)
    : QMainWindow(parent), currentUserId(idUsuario), currentUserRole(rol) {
    
    setWindowTitle("SITAPI - Panel Principal (" + rol + ")");
    resize(1100, 700);
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

    QTabWidget *coordSubTabs = new QTabWidget();

    QWidget *tabOps = new QWidget();
    QVBoxLayout *opsLayout = new QVBoxLayout(tabOps);
    QLabel *info = new QLabel("Panel de Control Académico");
    info->setStyleSheet("font-weight: bold; font-size: 14px;");
    btnAsignarAuto = new QPushButton("Ejecutar Asignación Automática de Tutores");
    btnAsignarAuto->setMinimumHeight(60);
    opsLayout->addWidget(info);
    opsLayout->addWidget(btnAsignarAuto);
    opsLayout->addStretch();
    coordSubTabs->addTab(tabOps, "Operaciones");

    QWidget *tabAlertas = new QWidget();
    QVBoxLayout *alertasLayout = new QVBoxLayout(tabAlertas);
    coordTablaAlertas = new QTableWidget();
    coordTablaAlertas->setColumnCount(5);
    coordTablaAlertas->setHorizontalHeaderLabels({"ID", "Estudiante", "Motivo", "Estado", "Comentarios"});
    coordTablaAlertas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    alertasLayout->addWidget(new QLabel("Monitor Global de Alertas:"));
    alertasLayout->addWidget(coordTablaAlertas);
    coordSubTabs->addTab(tabAlertas, "Alertas Globales");

    QWidget *tabAsig = new QWidget();
    QVBoxLayout *asigLayout = new QVBoxLayout(tabAsig);
    coordTablaAsignaciones = new QTableWidget();
    coordTablaAsignaciones->setColumnCount(5);
    coordTablaAsignaciones->setHorizontalHeaderLabels({"ID", "Estudiante", "Tutor", "Fecha", "Criterios"});
    coordTablaAsignaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    asigLayout->addWidget(new QLabel("Historial Total de Asignaciones:"));
    asigLayout->addWidget(coordTablaAsignaciones);
    coordSubTabs->addTab(tabAsig, "Asignaciones");

    QPushButton *btnRefreshCoord = new QPushButton("Actualizar Datos");
    connect(btnRefreshCoord, &QPushButton::clicked, this, &MainWindow::refrescarVistaCoordinador);

    coordLayout->addWidget(coordSubTabs);
    coordLayout->addWidget(btnRefreshCoord);

    connect(btnAsignarAuto, &QPushButton::clicked, this, &MainWindow::on_btnAsignarAuto_clicked);
    
    tabs->addTab(tabCoordinador, "Coordinación");
    
    refrescarVistaCoordinador();
}

void MainWindow::refrescarVistaCoordinador() {
    if (coordTablaAlertas) {
        coordTablaAlertas->setRowCount(0);
        std::vector<Alerta> todasAlertas = alertService.ConsultarTodasLasAlertas();
        for (auto& a : todasAlertas) {
            int row = coordTablaAlertas->rowCount();
            coordTablaAlertas->insertRow(row);
            coordTablaAlertas->setItem(row, 0, new QTableWidgetItem(QString::number(a.GetId())));
            coordTablaAlertas->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.GetIdEstudiante())));
            coordTablaAlertas->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.GetMotivo())));
            coordTablaAlertas->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.GetEstado())));
            coordTablaAlertas->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.GetComentarios())));
        }
    }

    if (coordTablaAsignaciones) {
        coordTablaAsignaciones->setRowCount(0);
        std::vector<Asignacion> todasAsig = assignmentService.ConsultarTodasLasAsignaciones();
        for (auto& asig : todasAsig) {
            int row = coordTablaAsignaciones->rowCount();
            coordTablaAsignaciones->insertRow(row);
            coordTablaAsignaciones->setItem(row, 0, new QTableWidgetItem(QString::number(asig.GetId()))); 
            coordTablaAsignaciones->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(asig.GetIdEstudiante())));
            coordTablaAsignaciones->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(asig.GetIdTutor())));
            coordTablaAsignaciones->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(asig.GetFecha())));
            coordTablaAsignaciones->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(asig.GetCriterios())));
        }
    }
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
    tablaAlertas->setColumnCount(5); 
    tablaAlertas->setHorizontalHeaderLabels({"ID", "Alumno", "Motivo", "Estado", "Comentarios"});
    tablaAlertas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    QHBoxLayout *alertBtnLayout = new QHBoxLayout();
    btnRefrescarAlertas = new QPushButton("Actualizar Tabla");
    btnEditarAlerta = new QPushButton("Editar Estado/Comentario");

    alertBtnLayout->addWidget(btnRefrescarAlertas);
    alertBtnLayout->addWidget(btnEditarAlerta);

    alertasLayout->addWidget(new QLabel("Monitor de Alertas:"));
    alertasLayout->addWidget(tablaAlertas);
    alertasLayout->addLayout(alertBtnLayout);
    
    subTabs->addTab(tabAlertas, "Alertas");

    layout->addWidget(subTabs);
    
    connect(btnAbrirChat, &QPushButton::clicked, this, &MainWindow::on_btnAbrirChat_clicked);
    connect(btnGenerarAlerta, &QPushButton::clicked, this, &MainWindow::on_btnGenerarAlerta_clicked);
    connect(btnRefrescarAlertas, &QPushButton::clicked, this, &MainWindow::refrescarTablaAlertas);
    connect(btnEditarAlerta, &QPushButton::clicked, this, &MainWindow::on_btnEditarAlerta_clicked);

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
            tablaAlertas->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.GetComentarios())));
        }
    }
}

void MainWindow::on_btnAsignarAuto_clicked() {
    bool resultado = assignmentService.RealizarAsignacionAutomatica();
    if (resultado) {
        QMessageBox::information(this, "Asignación", "Proceso completado con éxito. Se han generado nuevas asignaciones.");
        refrescarVistaCoordinador();
    } else {
        QMessageBox::warning(this, "Asignación", "No se realizaron cambios (es posible que todos los alumnos ya tengan tutor o falten tutores libres).");
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

void MainWindow::on_btnEditarAlerta_clicked() {
    int currentRow = tablaAlertas->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Aviso", "Selecciona una alerta de la tabla primero.");
        return;
    }

    QString idAlertaStr = tablaAlertas->item(currentRow, 0)->text();
    QString estadoActual = tablaAlertas->item(currentRow, 3)->text();
    QString comentariosActuales = tablaAlertas->item(currentRow, 4)->text();

    QDialog dialog(this);
    dialog.setWindowTitle("Gestionar Alerta #" + idAlertaStr);
    dialog.resize(400, 300);
    
    QFormLayout form(&dialog);
    
    QComboBox comboEstado;
    comboEstado.addItems({"Pendiente", "En seguimiento", "Resuelta"});
    comboEstado.setCurrentText(estadoActual);
    form.addRow("Estado:", &comboEstado);
    
    QTextEdit txtComentarios;
    txtComentarios.setText(comentariosActuales);
    form.addRow("Comentarios:", &txtComentarios);
    
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    
    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int idAlerta = idAlertaStr.toInt();
        std::string nuevoEstado = comboEstado.currentText().toStdString();
        std::string nuevosComentarios = txtComentarios.toPlainText().toStdString();
        
        if (alertService.ActualizarEstadoAlerta(idAlerta, nuevoEstado, nuevosComentarios)) {
            QMessageBox::information(this, "Éxito", "Alerta actualizada.");
            refrescarTablaAlertas();
        } else {
            QMessageBox::critical(this, "Error", "No se pudo actualizar la base de datos.");
        }
    }
}