import QtQuick

Item {
    id: matrixView
    property var model: null

    onModelChanged: {
        defocus()
        updateAllVectors()
    }

    function updateAllVectors() {
        if (model)
        {
            locationVector.updateVectorValue(model.element(0, 0),
                                             model.element(1, 0),
                                             model.element(2, 0))
            rotationVector.updateVectorValue(model.element(0, 1),
                                             model.element(1, 1),
                                             model.element(2, 1))
            scaleVector.updateVectorValue(model.element(0, 2),
                                          model.element(1, 2),
                                          model.element(2, 2))
        }
    }

    function defocus()
    {
        locationVector.defocus()
        rotationVector.defocus()
        scaleVector.defocus()
    }

    Row {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 8
        layoutDirection: Qt.LeftToRight

        Vector3InputForm {
            id: locationVector
            width: 100
            height: 50
            onVectorInputChanged: {
                if (model) {
                    model.setElement(0, 0, xValue)
                    model.setElement(1, 0, yValue)
                    model.setElement(2, 0, zValue)
                }
            }

            label: "Location"
        }
        Vector3InputForm {
            id: rotationVector
            width: 100
            height: 50
            label: "Rotation"
            onVectorInputChanged: {
                if (model) {
                    model.setElement(0, 1, xValue)
                    model.setElement(1, 1, yValue)
                    model.setElement(2, 1, zValue)
                }
            }
        }
        Vector3InputForm {
            id: scaleVector
            width: 100
            height: 50
            label: "Scale"
            onVectorInputChanged: {
                if (model) {
                    model.setElement(0, 2, xValue)
                    model.setElement(1, 2, yValue)
                    model.setElement(2, 2, zValue)
                }
            }
        }
    }
}
