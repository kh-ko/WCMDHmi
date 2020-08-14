import QtQuick 2.0
import FontManager 1.0
import "../../control/"

Item {
    id: panel
    width : 1000
    height: 120

    function show(value)
    {
        timer.stop();
        closeAni.stop();
        showAni.stop();

        toast.visible = true;
        toast.opacity = 0;
        toast.yOffset = toast.height;
        message.text = value;

        timer.start();
        showAni.start();
    }


    Timer {
        id : timer
        interval: 4000; running: false; repeat: false
        onTriggered:
        {
            closeAni.start()
        }
    }

    ParallelAnimation {
        id :showAni

        NumberAnimation {
            target: toast
            properties: "opacity"
            duration: 250
            from : 0
            to: 1.0
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: toast
            properties: "yOffset"
            duration: 500
            from: toast.height
            to : 0
            easing.type: Easing.InOutQuad
        }
    }

    ParallelAnimation {
        id :closeAni

        NumberAnimation {
            target: toast
            properties: "opacity"
            duration: 250
            from : 1.0
            to: 0
            easing.type: Easing.InOutQuad
        }

        onStopped: {
            toast.visible = false;
        }
    }

    Rectangle
    {
        property int yOffset : 0

        id: toast
        visible: false
        height: 120
        width : 1203
        color : "#d9000000"
        radius: 60
        border.color: "#0085ff"
        border.width: 5
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenterOffset: toast.yOffset * -1


        Text{
            id:message

            anchors.fill : parent

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            font.pixelSize: 50
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: "Alarm disable label"
        }

    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
