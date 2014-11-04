#ifndef TMCONNECTOR_H
#define TMCONNECTOR_H

#include <QObject>
#include <QLocalSocket>
#include <QString>

class TMConnector: public QObject
{
    Q_OBJECT

public:
    explicit TMConnector(QObject *parent = 0);
    ~TMConnector();

public slots:
    void send_MessageToServer(QString message);
    void socket_connected();
    void socket_disconnected();
    void socket_readReady();
    void socket_error(QLocalSocket::LocalSocketError);

private:
    QLocalSocket m_socket;
    QString m_serverName;
    QString m_message;
};

#endif // TMCONNECTOR_H
