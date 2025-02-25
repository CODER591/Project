import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12
import Qt.labs.settings 1.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.11


	MainPageForm {
		id: window
		Layout.minimumWidth: 800
        Layout.minimumHeight: 480
        Layout.preferredWidth: 768
        Layout.preferredHeight: 480
		background: Rectangle {
        color: backGroundColor


    }

	    Connections{
        target: guiManager
        onMessageRing: {
			messageSound.play()
        }
		onRequestRing: {
			friendSound.play()
		}
    }


    FriendListDelegateModel {
        id: friendModel
        visualModel.model: guiManager.friend_model
    }

    MessageListDelegateModel {
        id: messageModel
        visualModel.model: guiManager.message_model
    }

    FriendRequestListDelegateModel {
        id: friendRequestModel
        visualModel.model: guiManager.friend_request_model
    }

    Component {
        id: highlightBar
        Rectangle {
			property alias highlightRect: highlightRect
			id: highlightRect
            width: friendList.width; height: 40
            color: friendMouseAreaColor
            y: friendList.currentItem.y;
        }
    }

	Connections{
        target: guiManager
        onShowHighlighter: {
			highlightRect.color = to_show ? friendMouseAreaColor :  "trasparent" //FIXME:
        }
    }

    friendList.focus: true
    friendList.highlight: highlightBar
    friendList.highlightFollowsCurrentItem: false

    friendList.model: friendModel.visualModel

    messageList.model: messageModel.visualModel
    messageList.spacing: 10

    friendRequestList.model: friendRequestModel.visualModel

    findButton.onClicked: {
        guiManager.AddFriendRequest(findUserField.text)
        findUserField.text = ""
    }

	menuButton.onClicked: {
		drawer.open()
		}

	friendReqMA.onClicked: {
		 friendRequestDialog.open()
		 drawer.close()
		 }

	editProfileMA.onClicked: {
		editProfileMenu.open()
		}
								

	settingsMA.onClicked: {
		settingsMenu.open()
		}
	logoutMA.onClicked: {
			guiManager.LogOut()
			drawer.close()
			stackView.pop()
		}

    messageField.onEditingFinished: {
        if(messageField.text != "") {
            guiManager.SendMessage(messageField.text)
            messageField.text = "";
        }
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
