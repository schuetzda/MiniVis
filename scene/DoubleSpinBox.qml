import QtQuick
import QtQuick.Controls

SpinBox {
    id: doubleSpinBox
    value: 0
    from: decimalToInt(-1000)
    to: decimalToInt(1000)
    editable: true
    stepSize: decimalFactor

    property int decimals: 2
    property real realValue: value / 100
    readonly property int decimalFactor: Math.pow(10, decimals)

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
        return Number(value / decimalFactor).toLocaleString(Qt.locale("en_US"), 'f',
                                                            doubleSpinBox.decimals)
    }
    valueFromText: function (text, locale) {
        return Math.round(Number.fromLocaleString(Qt.locale("en_US"), text) * decimalFactor)
    }
}
