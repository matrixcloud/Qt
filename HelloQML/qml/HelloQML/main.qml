import QtQuick 2.0
import QtMultimedia 5.0
import QtTest 1.0

Rectangle {
    width: 360
    height: 360
    color: "#a83e3e"
    border.color: "#2891e2"
    Text {
        id:text1
        text: "<h2>Hello world!</h2>"
        color:"darkgreen"
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }

        TextInput {
            id: textInput1
            x: 145
            y: 101
            width: 80
            height: 20
            text: qsTr(text1.text)
            font.pixelSize: 12
        }
    }
}
