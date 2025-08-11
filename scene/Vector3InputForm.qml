import QtQuick
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

Item {
    id: vector3InputForm
    property real xValue: 0
    property real yValue: 0
    property real zValue: 0
    property string label: ""

    ColumnLayout {
        spacing: 4

        Label {
            text: label
            color: "white"
            font.pixelSize: 14
            font.bold: false
            Layout.preferredWidth: 70
        }
        DoubleSpinBox {
            id: xTextField
            realValue: xValue
            decimals: 2
            Layout.preferredWidth: 90
        }
        DoubleSpinBox {
            id: yTextField
            realValue: yValue
            decimals: 2
            Layout.preferredWidth: 90
        }
        DoubleSpinBox {
            id: zTextField
            realValue: zValue
            decimals: 2
            Layout.preferredWidth: 90
        }
    }
}
