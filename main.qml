import QtQuick 2.7
import QtQml 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Unipg Racing Team")

    ListView {
        id: listView
        anchors.fill: parent
        header: headerComponent
        model: dataModel
        delegate: Item {
            id: dataDelegate
            width: parent.width; height: 50

            ColumnLayout {

                Text {
                    id: tel_name
                    text: name
                    font.bold: true
                    font.family: "Ubuntu-Regular"
                    font.pixelSize: 20
                    color: "#6f6f6f"
                }
                Text {
                    text: value
                    font.family: "Ubuntu-Regular"
                    font.pixelSize: 15
                    anchors.left: tel_name.right
                    anchors.leftMargin: 10
                }
            }
        }
    }

    Component {
        id: headerComponent
        Rectangle {
            width: parent.width; height: 80
            color: "#417690"
            Text {
                anchors.centerIn: parent
                text: "<b>DATA LIST</b>"
                font.family: "Ubuntu-Regular"
                font.pixelSize: 25
                color: "#ffc"
            }
        }
    }
}

