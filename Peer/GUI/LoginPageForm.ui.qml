import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
    id: loginPage

    property alias buttonLogIn: buttonLogIn
    property alias buttonRegister: buttonRegister
    property alias loginUsername: loginUsername

    background: Rectangle {
        color: backGroundColor
    }

    Rectangle {
        id: iconRect
        width: parent.width
        height: parent.height / 3
        color: backGroundColor

        Text {
            id: icontext
            width: 390
            height: 160
            text: qsTr("MesX")
            anchors.centerIn: parent
            font.pointSize: 110
            font.family: "Verdana"
            color: mainAppColor
        }
    }

    ColumnLayout {
        id: columnLogin
        width: 320
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: iconRect.bottom
        spacing: 10

        TextField {
            id: loginUsername
            width: parent.width
            placeholderText: qsTr("User name")
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 20
            background: Rectangle {
                implicitWidth: columnLogin.width
                implicitHeight: 50
                radius: implicitHeight / 2
                color: "transparent"

                Text {
                    text: "\uf007"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        TextField {
            id: loginPassword
            width: parent.width
            placeholderText: qsTr("Password")
            color: mainTextCOlor
            font.pointSize: 14
            font.family: "fontawesome"
            leftPadding: 20
            echoMode: TextInput.Password
            background: Rectangle {
                implicitWidth: columnLogin.width
                implicitHeight: 50
                color: "transparent"
                Text {
                    text: "\uf023"
                    font.pointSize: 14
                    font.family: "fontawesome"
                    color: mainAppColor
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    width: parent.width - 10
                    height: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    color: mainAppColor
                }
            }
        }

        Button {
            id: buttonLogIn
            implicitWidth: parent.width
            text: qsTr("Log In")
            font.pointSize: 16

            contentItem: Text {
                font: buttonLogIn.font
                color: "#ffffff"
                text: "Log In"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: mainAppColor
                opacity: buttonLogIn.down ? 0.7 : 1
                radius: height / 3
                border.color: mainAppColor
            }
        }

        Button {
            id: buttonRegister
            implicitWidth: parent.width
            text: qsTr("Register")
            Layout.fillWidth: false
            font.pointSize: 16

            contentItem: Text {
                text: buttonRegister.text
                font: buttonRegister.font
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 50
                color: "transparent" //"#6fda9c"
                opacity: buttonRegister.down ? 0.7 : 1
                radius: height / 3
                border.color: mainAppColor
            }
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/