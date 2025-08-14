import QtQuick
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

Item {
    id: vector3InputForm
    property real xValue: 0
    property real yValue: 0
    property real zValue: 0
    property string label: ""

    signal vectorInputChanged(var x, var y, var z)

    function defocus() {
        xTextField.focus = false
        yTextField.focus = false
        zTextField.focus = false
    }

    function updateVectorValue(x, y, z) {
        xTextField.internalChange = true
        yTextField.internalChange = true
        zTextField.internalChange = true
        xValue = x
        yValue = y
        zValue = z
        xTextField.realValue = x
        yTextField.realValue = y
        zTextField.realValue = z
    }

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
            decimals: 1
            Layout.preferredWidth: 90
            onValueChanged: {
                vector3InputForm.xValue = realValue
                vectorInputChanged(vector3InputForm.xValue,
                                   vector3InputForm.yValue,
                                   vector3InputForm.zValue)
            }
        }
        DoubleSpinBox {
            id: yTextField
            decimals: 1
            Layout.preferredWidth: 90
            onValueChanged: {
                vector3InputForm.yValue = realValue
                vectorInputChanged(vector3InputForm.xValue,
                                   vector3InputForm.yValue,
                                   vector3InputForm.zValue)
            }
        }
        DoubleSpinBox {
            id: zTextField
            decimals: 1
            Layout.preferredWidth: 90
            onValueChanged: {
                vector3InputForm.zValue = realValue
                vectorInputChanged(vector3InputForm.xValue,
                                   vector3InputForm.yValue,
                                   vector3InputForm.zValue)
            }
        }
    }
}
