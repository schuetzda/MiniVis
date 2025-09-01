import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Controls.Basic 6.9
import QtQuick.Layouts 6.9
import QtQuick.Dialogs 6.9

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
                                   outerContextMenu.popup(mouse.x, mouse.y)
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
                    property bool editing: false

                    Rectangle {
                        anchors.fill: parent
                        color: sceneViewContainer.selectedIndex
                               === model.index ? "#444" : "transparent"

                        // Color changed => col
                        onColorChanged: {
                            if (sceneViewContainer.selectedIndex !== model.index) {
                                editing = false
                            }
                        }

                        Row {
                            leftPadding: 5
                            anchors.verticalCenter: parent.verticalCenter

                            Image {
                                source: icon
                                width: 24
                                height: 24
                            }

                            Loader {
                                sourceComponent: sceneItem.editing ? editNodeComponent : viewNodeComponent
                            }

                            Component {
                                id: viewNodeComponent
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: model.display
                                    color: "white"
                                    font.pixelSize: 18
                                    font.bold: true
                                }
                            }

                            Component {
                                id: editNodeComponent
                                TextField {
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: model.display
                                    font.pixelSize: 18
                                    font.bold: true
                                    focus: true

                                    Component.onCompleted: {
                                        forceActiveFocus()
                                        selectAll()
                                    }

                                    Keys.onReturnPressed: {
                                        sceneTreeModel.setData(
                                                    sceneView.model.index(row,
                                                                          0),
                                                    text)
                                        sceneItem.editing = false
                                    }
                                    Keys.onEscapePressed: {
                                        sceneItem.editing = false
                                    }

                                    onEditingFinished: sceneItem.editing = false
                                }
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
                                           itemContextMenu.deleteEnabled = model.type
                                           !== 2 // Camera can't be deleted
                                           itemContextMenu.popup(mouse.x,
                                                                 mouse.y)
                                       }
                                   }
                    }
                    Menu {
                        id: itemContextMenu
                        property bool deleteEnabled: true
                        Menu {
                            title: "Add Node:"
                            MenuItem {
                                text: "Model..."
                                onTriggered: {
                                    fileDialog.open()
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
                            text: "Change Name"
                            onTriggered: {
                                sceneItem.editing = true
                            }
                        }

                        MenuItem {
                            text: "Delete"
                            enabled: itemContextMenu.deleteEnabled
                            onTriggered: {
                                sceneTreeModel.removeNode(
                                            sceneViewContainer.selectedRow)
                                sceneViewContainer.selectedIndex = -1
                                propertiesContainer.hidePropertiesContainer()
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
                id: outerContextMenu
                Menu {
                    title: "Add Node:"
                    MenuItem {
                        text: "Model..."
                        onTriggered: {
                            fileDialog.open()
                        }
                    }
                    MenuItem {
                        text: "Light"
                        onTriggered: {
                            sceneTreeModel.addNode(1)
                        }
                    }
                }
            }
            FileDialog {
                id: fileDialog
                title: "Select STL File"
                currentFolder: ""
                nameFilters: ["STL files (*.stl)"]

                onAccepted: {
                    if (selectedFile) {
                        sceneTreeModel.addModel(selectedFile)
                        console.log("Selected file:", selectedFile)
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
