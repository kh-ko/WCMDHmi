import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import FontManager 1.0
import QmlEnumDef 1.0
import QtGraphicalEffects 1.0

Item {
    signal signalChangeText(string value)

    property alias  pixelSize       : textContent.font.pixelSize
    property bool   isHighlight     : false
    property color  bgColor         : "#2F2F2F"
    property bool   isLocaleStyle   : true
    property bool   isDisable       : false
    property int    fixedN          : 0
    property int    maxLength       : 15
    property string labelText       : ""
    property alias  textValue       : textContent.text
    property alias  postfix         : textPostfix.text
    property alias  textHAlign      : textContent.horizontalAlignment
    property int    textInputType
    property var    reservedValue   : ""

    id: control

    width : 100
    height: 100

    Rectangle{
        id :bg
        color: control.bgColor
        radius: 20
        border.width: 0
        anchors.fill: parent
        visible: false
    }

    InnerShadow{
        anchors.fill: bg
        horizontalOffset: 5
        verticalOffset: 5
        radius: 5.0
        samples: 17
        color: "#59000000"
        source: bg
        cached: true

        visible: !control.isDisable
    }

    Rectangle{
        id :bgShadow
        anchors.fill: bg
        color: "#20000000"
        radius: 20
        border.width: 0

        //visible: !control.isDisable
    }

    Text {
        id: textCover

        anchors.fill : textContent

        horizontalAlignment : textContent.horizontalAlignment
        verticalAlignment   : textContent.verticalAlignment
        elide               : textContent.elide
        wrapMode            : textContent.wrapMode

        color               : textContent.color
        font.family         : textContent.font.family
        font.pixelSize      : textContent.font.pixelSize
        fontSizeMode        : textContent.fontSizeMode

        visible: textInputType === QmlEnumDef.PASSWD_MODE ? true : false

        text : "********************".slice(20 - textContent.text.length)
    }

    Text {
        id: textContent

        anchors.right: textPostfix.left
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        verticalAlignment   : Text.AlignVCenter
        elide               : Text.ElideRight
        wrapMode            : Text.NoWrap

        color           : control.isDisable? "#ACACAC" : isHighlight ? "#0085FF" : "#ffffff"
        font.family     : FontManager.nanumGothicName
        font.pixelSize  : 25
        fontSizeMode    : Text.FixedSize

        visible: textInputType === QmlEnumDef.PASSWD_MODE ? false : true

        text : "test"
    }

    Text {
        id: textPostfix

        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        verticalAlignment   : Text.AlignVCenter
        horizontalAlignment : Text.AlignRight
        elide               : Text.ElideRight
        wrapMode            : Text.NoWrap

        color           : textContent.color
        font.family     : textContent.font.family
        font.pixelSize  : textContent.font.pixelSize
        fontSizeMode    : textContent.fontSizeMode

        text : ""
    }

    MouseArea
    {
        anchors.fill : parent

        onClicked: {
            if(control.isDisable)
                return;

            ViewManager.keypad.showKeypad(control)
        }
    }

    function getTextValue(){
        return textContent.text;
    }

    function inputTextValue(value)
    {
        control.signalChangeText(value);
    }

}

