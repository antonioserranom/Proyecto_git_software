#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "../services/servicio_sesion.h"

class MainWindow; 

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    QLabel *titleLabel;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QPushButton *loginButton;
    QLabel *statusLabel;

    SessionService sessionService;
    
    void setupUi();
    void centerWindow();
};

#endif