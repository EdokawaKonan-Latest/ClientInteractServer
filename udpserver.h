﻿#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTimer>
#include <QThread>
#include "QCoreApplication"
#include <udpclient.h>

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
    QByteArray m_s;
    QByteArray m_clientData;
    int m_flag = 0;
signals:
    void triggerServer(QByteArray temp);
public slots:
    void slotClientSend(QByteArray temp);
};

#endif // TCPSERVER_H