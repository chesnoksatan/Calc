import QtQuick 2.10
import QtQuick.Window 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4 as OLD

ApplicationWindow {
    id: root

    visible: true

    width: 400
    height: 600

    color: "#f3e3e3e3"

    minimumWidth: 400
    minimumHeight: 600

    title: qsTr("Калькулятор")

    readonly property var calculatorRegExp: new RegExp(/^(\d+(\.\d+)?)(?:([-+/*])(\d+(\.\d+)?)){1}$/)

    onClosing: FormController.writeSettings()

    Connections {
        target: FormController

        onSignalUpdateConsole: {setMessage(errorCode, msg)}
    }

    function setMessage(errorCode, msg) {
        var date = new Date();
        var currentTime = '[' + date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + "::" + date.getMilliseconds() + "] ";

        switch (errorCode) {
        case 1:
            _console.text = "<h style='color: " + "Green"  +  ";' >" + currentTime + msg + "</h>" + _console.text
            break;
        case 0:
            _console.text = "<h style='color: " + "Blue"  +  ";' >" + currentTime + msg + "</h>" + _console.text
            break;
        case -1:
        case -2:
        case -3:
            _console.text = "<h style='color: " + "Red"  +  ";' >" + currentTime + msg + "</h>" + _console.text
            break;
        default:
            break;
        }
    }

    TextField {
        id: calcArea

        text: ""

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        anchors.rightMargin: 2
        anchors.leftMargin: 2
        anchors.topMargin: 2

        height: parent.height * 3 / 16

        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: root.height * 3 / 32

        validator: RegExpValidator {regExp: calculatorRegExp}

        background: Rectangle {
            color: "Transparent"
            border.color: "DarkGray"
            border.width: 1

            anchors.fill: parent

            radius: 2
        }
    }

    GridLayout {
        id: buttons

        height: root.height / 2

        columnSpacing: 1
        rowSpacing: 1

        anchors.rightMargin: 2
        anchors.leftMargin: 2
        anchors.bottomMargin: 2
        anchors.topMargin: 2

        anchors.top: calcArea.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        columns: 4
        rows: 5

        ButtonCalculator {
            text: qsTr("/");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("*");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("+");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("-");
            Layout.fillHeight: true;
            Layout.maximumWidth: root.width / 4
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("7");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("8");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("9");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }

        ButtonCalculator {
            id: evalt
            text: qsTr("=");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            Layout.rowSpan: 4;
            Layout.maximumWidth: root.width / 4;
            onClicked: {
                if (calculatorRegExp.test(calcArea.text)) {
                    setMessage(1, "Вы ввели выражение: " + calcArea.text);
                    FormController.getRequest(calcArea.text);
                    calcArea.text = "";
                }
                else {
                    setMessage(-3, "Вы ввели неправильное выражение");
                    calcArea.text = "";
                }

                enabled = false;
                enableBtn.start();
            }
        }

        ButtonCalculator {
            text: qsTr("4");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("5");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("6");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }

        ButtonCalculator {
            text: qsTr("1");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("2");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("3");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }

        ButtonCalculator {
            text: qsTr(".");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("0");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3d6d6d6" : "#f3eeeeee";
            onClicked: calcArea.text += text;
        }
        ButtonCalculator {
            text: qsTr("C");
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            color: pressed ? "#f3bdbebd" : "#f3d3d3d3";
            onClicked: calcArea.text = "";
        }
    }

    Timer {
        id: enableBtn
        repeat: false
        running: false
        interval: 500
        onTriggered: {evalt.enabled = true}
    }

    RowLayout {
        id: delayRow
        anchors.topMargin: 2

        anchors.rightMargin: 2
        anchors.leftMargin: 2
        anchors.bottomMargin: 2

        anchors.top: buttons.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Label {text: qsTr("Задержка") ;Layout.maximumHeight: 25}
        OLD.SpinBox {id: delay; Layout.fillWidth: true; minimumValue: 1}
        Button {
            text: qsTr("Установить");
            Layout.maximumHeight: 25;
            Layout.minimumHeight: 25;
            background: Rectangle {
                border.color: "DarkGray";
                color: parent.pressed ? "#d6d6d6" : "#eeeeee"
            }
            onClicked: FormController.setDelay(delay.value);
        }
    }

    RowLayout {
        id: queueRequestsRow
        anchors.topMargin: 2
        anchors.rightMargin: 2
        anchors.leftMargin: 2
        anchors.bottomMargin: 2

        anchors.top: delayRow.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Label {text: qsTr("QueueRequests:") ;Layout.maximumHeight: 25}
        Label {objectName: "QueueRequests"; horizontalAlignment: Text.AlignHCenter; Layout.fillWidth: true; Layout.maximumHeight: 25; text: "0";}

        Label {text: qsTr("QueueResults:") ; Layout.minimumWidth: 127;Layout.maximumHeight: 25}
        Label {objectName: "QueueResults"; horizontalAlignment: Text.AlignHCenter; Layout.fillWidth: true; Layout.maximumHeight: 25; text: "0";}
    }

    Rectangle {
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.rightMargin: 2
        anchors.leftMargin: 2

        anchors.top: queueRequestsRow.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        color: "Transparent"
        border.color: "DarkGray"
        border.width: 1

        radius: 2

        Flickable {
            id: flick

            anchors.fill: parent

            interactive: true
            clip: true

            function ensureVisible(r) {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                    contentX = r.x+r.width-width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                    contentY = r.y+r.height-height;
            }

            TextEdit {
                id: _console

                anchors.fill: parent

                anchors.topMargin: 2
                anchors.leftMargin: 5

                height: root.height / 12

                font.pointSize: 10
                readOnly: true

                selectByMouse: true

                textFormat: TextEdit.RichText
            }
        }

        ScrollBar {}
    }
}
