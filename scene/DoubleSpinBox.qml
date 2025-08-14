import QtQuick
import QtQuick.Controls

SpinBox {
    id: doubleSpinBox
    from: decimalToInt(-10000)
    to: decimalToInt(10000)
    editable: true
    stepSize: realStepSize * decimalFactor

    property int decimals: 2
    readonly property int decimalFactor: Math.pow(10, decimals)
    property real realValue: 0
    property real realStepSize: 1
    property bool internalChange: false

    function decimalToInt(decimal) {
        return decimal * decimalFactor
    }

    function roundDecimal(value) {
        let factor = Math.pow(10, decimals)
        return Math.round(value * factor) / factor
    }

    value: roundDecimal(realValue) * decimalFactor

    onValueChanged: {
        if (!internalChange) {
            realValue = value / decimalFactor
        }
        internalChange = false
    }
    onActiveFocusChanged: isActive => {
        if (!isActive) {
            realValue = value / decimalFactor
        }
    }

    Keys.onReturnPressed: {
        realValue = value / decimalFactor
        doubleSpinBox.focus = false
        valueChanged()
    }

    validator: DoubleValidator {
        bottom: Math.min(doubleSpinBox.from, doubleSpinBox.to)
        top: Math.max(doubleSpinBox.from, doubleSpinBox.to)
        decimals: doubleSpinBox.decimals
        notation: DoubleValidator.StandardNotation
    }

    textFromValue: function (value, locale) {
        return (value / decimalFactor).toLocaleString(locale, 'f',
                                                      doubleSpinBox.decimals)
    }

    valueFromText: function (text, locale) {
        return Math.round(Number.fromLocaleString(locale, text) * decimalFactor)
    }
}
