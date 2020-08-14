import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    property color glowOnColor : "#59FF0000"
    property color glowOffColor : "#59131313"
    property bool isOn
    property alias onImage : imageOn.source
    property alias offImage : imageOff.source

    id : component

    Image {
        id: imageOn
        anchors.fill: parent

        fillMode: Image.PreserveAspectFit
        visible: isOn ? true : false
    }

    Glow {
        anchors.fill: imageOn
        radius: 15
        samples: 17
        source: imageOn
        color: glowOnColor

        visible: imageOn.visible
    }

    Image {
        id: imageOff
        anchors.fill: parent

        fillMode: Image.PreserveAspectFit
        visible: isOn ? false : true
    }

    Glow {
        anchors.fill: imageOff
        radius: 15
        samples: 17
        source: imageOff
        color: glowOffColor

        visible: imageOff.visible
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
