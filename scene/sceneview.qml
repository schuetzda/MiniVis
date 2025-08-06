import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Layouts

TreeView {
    id: sceneView
    model: sceneTreeModel
    implicitHeight: parent.height
    implicitWidth: parent.width

    delegate: Item {
        id:treeItem
        implicitWidth: parent.width
        implicitHeight: 30
        Row {
            anchors.verticalCenter: parent.verticalCenter
            spacing: 5
            Image {
                source: icon
                width: 24
                height: 24
            }

            Text {
                text: model.display
                color: "white"
                font.pixelSize: 20
                font.bold: true
            }
        }
    }
}
