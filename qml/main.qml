import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import MiniVis

Rectangle {
    anchors.fill: parent
    Material.theme: Material.Dark
    Material.accent: "#3498db"

    //Main Rectangle covering the whole window
    Rectangle {
        id: mainContainer
        width: parent.width
        height: parent.height
        anchors.fill: parent
        color: "transparent"

        SplitView {
            anchors.fill: parent
            handle: Rectangle {
                id: handleDelegate
                implicitWidth: 3
                color: SplitHandle.pressed ? "#3498db" : (SplitHandle.hovered ? Qt.lighter("#3498db", 0.7) : "darkgray")
            }

            //Left: The rendering window with different tabs and a toolbar to select a current model
            Rectangle {
                id: leftContainer
                SplitView.preferredHeight: parent.height
                SplitView.fillWidth: true
                SplitView.minimumWidth: 150
                color: "transparent"
                anchors.left: parent.left

                ColumnLayout {
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    spacing: 0

                    Rectangle {
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        color: Material.background
                        TabBar {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            id: bar
                            TabButton {
                                text: qsTr("Scene1")
                                width: 70
                            }
                        }
                    }

                    Rectangle {
                        id: renderContainer
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        color: "transparent"

                        Rectangle {
                            id: renderContainerTopBorder
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            width: parent.width
                            color: "darkgray"
                        }

                        RowLayout {
                            anchors.top: renderContainerTopBorder.bottom
                            anchors.left: renderContainer.left
                            anchors.right: renderContainer.right
                            anchors.bottom: renderContainer.bottom
                            spacing: 0
                            Rectangle {
                                id: renderToolbar
                                Layout.fillHeight: true
                                Layout.preferredWidth: 60
                                color: Material.background
                            }
                            Rectangle {
                                id: renderViewport
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "gray"


                                VulkanTextureItem {
                                    id: renderer
                                    registry: ecsRegistry
                                    anchors.fill: parent
                                }
                            }
                        }
                    }
                }
            }

            //Right: The property window for selecting color, export file etc.
            Rectangle {
                id: rightContainer
                SplitView.preferredWidth: 400
                SplitView.minimumWidth: 150
                SplitView.preferredHeight: parent.height

                color: Material.background

                ColumnLayout {
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                    spacing: 0

                    TabBar {
                        id: propertiesBar
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50

                        TabButton {
                            text: qsTr("Scene")
                            Layout.fillWidth: true
                       }
                        TabButton {
                            text: qsTr("Export")
                            Layout.fillWidth: true
                        }
                    }
                    Rectangle {
                        id: propertiesContainer
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: Material.background

                        Rectangle {
                            id: propertiesTopBorder
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            width: parent.width
                            color: "darkgray"
                        }
                        SceneView {
                            anchors.left: parent.left
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            height: parent.height-propertiesTopBorder.height
                            color: Material.background
                            propertiesColor: "#303030"
                        }
                    }
                }
            }
        }
    }
}
