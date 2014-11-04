#include "tmconnector.h"
#include <QDataStream>

#define PWM_PIPE_NAME_SYSTEM_LEVEL "\\\\.\\pipe\\TMIPCPALLADIUMSYSTEM"
#define PWM_PIPE_NAME_SESSION_LEVEL "\\\\.\\pipe\\TMIPCPALLADIUMSESSION"
#define PWM_PIPE_NAME_RELAY "\\\\.\\pipe\\mynamedpipe"

TMConnector::TMConnector(QObject *parent) : QObject(parent), m_socket(this), m_serverName(PWM_PIPE_NAME_RELAY), m_message()
{
    connect(&m_socket, SIGNAL(connected()), this, SLOT(socket_connected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(socket_readReady()));
    connect(&m_socket, SIGNAL(error(QLocalSocket::LocalSocketError)), this, SLOT(socket_error(QLocalSocket::LocalSocketError)));
}

TMConnector::~TMConnector()
{
    m_socket.abort();
}

void TMConnector::send_MessageToServer(QString message) {
    m_socket.abort();
    m_message = message;
    m_socket.connectToServer(m_serverName, QLocalSocket::WriteOnly);
}

void TMConnector::socket_connected()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << m_message;
    out.device()->seek(0);
    m_socket.write(block);
    m_socket.flush();
    m_socket.disconnectFromServer();

    qDebug() << "socket connetcted";
}

void TMConnector::socket_disconnected() {
    qDebug() << "socket_disconnected";
}


void TMConnector::socket_readReady() {
    qDebug() << "socket_readReady";

    QDataStream in(&m_socket);
    in.setVersion(QDataStream::Qt_5_3);
    if (m_socket.bytesAvailable() < (int)sizeof(quint16)) {
        return;
    }
    QString message;
    in >> message;

    qDebug() << "Client got Msg : " << message;

    send_MessageToServer("OK");
}

void TMConnector::socket_error(QLocalSocket::LocalSocketError e) {
    qDebug() << e;
}
