import QtQuick
import QtQuick.Controls

SpinBox {
    id: doubleSpinBox
    value: 0
    from: decimalToInt(-1000)
    to: decimalToInt(1000)
    editable: true
    stepSize: realStepSize*decimalFactor

    property int decimals: 2
    readonly property int decimalFactor: Math.pow(10, decimals)
    property real realValue: value / decimalFactor
    property real realStepSize: 0.1

    function decimalToInt(decimal) {
        return decimal * decimalFactor
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
