import QtQuick 2.0
import "../../control/"

Item {
    id : panel

    anchors.fill: parent

    function showKeypad(value)
    {
        vKeypad.showKeypad(value)
    }

    UiKeypad{
        id :vKeypad
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
