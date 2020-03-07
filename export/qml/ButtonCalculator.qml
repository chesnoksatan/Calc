import QtQuick 2.0
import QtQuick.Controls 2.3

Button {
    id: control

    property alias color: bcg.color

    implicitHeight: 0

    contentItem: Text {
        text: control.text

        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: (control.height - 2) * 0.3

        color: "#1b1c1d"
    }

    background: Rectangle {
        id: bcg
        border.color: "DarkGray"
    }
}
