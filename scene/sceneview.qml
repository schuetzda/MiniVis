import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts

TreeView {
    id: sceneView
    model: sceneTreeModel
    implicitHeight: parent.height
    implicitWidth: parent.width
    topMargin: 5

    property var selectedIndex: null

    delegate: Item {
        id: treeItem
        implicitWidth: sceneView.width
        implicitHeight: 30

        Rectangle {
            anchors.fill: parent
            color: sceneView.selectedIndex === model.index ? "#444" : "transparent"
            Row {
                leftPadding: 5
                anchors.verticalCenter: parent.verticalCenter

                Image {
                    source: icon
                    width: 24
                    height: 24
                }

                Text {
                    text: model.display
                    color: "white"
                    font.pixelSize: 18
                    font.bold: true
                }
            }
        }
        MouseArea {
            id: clickArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: (mouse)=> {
                sceneView.selectedIndex = model.index
                const mouseYOffset = 5; //Horizontal offset between ContextMenu and mouse position
                if (mouse.button === Qt.RightButton) {
                    contextMenu.popup(mouseX, mouseY+ mouseYOffset)
                }
            }
        }
        Menu {
            id: contextMenu
        MenuItem {
            text: "Add Node"
            onTriggered: {
                console.log("Add Node")
            }
        }
        MenuItem {
            text: "Delete"
            onTriggered: {
                console.log("Delete")
            }
        }
        }
    }
}
