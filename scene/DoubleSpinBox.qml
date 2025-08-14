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
    property real realValue: roundDecimal(
                                 value / decimalFactor) //This is only used to convert to text, changing this won't change the underlying value
    property real realStepSize: 1

    function decimalToInt(decimal) {
        return decimal * decimalFactor
    }

    function roundDecimal(value) {
        let factor = Math.pow(10, decimals)
        return Math.round(value * factor) / factor
    }

    function changeValue(realValue) {
        value = realValue * decimalFactor
    }
    value: 0

    onValueChanged: {
        realValue = roundDecimal(value / decimalFactor)
    }
    onActiveFocusChanged: isActive => {                          }

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
