#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTimer>
#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <udpserver.h>
#include "QCoreApplication"

class UdpClient : public QThread
{
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = nullptr);
    ~UdpClient();
    void run()override;
    Q_INVOKABLE bool connect(QHostAddress ip,quint16 port);
    Q_INVOKABLE bool sendMessage(QByteArray sendStr);
    Q_INVOKABLE QByteArray receiveMessage();
signals:
    void triggerClient(QByteArray temp);
public slots:
    void slotServerSend(QByteArray temp);
    
private:
    QUdpSocket *m_client;
    //服务端的ip
    QHostAddress addr;
    //服务端端口
    quint16 port;  
    QTimer *m_pTimer;
    QByteArray m_s;
    QByteArray m_serverData;
};

#endif // TCPSOCKET_H
