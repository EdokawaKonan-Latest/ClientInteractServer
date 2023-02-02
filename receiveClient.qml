import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import an.qt.myUdpClient 1.0
import QtQuick.Window 2.2
import Qt.labs.settings 1.0
Window {

    //property var test: udpclient;

//    Server {
//        id: server
//    }
    visible: false
    x:200
    y:300
    width: 400
    height: 150
    Page{
//        UdpClient{
//            id:udpclient;
//            onTriggerClient: {
//                receive.text = temp;
//            }
//        }
        header: ToolBar{
            RowLayout{
                anchors.fill: parent
                Text{
                    text: qsTr("接收云台数据Client")
                    font.pointSize: 20
                    horizontalAlignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                }
            }
        }

        GridLayout{
            anchors.centerIn: parent
            rows:5;
            rowSpacing: 5;
            columns: 2;
            columnSpacing: 5;


            Button{
                text:qsTr("server端发送数据为");
                Layout.alignment:Qt.AlignCenter
                highlighted: true
                onClicked: {

                }
            }
            Text {
                id:receive
            }
        }
    }
    Component.onDestruction: {

    }

}
