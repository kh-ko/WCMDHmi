import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.4
import FontManager 1.0
import ViewManager 1.0
import QmlEnumDef 1.0
import "."

Item {
    property UiInput vinputText : null

    id : control
    visible: false
    anchors.fill: parent

    function showKeypad(vinputText)
    {
        control.vinputText = vinputText
        textLabel.text = vinputText.labelText

        if(control.vinputText.textInputType === QmlEnumDef.INT_MODE)
        {
            virtualTextField.maximumLength = 32767
            virtualTextField.inputMethodHints = Qt.ImhDigitsOnly
            virtualTextField.echoMode = TextInput.Normal
            virtualTextField.validator = null
        }
        else if(control.vinputText.textInputType === QmlEnumDef.PASSWD_MODE)
        {
            virtualTextField.maximumLength = 32767
            virtualTextField.inputMethodHints = Qt.ImhDigitsOnly
            virtualTextField.echoMode = TextInput.Password
            virtualTextField.validator = null
        }
        else if(control.vinputText.textInputType === QmlEnumDef.STRING_MODE)
        {
            virtualTextField.maximumLength = control.vinputText.maxLength
            virtualTextField.inputMethodHints = Qt.ImhNone
            virtualTextField.echoMode = TextInput.Normal
            virtualTextField.validator = null
        }
        if(control.vinputText.textInputType === QmlEnumDef.FLOAT_MODE)
        {
            virtualTextField.maximumLength = 32767
            virtualTextField.inputMethodHints = Qt.ImhDigitsOnly
            virtualTextField.echoMode = TextInput.Normal
            virtualTextField.validator = null
        }
        if(control.vinputText.textInputType === QmlEnumDef.IP_MODE)
        {
            virtualTextField.maximumLength = control.vinputText.maxLength
            virtualTextField.inputMethodHints = Qt.ImhDigitsOnly
            virtualTextField.echoMode = TextInput.Normal
            virtualTextField.validator = ipExpValidator
        }
        if(control.vinputText.textInputType === QmlEnumDef.S_INT_MODE || control.vinputText.textInputType === QmlEnumDef.S_FLOAT_MODE)
        {
            virtualTextField.maximumLength = 32767
            virtualTextField.inputMethodHints = Qt.ImhFormattedNumbersOnly
            virtualTextField.echoMode = TextInput.Normal
            virtualTextField.validator = null
        }

        if(control.vinputText.reservedValue != "")
            virtualTextField.text = control.vinputText.reservedValue;
        else
            virtualTextField.text = control.vinputText.getTextValue();

        control.visible = true;
        virtualTextField.forceActiveFocus();//  .focus = true;
        virtualTextField.selectAll();
    }

    RegExpValidator{
        id : ipExpValidator
        regExp : /^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/
    }

    Rectangle{
        color: "#cc000000"
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent

            onClicked:
            {
                virtualTextField.focus = false
                virtualKeyPad.active = false
                control.visible = false
                control.vinputText = null
            }
        }
    }

    UiButton{
        textValue :qsTr("Cancel")

        width :  140
        height : 80
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.verticalCenter: textLabel.verticalCenter

        onSignalEventClicked: {
            virtualTextField.focus = false
            virtualKeyPad.active = false
            control.visible = false
            control.vinputText = null
        }
    }

    Text {
        id: textLabel
        height: 40
        color: "#ffffff"
        text: qsTr("Text")
        verticalAlignment: Text.AlignVCenter
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.bottom: virtualTextField.top
        anchors.bottomMargin: 40

        font.family: FontManager.nanumGothicBName
        font.pixelSize: 35

    }

    TextField{
        id: virtualTextField
        font.family: FontManager.nanumGothicBName
        font.pixelSize: 35
        height: 50
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        color: "#000000"
        anchors.bottom: virtualKeyPad.top
        anchors.bottomMargin: 40

        Keys.onReleased: {

            if(virtualTextField.text.length > 0 && (control.vinputText.textInputType === QmlEnumDef.INT_MODE || control.vinputText.textInputType === QmlEnumDef.FLOAT_MODE || control.vinputText.textInputType === QmlEnumDef.IP_MODE || control.vinputText.textInputType === QmlEnumDef.S_INT_MODE || control.vinputText.textInputType === QmlEnumDef.S_FLOAT_MODE))
            {

                virtualTextField.text = virtualTextField.text.trim()

                if(control.vinputText.textInputType === QmlEnumDef.INT_MODE || control.vinputText.textInputType === QmlEnumDef.S_INT_MODE)
                {
                    if(virtualTextField.text != "-")
                    {
                        var intValue = parseInt(virtualTextField.text.replace(/,/g,""))

                        if(control.vinputText.isLocaleStyle)
                            virtualTextField.text = intValue.toLocaleString(ViewManager.locale, 'f', 0)
                        else
                            virtualTextField.text = intValue
                    }
                }
                else if(control.vinputText.textInputType === QmlEnumDef.FLOAT_MODE || control.vinputText.textInputType === QmlEnumDef.S_FLOAT_MODE)
                {
                    if(virtualTextField.text != "-")
                    {
                        var dotIdx = virtualTextField.text.indexOf(".")

                        if(dotIdx === - 1)
                        {
                            var numberValue01 = parseInt(virtualTextField.text.replace(/,/g,""))
                            virtualTextField.text = numberValue01.toLocaleString(ViewManager.locale, 'f', 0)
                        }
                        else
                        {
                            var preValue
                            var postValue
                            var valueArray = virtualTextField.text.split(".");

                            if(dotIdx === 0)
                            {
                                preValue = "0.";
                            }
                            else
                            {
                                preValue = valueArray[0].toLocaleString(ViewManager.locale, 'f', 0) + ".";
                            }

                            if(valueArray.length > 1)
                            {
                                postValue = valueArray[1].trim().substr(0, control.vinputText.fixedN)
                            }

                            virtualTextField.text = preValue + postValue;
                        }
                    }
                }
            }

            if(control.vinputText.textInputType === QmlEnumDef.STRING_MODE)
            {
                virtualTextField.text = virtualTextField.text.replace(/,/g,"")
                virtualTextField.text = virtualTextField.text.replace(/'/g,"")
                virtualTextField.text = virtualTextField.text.replace(/"/g,"")
            }

            if (event.key === Qt.Key_Return)
            {
                virtualTextField.focus = false
                virtualKeyPad.active = false
                control.visible = false

                if(control.vinputText !== null)
                {
                    control.vinputText.inputTextValue(virtualTextField.text)
                    control.vinputText = null
                }
            }
        }
    }

    InputPanel
    {
        id: virtualKeyPad
        z: 99
        x: 0
        y: control.height - height
        width: control.width
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
