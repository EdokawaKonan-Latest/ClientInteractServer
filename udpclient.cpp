#include "udpclient.h"
extern int m_flag;
UdpClient::UdpClient(QObject *parent) : QThread(parent) {

    //线程开始
    start();
}
void UdpClient::run() {
    //client的定义
    m_client = new QUdpSocket;
    //服务端ip addr
    addr = "192.168.8.130";
    port = 50001;
    //设置缓冲区大小
    m_client->setReadBufferSize(32 * 1024 * 1024);
    //连接服务器
    connect(addr, port);
    //定时器定义
    m_pTimer = new QTimer();
    m_pTimer->setInterval(200);
    m_pTimer->start();
    //定时器槽
    QObject::connect(m_pTimer, &QTimer::timeout, this, [=, this]() mutable{
        if(m_s.size() != 0 && !m_flag) {
            emit triggerClient(m_s);//触发信号
            m_s.clear();
        }
    });
    QByteArray temp = "";
    while (1) {
        if(m_serverData.size()) {
            sendMessage(m_serverData);
            //数据清空
            m_serverData.clear();
        }

        //接受服务端数据
        temp = receiveMessage();
        //数据追加
        if(temp.size() != 0 && temp != "") {
            m_s += temp;
        }
        //数据超过10000就触发信号
        if(m_s.size() >= 50) {
            emit triggerClient(m_s);//触发信号
            m_s.clear();
        }
        //处理消息
        //QCoreApplication::processEvents();
    }
}



//连接服务器
bool UdpClient::connect(QHostAddress ip,quint16 port) {
    m_client->connectToHost(ip, port,QUdpSocket::ReadWrite);
    //等待连接2s
    if (m_client->waitForConnected(2000)) {
        qDebug() << "server connect success"<< ip << " " << port;
        return 1;
    }
    else {
        qDebug() << "server connect failed"<< ip << " " << port;
        return 0;
    }
}

//给服务器发送数据
bool UdpClient::sendMessage(QByteArray s) {
    if(s.size() == 0) return 1;
    static int a = 0;
    m_client->writeDatagram(s, s.size(), addr, port);
    m_flag = 0;
    return 0;
}

QByteArray UdpClient::receiveMessage() {
    QByteArray arr;
    arr.resize(m_client->pendingDatagramSize());
    if(arr.size() == 0) {
        return "";
    }
    //接收数据  不需要记录服务端的ip 和 port
    m_client->readDatagram(arr.data(), arr.size());
    return arr;
}

//槽
void UdpClient::slotServerSend(QByteArray temp) {
    m_serverData = temp;
}

UdpClient::~UdpClient() {
    this->wait();
    this->exit(0);
}
