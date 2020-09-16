import QtQuick 2.0
import ViewManager 1.0
import "."

Item {
    property color bgColor : "#232323"
    property bool isDisable : false
    property bool isHourMode : true
    property bool isCalendarMode : false
    property int year : 2020
    property int month : 1
    property int day : 10
    property int hour : 10

    signal signalEventChangedDate(int year, int month, int day, int hour)

    function setDate(inYear, inMonth, inDay)
    {
        signalEventChangedDate(inYear, inMonth, inDay, 0)
    }

    id: control
    width :429
    height : 60

    UiInputNumber{
        id : inputYear
        width: 120
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        bgColor: control.bgColor

        isLocaleStyle: false
        isDisable : control.isDisable
        numberValue : control.year
        min : 2020
        max : 9999
        postfix: "."
        fillZero: "0000"

        onSignalChangeValue: {
            signalEventChangedDate(value, control.month, control.day, control.hour)
        }

        MouseArea{
            anchors.fill: parent
            enabled: control.isCalendarMode

            onClicked: {
                ViewManager.calendar.showCalendar(control)
            }
        }
    }

    UiInputNumber{
        id : inputMonth
        width: 88
        anchors.left: inputYear.right
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        bgColor: control.bgColor

        isLocaleStyle: false
        isDisable : control.isDisable
        numberValue : control.month
        min : 1
        max : 12
        postfix: "."
        fillZero: "00"

        onSignalChangeValue: {
            signalEventChangedDate(control.year, value, control.day, control.hour)
        }

        MouseArea{
            anchors.fill: parent
            enabled: control.isCalendarMode

            onClicked: {
                ViewManager.calendar.showCalendar(control)
            }
        }
    }

    UiInputNumber{
        id : inputDay
        width: 88
        anchors.left: inputMonth.right
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        bgColor: control.bgColor

        isLocaleStyle: false
        isDisable : control.isDisable
        numberValue : control.day
        min : 1
        max : 31
        postfix: "."
        fillZero: "00"

        onSignalChangeValue: {
            control.signalEventChangedDate(control.year, control.month, value, control.hour)
        }

        MouseArea{
            anchors.fill: parent
            enabled: control.isCalendarMode

            onClicked: {
                ViewManager.calendar.showCalendar(control)
            }
        }

        UiInputNumber{
            id : inputHour
            width: 98
            anchors.left: inputDay.right
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            visible: control.isHourMode
            bgColor: control.bgColor

            isLocaleStyle: false
            isDisable : control.isDisable
            numberValue : control.hour
            min : 0
            max : 23
            postfix: "h"
            fillZero: "00"

            onSignalChangeValue: {
                control.signalEventChangedDate(control.year, control.month, control.day, value)
            }
        }
    }
}


