#include "login_window.h"
#include "main_window.h" 
#include <QMessageBox>
#include <QScreen>
#include <QApplication>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("SITAPI - Acceso al Sistema");
    
    setupUi();
    
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::on_loginButton_clicked);

    centerWindow();
}

LoginWindow::~LoginWindow() {
}

void LoginWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    titleLabel = new QLabel("SITAPI - GESTIÓN DE TUTORÍAS", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20pt; font-weight: bold; margin-bottom: 20px;");
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    
    idLabel = new QLabel("ID de Usuario:", centralWidget);
    idLineEdit = new QLineEdit(centralWidget);
    idLineEdit->setPlaceholderText("Introduzca su ID");
    
    inputLayout->addWidget(idLabel);
    inputLayout->addWidget(idLineEdit);
    
    mainLayout->addLayout(inputLayout);

    loginButton = new QPushButton("Iniciar Sesión", centralWidget);
    loginButton->setMinimumHeight(40);
    loginButton->setStyleSheet("background-color: #3498db; color: white; font-weight: bold;");
    
    statusLabel = new QLabel(" ");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("color: red;");

    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(statusLabel);
    
    mainLayout->addStretch();
}

void LoginWindow::centerWindow() {
    resize(400, 300); 
    
    const QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }
}

void LoginWindow::on_loginButton_clicked() {
    QString idUsuario = idLineEdit->text().trimmed();
    
    if (idUsuario.isEmpty()) {
        statusLabel->setText("El ID de usuario no puede estar vacío.");
        return;
    }

    std::string rol = sessionService.Autenticar(idUsuario.toStdString());
    
    if (rol == "ERROR") {
        statusLabel->setText("Acceso Denegado: ID o Contraseña incorrectos.");
        idLineEdit->clear();
        return;
    }

    QMessageBox::information(this, "Acceso Exitoso", 
                             QString("¡Bienvenido al sistema! Rol detectado: %1").arg(QString::fromStdString(rol)));
    
    MainWindow *mainWindow = new MainWindow(QString::fromStdString(idUsuario.toStdString()), QString::fromStdString(rol));
    mainWindow->show();
    
    this->close();
}