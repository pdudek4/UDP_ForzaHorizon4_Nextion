import QtQuick 2.12
import udp1ds 1.0

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello udp1ds")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }
}
