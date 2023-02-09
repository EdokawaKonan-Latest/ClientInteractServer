import QtQuick 2.0
import QtQuick.Controls 2.2

Window {


    visible: true
    x:700
    y:300
    width: 400
    height: 150
    UdpServer{
        id:udpserver;
        onTriggerServer: {
            receive.text = temp;
            udpclient.slotServerSend(temp)
        }
    }


    Page{


        header: ToolBar{
            RowLayout{
                anchors.fill: parent
                Text{
                    text: qsTr("接收client数据Server")
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

            //接收客服端数据
            Button{
                text:qsTr("从客户端接收数据为");
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
    Component.onCompleted: {
    }
}
