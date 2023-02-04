#include "udpserver.h"
extern int m_flag;
UdpServer::UdpServer(QObject *parent) : QThread(parent) {

    start();
}
void UdpServer::run() {
    //udpserver的定义
    m_server = new QUdpSocket;
    //设置缓冲区大小
    m_server->setReadBufferSize(32 * 1024 * 1024);
    //设置服务端端口号 ip默认是主机ip
    setPort(7777);
    //线程开始
    //temp用来存储receiveMessage()
    QByteArray temp = "";

    //定时器，负责心跳包 以及定时emit
    m_pTimer = new QTimer();
    m_pTimer->setInterval(200);
    m_pTimer->start();
    //定时器连接槽函数
    QObject::connect(m_pTimer, &QTimer::timeout, this, [=, this]()mutable{
        //m_s.size()不等于0， 并且锁是解开的，就发送数据
//        if(m_s.size() != 0 ) {
//            emit triggerServer(m_s);
//            m_s.clear();
//        }
    });

    //负责处理数据接收， 以及发送clientData
    while (1) {
        if(m_clientData.size()) {
            sendMessage(m_clientData);
            m_clientData.clear();
        }
        //获取数据
        temp = receiveMessage();
        //receive数据拼接给m_s
        if(!temp.isEmpty() && temp != "") {
            //qDebug() << temp;
            m_s += temp;
        }

        //数据长度超过10000就激活信号发数据
        if(!m_flag && m_s.size() >= 50) {
            //加锁
            m_flag = 1;
            QByteArray x = m_s;
            emit triggerServer(x);
            m_s.clear();
        }
        //这样可以让死循环给出一定时间去处理qt的消息，也就是上面的定时器消息
        //QCoreApplication::processEvents();
    }
}

//槽 负责获取clientData的数据
void UdpServer::slotClientSend(QByteArray temp) {
    m_clientData = temp;
}

//设置服务端ip 端口
bool UdpServer::setPort(quint16 port) {
    //第一个参数绑定本机的ip地址 第二个参数是端口
    bool q = m_server->bind(QHostAddress::Any, port, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    return q;
}

//向客户端发送数据 addr,port是客户端的addr,port
bool UdpServer::sendMessage(QByteArray s) {
    if(m_server->writeDatagram(s, s.size(), addr, port)) {
        return 1;
    }
    return 0;
}

//接受客户端数据，通过readDatagram可以获取客户端 adrr port
QByteArray UdpServer::receiveMessage() {
    QByteArray arr;
    arr.resize(m_server->pendingDatagramSize());
    if(arr.size() == 0) {
        return "";
    }
    m_server->readDatagram(arr.data(), arr.size(), &addr, &port);
    return arr;
}

//析构函数
UdpServer::~UdpServer() {
    wait();
    exit(0);
}
