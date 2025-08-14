import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: matrixView
    property var model: null

    onModelChanged: {

        var activeSpinBox = getActiveSpinBox()
        if (activeSpinBox) {
            activeSpinBox.focus = false
            activeSpinBox.editable = false
        }
        if (model) {
            Qt.callLater(function () {
                x0TextField.changeValue(model.element(0, 0))
                y0TextField.changeValue(model.element(1, 0))
                z0TextField.changeValue(model.element(2, 0))

                x1TextField.changeValue(model.element(0, 1))
                y1TextField.changeValue(model.element(1, 1))
                z1TextField.changeValue(model.element(2, 1))

                x2TextField.changeValue(model.element(0, 2))
                y2TextField.changeValue(model.element(1, 2))
                z2TextField.changeValue(model.element(2, 2))
            })
        }
        if (activeSpinBox) {
            activeSpinBox.focus = true
            activeSpinBox.editable = true
        }
    }

    function getActiveSpinBox() {
        if (x0TextField.activeFocus)
            return x0TextField
        if (y0TextField.activeFocus)
            return y0TextField
        if (z0TextField.activeFocus)
            return z0TextField

        if (x1TextField.activeFocus)
            return x1TextField
        if (y1TextField.activeFocus)
            return y1TextField
        if (z1TextField.activeFocus)
            return z1TextField

        if (x2TextField.activeFocus)
            return x2TextField
        if (y2TextField.activeFocus)
            return y2TextField
        if (z2TextField.activeFocus)
            return z2TextField
        return null
    }

    function changeModel(newModel) {
        //Set the model first to null to reset the SpinBox elements
        model = null
        model = newModel
    }

    Row {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 8
        layoutDirection: Qt.LeftToRight

        ColumnLayout {
            spacing: 4

            Label {
                text: "Transform"
                color: "white"
                font.pixelSize: 14
                font.bold: false
                Layout.preferredWidth: 70
            }
            DoubleSpinBox {
                id: x0TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(0, 0, realValue)
                }
            }
            DoubleSpinBox {
                id: y0TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(1, 0, realValue)
                }
            }
            DoubleSpinBox {
                id: z0TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(2, 0, realValue)
                }
            }
        }
        ColumnLayout {
            spacing: 4

            Label {
                text: "Rotation"
                color: "white"
                font.pixelSize: 14
                font.bold: false
                Layout.preferredWidth: 70
            }
            DoubleSpinBox {
                id: x1TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(0, 1, realValue)
                }
            }
            DoubleSpinBox {
                id: y1TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(1, 1, realValue)
                }
            }
            DoubleSpinBox {
                id: z1TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(2, 1, realValue)
                }
            }
        }
        ColumnLayout {
            spacing: 4

            Label {
                text: "Scale"
                color: "white"
                font.pixelSize: 14
                font.bold: false
                Layout.preferredWidth: 70
            }
            DoubleSpinBox {
                id: x2TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(0, 2, realValue)
                }
            }
            DoubleSpinBox {
                id: y2TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(1, 2, realValue)
                }
            }
            DoubleSpinBox {
                id: z2TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    if (model)
                        matrixView.model.setElement(2, 2, realValue)
                }
            }
        }
    }
}
