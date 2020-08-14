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

    property alias bgColor : inputText.bgColor
    property alias textValue : inputText.textValue
    property alias fontSize : inputText.textFontSize
    property alias font : inputText.textFont
    property alias textHAlign : inputText.textHAlign
    property alias textVAlign : inputText.textVAlign
    property alias postfix : inputText.postfix
    property alias maxLength : inputText.maxLength

    property string labelText : ""
    property int    inputWidth : -1

    signal signalChangeText(string value)

    id : control
    width: 100
    height: 100

    UiLabelNormalSystemText{
        visible: inputWidth === -1 ? false : true
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        textValue: labelText
    }

    UiInput
    {
        id : inputText
        width: inputWidth === -1 ? parent.width : inputWidth
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        textHAlign: Text.AlignLeft
        textVAlign: Text.AlignVCenter
        textFont : FontManager.nanumGothicBName
        textFontSize: 20
        textInputType : EnumDefine.IP_MODE
        maxLength: 15

        onSignalChangeText: {
            control.signalChangeText(value)
        }
    }
}
