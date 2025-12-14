#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include "../services/servicio_chat.h"

class ChatWindow : public QWidget {
    Q_OBJECT

public:
    explicit ChatWindow(int idChat, std::string idUsuario, std::string idOtroUsuario, QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void on_sendButton_clicked();
    void refreshMessages();

private:
    int currentChatId;
    std::string currentUserId;
    std::string otherUserId;
    
    ChatService chatService;
    QTimer *refreshTimer;

    QVBoxLayout *mainLayout;
    QListWidget *messageList;
    QLineEdit *inputMessage;
    QPushButton *sendButton;
    QLabel *headerLabel;

    void setupUi();
};

#endif