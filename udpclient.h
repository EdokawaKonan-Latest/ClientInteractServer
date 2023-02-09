#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTimer>
#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <udpserver.h>
#include "QCoreApplication"
#include <vector>
using std::vector;
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
    void triggerClient(vector<QByteArray> temp);
public slots:
    void slotServerSend(vector<QByteArray> temp);
    
private:
    QUdpSocket *m_client;
    //服务端的ip
    QHostAddress addr;
    //服务端端口
    quint16 port;  
    QTimer *m_pTimer;
    vector<QByteArray>  m_s;
    vector<QByteArray> m_serverData;
    //QByteArray m_serverData;
};

#endif // TCPSOCKET_H
