import QtQuick 2.0
import FontManager 1.0
import EnumDefine 1.0
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

    property var    textValue    : "Test"
    property var    maxLength    : 15
    property string labelText    : ""
    property int    inputWidth   : -1

    signal signalChangeText(string value)

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

        textHAlign: Text.AlignLeft
        textInputType : EnumDefine.STRING_MODE

        labelText : control.labelText
        isLocaleStyle: false
        maxLength: control.maxLength
        textValue: control.textValue

        onSignalChangeText: {
            control.signalChangeText(value)
        }
    }
}
