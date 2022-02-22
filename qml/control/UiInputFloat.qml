import QtQuick 2.0
import FontManager 1.0
import QmlEnumDef 1.0
import ViewManager 1.0
import "."

Item {

    function getVInputText()
    {
        return inputText;
    }

    property var    isSignedInput : false
    property var    reservedValue : ""
    property alias  isHighlight  : inputText.isHighlight
    property alias  bgColor      : inputText.bgColor
    property alias  isDisable    : inputText.isDisable
    property alias  pixelSize    : inputText.pixelSize
    property alias  postfix      : inputText.postfix
    property int    fixedN       : 1

    property bool   isLocaleStyle: true
    property real    realValue    : 1000
    property var     min
    property var     max
    property string labelText     : ""
    property int    inputWidth    : -1

    signal signalChangeValue(real value)

    id : control
    width: 100
    height: 100

    UiLabelSystem
    {
        id : label
        width: parent.width - inputWidth
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter

        visible: inputWidth === -1 ? false : true
        textValue: labelText
    }

    UiInput
    {
        id : inputText
        width               : inputWidth === -1 ? parent.width : inputWidth
        height              : parent.height
        anchors.top         : parent.top
        anchors.topMargin   : 0
        anchors.bottom      : parent.bottom
        anchors.bottomMargin: 0
        anchors.right       : parent.right
        anchors.rightMargin : 0

        textHAlign      : Text.AlignRight
        textInputType   : control.isSignedInput ? QmlEnumDef.S_FLOAT_MODE : QmlEnumDef.FLOAT_MODE

        reservedValue   : control.reservedValue
        fixedN          : control.fixedN
        labelText       : control.labelText
        isLocaleStyle   : control.isLocaleStyle
        textValue       : (realValue.toLocaleString(ViewManager.locale, 'f', control.fixedN + 1)).slice(0,-1)

        onSignalChangeText: {

            if(value === "")
                value = "0"

            var inputValue = parseFloat(value.replace(/,/g,""));

            if(inputValue < min)
                inputValue = min
            else if(inputValue > max)
                inputValue = max

            control.signalChangeValue(inputValue)
        }
    }
}
