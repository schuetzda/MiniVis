import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: sceneViewContainer

    width: (Layout.preferredWidth
            !== undefined) ? Layout.preferredWidth : (parent ? parent.width : 0)
    height: (Layout.preferredHeight
             !== undefined) ? Layout.preferredHeight : (parent ? parent.height : 0)

    property color color: "white"
    property color propertiesColor: "white"

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
            color: sceneViewContainer.color

            //Handle right clicks that are not directly on a sceneItem (Left clicks are handled by the TapHandler)
            MouseArea {
                id: sceneViewClickArea
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onClicked: mouse => {
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
                anchors.fill: parent

                delegate: Item {
                    id: sceneItem
                    implicitWidth: sceneView.width
                    implicitHeight: 30
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
                    //Handle mouse click on an sceneItem
                    MouseArea {
                        id: sceneItemClickArea
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onClicked: mouse => {
                                       sceneViewContainer.selectedIndex = model.index
                                       sceneViewContainer.selectedRow = row
                                       propertiesContainer.showPropertiesContainer(
                                            row)
                                       if (mouse.button === Qt.RightButton) {
                                           contextMenu.deleteEnabled = model.type !== 2
                                           const mouseYInSceneView = sceneItem.implicitHeight
                                           * row + mouse.y
                                           contextMenu.popup(mouse.x,
                                                             mouseYInSceneView)
                                       }
                                   }
                    }
                }
                // Handle mouse click not directly on a scene item
                TapHandler {
                    target: sceneView.contentItem
                    onTapped: function (event) {
                        sceneViewContainer.selectedIndex = -1
                        propertiesContainer.hidePropertiesContainer()
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
                        sceneViewContainer.selectedIndex = -1
                        propertiesContainer.hidePropertiesContainer()
                    }
                }
            }
        }
        Rectangle {
            id: propertiesContainer
            SplitView.preferredHeight: 0
            SplitView.fillWidth: true
            visible: false
            color: sceneViewContainer.propertiesColor
            property int containerHeight: 400

            function showPropertiesContainer(row) {
                if (!visible) {
                    propertiesContainer.SplitView.preferredHeight = containerHeight
                    propertiesContainer.height = containerHeight
                    propertiesSplitView.splitDelegateInstance.height = 3
                    propertiesSplitView.splitDelegateInstance.implicitHeight = 3
                    propertiesContainer.visible = true
                }
                matrixView.changeModel(sceneView.model.getMatrix(row))
            }
            function hidePropertiesContainer(model) {
                if (visible) {
                    containerHeight = propertiesContainer.SplitView.preferredHeight
                    propertiesSplitView.splitDelegateInstance.height = 0
                    propertiesSplitView.splitDelegateInstance.implicitHeight = 0
                    propertiesContainer.visible = false
                }
            }

            MatrixView {
                id: matrixView
            }
        }
    }
}
