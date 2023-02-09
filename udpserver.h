#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTimer>
#include <QThread>
#include "QCoreApplication"
#include <udpclient.h>
#include <vector>
using std::vector;
class UdpServer : public QThread {
    Q_OBJECT
public:
    ~UdpServer();
    explicit UdpServer(QObject *parent = nullptr);
    Q_INVOKABLE bool setPort(quint16 port);
    Q_INVOKABLE bool sendMessage(QByteArray s);
    Q_INVOKABLE QByteArray receiveMessage();
    void run()override;
private:
    QUdpSocket* m_server;
    //通信的ip和端口
    QHostAddress addr;
    quint16 port;
    QTimer *m_pTimer;
    vector<QByteArray>  m_s;
    //QByteArray m_clientData;
    vector<QByteArray> m_clientData;
signals:
    void triggerServer(vector<QByteArray> temp);
public slots:
    void slotClientSend(vector<QByteArray> temp);
};

#endif // TCPSERVER_H
