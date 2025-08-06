import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: sceneViewContainer
    width: parent.width
    height: parent.height

    property int selectedIndex: -1
    property int selectedRow: -1

    MouseArea {
        id: sceneViewClickArea
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        z: -1
        onClicked: mouse => {
                       const mouseYOffset = 5
                       //Horizontal offset between ContextMenu and mouse position
                       console.log("Click")
                       if (mouse.button === Qt.RightButton) {
                           selectedIndex = -1
                           contextMenu.deleteEnabled = false
                           contextMenu.popup(mouseX, mouseY + mouseYOffset)
                       }
                   }
    }

    TreeView {
        id: sceneView
        model: sceneTreeModel
        implicitHeight: parent.height
        implicitWidth: parent.width
        topMargin: 5

        delegate: Item {
            id: sceneItem
            implicitWidth: sceneView.width
            implicitHeight: 30

            required property int row

            Rectangle {
                anchors.fill: parent
                color: sceneViewContainer.selectedIndex === model.index ? "#444" : "transparent"
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
                id: sceneItemClickArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: mouse => {
                               sceneViewContainer.selectedIndex = model.index
                               sceneViewContainer.selectedRow = row
                               const mouseYOffset = 5
                               //Horizontal offset between ContextMenu and mouse position
                               if (mouse.button === Qt.RightButton) {
                                   contextMenu.deleteEnabled = model.type !== 2
                                   contextMenu.popup(mouseX,
                                                     mouseY + mouseYOffset)
                               }
                           }
            }
        }
    }

    Menu {
        id: contextMenu
        property bool deleteEnabled: true
        MenuItem {
            text: "Add Node"
            onTriggered: {
                console.log("Add Node")
            }
        }
        MenuItem {
            text: "Delete"
            enabled: contextMenu.deleteEnabled
            onTriggered: {
                sceneTreeModel.removeNode(sceneViewContainer.selectedRow)
            }
        }
    }
}
