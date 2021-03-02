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

    property alias  isHighlight  : inputText.isHighlight
    property alias  bgColor      : inputText.bgColor
    property alias  isDisable    : inputText.isDisable

    property alias  postfix      : inputText.postfix

    property var    inputType   : QmlEnumDef.INT_MODE
    property string fillZero    : ""
    property bool   isLocaleStyle : true
    property var    numberValue    : 1000
    property var    min
    property var    max
    property string labelText   : ""
    property int    inputWidth  : -1

    signal signalChangeValue(int value)

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
        width: inputWidth === -1 ? parent.width : inputWidth
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        textHAlign: Text.AlignRight
        textInputType : control.inputType //QmlEnumDef.INT_MODE

        labelText : control.labelText
        isLocaleStyle: control.isLocaleStyle
        //textValue: control.isLocaleStyle ? numberValue.toLocaleString(ViewManager.locale, 'f', 0) : fillZero === "" ? numberValue : (fillZero + numberValue).slice(-1 * fillZero.length)
        textValue: fillZero !== ""          ? (fillZero + numberValue).slice(-1 * fillZero.length) :
                   control.isLocaleStyle    ? numberValue.toLocaleString(ViewManager.locale, 'f', 0) : numberValue

        onSignalChangeText: {

            if(value === "")
                value = "0"

            var inputValue = parseInt(value.replace(/,/g,""));

            if(inputValue < min)
                inputValue = min
            else if(inputValue > max)
                inputValue = max

            control.signalChangeValue(inputValue)
        }
    }
}
