import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../control/"

Rectangle {
    property UiInputDate input;

    function showCalendar(inputDate)
    {
        input = inputDate
        calendar.selectedDate = new Date(input.year, input.month - 1, input.day)
        panel.visible = true;
    }

    id: panel
    color: "#59000000"
    border.width: 0
    visible: false
    width: 1920
    height: 1080

    MouseArea
    {
        anchors.fill: parent
        onClicked: {panel.visible = false}
    }

    Rectangle{
        id: rectangle
        color: "#E9000000"
        radius: 20
        anchors.right: parent.right
        anchors.rightMargin: 710
        border.width:0

        width: 500
        height: 600
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        MouseArea
        {
            anchors.fill: parent
            onClicked: {}
        }

        UiButton{
            height: 80
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 20

            textValue: qsTr("Cancle")

            onSignalEventClicked:
            {
                panel.visible = false
            }

        }

        UiCalendar{
            id : calendar
            width: 500
            height: 500
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter

            onPressed: {}
            onClicked: {
                input.setDate(date.getFullYear(), date.getMonth() + 1 , date.getDate());
                panel.visible = false
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
