#include "chat_window.h"
#include <QDateTime>

ChatWindow::ChatWindow(int idChat, std::string idUsuario, std::string idOtroUsuario, QWidget *parent)
    : QWidget(parent), currentChatId(idChat), currentUserId(idUsuario), otherUserId(idOtroUsuario) {
    
    setWindowTitle(QString::fromStdString("Chat con " + otherUserId));
    resize(400, 500);

    setupUi();

    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &ChatWindow::refreshMessages);
    refreshTimer->start(2000); 

    refreshMessages();
}

ChatWindow::~ChatWindow() {
}

void ChatWindow::setupUi() {
    mainLayout = new QVBoxLayout(this);

    headerLabel = new QLabel(QString::fromStdString("Conversación con: " + otherUserId));
    headerLabel->setStyleSheet("font-weight: bold; font-size: 14px; margin-bottom: 10px;");
    mainLayout->addWidget(headerLabel);

    messageList = new QListWidget(this);
    mainLayout->addWidget(messageList);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputMessage = new QLineEdit(this);
    sendButton = new QPushButton("Enviar", this);
    
    inputLayout->addWidget(inputMessage);
    inputLayout->addWidget(sendButton);

    mainLayout->addLayout(inputLayout);

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::on_sendButton_clicked);
}

void ChatWindow::on_sendButton_clicked() {
    QString texto = inputMessage->text().trimmed();
    if (texto.isEmpty()) return;

    if (chatService.EnviarMensaje(currentChatId, currentUserId, texto.toStdString())) {
        inputMessage->clear();
        refreshMessages();
    }
}

void ChatWindow::refreshMessages() {
    std::vector<Mensaje> mensajes = chatService.LeerConversacion(currentChatId);
    
    messageList->clear();
    for (const auto& msg : mensajes) {
        QString itemText = QString("[%1] %2: %3")
                           .arg(QString::fromStdString(msg.GetFechaEnvio()))
                           .arg(QString::fromStdString(msg.GetRemitente()))
                           .arg(QString::fromStdString(msg.GetContenido()));
        messageList->addItem(itemText);
    }
    messageList->scrollToBottom();
}