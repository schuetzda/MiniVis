import QtQuick

Item {
    id: matrixView
    property var model: null
    Row {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 8
        layoutDirection: Qt.LeftToRight

        Vector3InputForm {
            width: 100
            height: 50
            xValue: model ? model.element(0,0) : 0
            yValue: model ? model.element(1,0) : 0
            zValue: model ? model.element(2,0) : 0
            label: "Location"
        }
        Vector3InputForm {
            width: 100
            height: 50
            xValue: model ? model.element(0,1) : 0
            yValue: model ? model.element(1,1) : 0
            zValue: model ? model.element(2,1) : 0
            label: "Rotation"
        }
        Vector3InputForm {
            width: 100
            height: 50
            xValue: model ? model.element(0,2) : 0
            yValue: model ? model.element(1,2) : 0
            zValue: model ? model.element(2,2) : 0
            label: "Scale"
        }
    }
}
