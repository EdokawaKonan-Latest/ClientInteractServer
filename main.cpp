#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "udpclient.h"
#include <udpserver.h>
#include <QThread>
#include <time.h>
using namespace std;
int m_flag;
int m_flag1;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //qml中使用 udpclient udpserver文件
    //qmlRegisterType<UdpClient>("an.qt.myUdpClient",1,0,"UdpClient");
    //qmlRegisterType<UdpServer>("an.qt.myUdpServer",1,0,"UdpServer");

    //client与server通过connect交互
    //变量声明
    UdpServer * Server = new UdpServer;
    UdpClient * Client = new UdpClient;
    qRegisterMetaType<vector<QByteArray>>("vector<QByteArray>");

    //将client中的信号triggerClient() 与 server中的槽slotClientSend绑定
    //当client接收数据到达一定数量之后,触发信号让server发送数据
    QObject::connect(Client,SIGNAL(triggerClient(vector<QByteArray>)), Server, SLOT(slotClientSend(vector<QByteArray>)));

    //将Server中的信号triggerServer() 与 server中的槽slotServerSend绑定
    //当server接收数据到达一定数量之后,触发信号让server发送数据
    QObject::connect(Server,SIGNAL(triggerServer(vector<QByteArray>)), Client, SLOT(slotServerSend(vector<QByteArray>)));

    //QQmlApplicationEngine engine;
    app.setApplicationName("temp");
    app.setOrganizationName("clientdata");
    //engine.load(QUrl(QStringLiteral("qrc:/receiveClient.qml")));

    //if (engine.rootObjects().isEmpty())
      //  return -1;
    return app.exec();
}
