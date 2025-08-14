import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: matrixView
    property var model: null

    onModelChanged: {
        if (model) {
            x0TextField.focus = false
            x0TextField.focusChanged(false)
            x0TextField.changeValue(model.element(0, 0))
            y0TextField.changeValue(model.element(1, 0))
            z0TextField.changeValue(model.element(2, 0))

            x1TextField.changeValue(model.element(0, 1))
            y1TextField.changeValue(model.element(1, 1))
            z1TextField.changeValue(model.element(2, 1))

            x2TextField.changeValue(model.element(0, 2))
            y2TextField.changeValue(model.element(1, 2))
            z2TextField.changeValue(model.element(2, 2))
        }
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
                    matrixView.model.setElement(0, 0, realValue)
                }
            }
            DoubleSpinBox {
                id: y0TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    matrixView.model.setElement(1, 0, realValue)
                }
            }
            DoubleSpinBox {
                id: z0TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
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
                    matrixView.model.setElement(0, 1, realValue)
                }
            }
            DoubleSpinBox {
                id: y1TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    matrixView.model.setElement(1, 1, realValue)
                }
            }
            DoubleSpinBox {
                id: z1TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
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
                    matrixView.model.setElement(0, 2, realValue)
                }
            }
            DoubleSpinBox {
                id: y2TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    matrixView.model.setElement(1, 2, realValue)
                }
            }
            DoubleSpinBox {
                id: z2TextField
                decimals: 1
                Layout.preferredWidth: 90
                onRealValueChanged: {
                    matrixView.model.setElement(2, 2, realValue)
                }
            }
        }
    }
}
