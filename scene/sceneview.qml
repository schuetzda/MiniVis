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

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical
        id: propertiesSplitView
        property var splitDelegateInstance
        Component {
            id: propertiesSplitDelegate
            Rectangle {
                implicitHeight: 0
                color: SplitHandle.pressed ? "#3498db" : (SplitHandle.hovered ? Qt.lighter("#3498db", 0.7) : "darkgray")

                Component.onCompleted: {
                    propertiesSplitView.splitDelegateInstance = this
                }
            }
        }

        handle: propertiesSplitDelegate

        Rectangle {

            id: treeViewContainer
            SplitView.fillHeight: true
            SplitView.fillWidth: true
            color: "green"

            MouseArea {
                id: sceneViewClickArea
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                z: 1
                onClicked: mouse => {
                               sceneViewContainer.selectedIndex = -1
                               propertiesContainer.hidePropertiesContainer()
                               if (mouse.button === Qt.RightButton) {
                                   contextMenu.deleteEnabled = false
                                   contextMenu.popup(mouse.x, mouse.y)
                               }
                           }
            }

            TreeView {
                id: sceneView
                model: sceneTreeModel
                topMargin: 5
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 30 * 3
                z: 1 //Put in front of sceneViewClickArea

                delegate: Item {
                    id: sceneItem
                    implicitWidth: sceneView.width
                    implicitHeight: 30
                    z:2
                    required property int row

                    Rectangle {
                        anchors.fill: parent
                        color: sceneViewContainer.selectedIndex
                               === model.index ? "#444" : "transparent"
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
                                       //Horizontal offset between ContextMenu and mouse position
                                       propertiesContainer.showPropertiesContainer(
                                           1, 1)
                                       if (mouse.button === Qt.RightButton) {
                                           contextMenu.deleteEnabled = model.type !== 2
                                           contextMenu.popup(mouse.x, mouse.y)
                                       }
                                   }
                    }
                }
            }

            Menu {
                id: contextMenu
                property bool deleteEnabled: true
                Menu {
                    title: "Add Node:"
                    MenuItem {
                        text: "Model"
                        onTriggered: {
                            sceneTreeModel.addNode(0)
                        }
                    }
                    MenuItem {
                        text: "Light"
                        onTriggered: {
                            sceneTreeModel.addNode(1)
                        }
                    }
                }
                MenuItem {
                    text: "Delete"
                    enabled: contextMenu.deleteEnabled
                    onTriggered: {
                        sceneTreeModel.removeNode(
                                    sceneViewContainer.selectedRow)
                    }
                }
            }
        }
        Rectangle {
            id: propertiesContainer
            SplitView.preferredHeight: 0
            SplitView.fillWidth: true
            color: "blue"
            visible: false
            property int containerHeight: 400

            function showPropertiesContainer(sceneType, row) {
                if (!visible) {
                    propertiesContainer.SplitView.preferredHeight = containerHeight
                    propertiesContainer.height = containerHeight
                    propertiesSplitView.splitDelegateInstance.height = 3
                    propertiesSplitView.splitDelegateInstance.implicitHeight = 3
                    propertiesContainer.visible = true
                }
            }
            function hidePropertiesContainer() {
                if (visible) {
                    containerHeight = propertiesContainer.SplitView.preferredHeight
                    propertiesSplitView.splitDelegateInstance.height = 0
                    propertiesSplitView.splitDelegateInstance.implicitHeight = 0
                    propertiesContainer.visible = false
                }
            }
        }
    }
}
