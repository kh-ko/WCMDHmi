import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import FontManager 1.0
import EnumDefine 1.0
import MouseEventSpy 1.0

Calendar{
    id :control

    width : 500
    height: 500

    frameVisible: false

    style: CalendarStyle{
        id: calendarStyle
        gridVisible: false

        background: Rectangle{
            color: "#00000000"
        }

        navigationBar : Rectangle{
            id: rectangle
            height: 70
            color: "#00000000"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            UiButton{
                id : preMonth
                width : 50
                height: 50
                textValue: "<"
                //iconSource: "image/left.png"
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.verticalCenter: parent.verticalCenter

                onSignalEventClicked: {
                    control.showPreviousMonth()
                }
            }

            UiLabelContent{
                height: 50
                anchors.right: nextMonth.left
                anchors.rightMargin: 0
                anchors.left: preMonth.right
                anchors.leftMargin: 0
                anchors.verticalCenter: parent.verticalCenter

                horizontalAlignment: Text.AlignHCenter

                textValue : (control.visibleMonth + 1) + ". " + control.visibleYear


            }

            UiButton{
                id : nextMonth
                width : 50
                height: 50
                textValue: ">"
                //iconSource: "image/right.png"
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter

                onSignalEventClicked: {
                    control.showNextMonth()
                }
            }
        }

        dayOfWeekDelegate: Item{
            width : parent.width
            height: 50

            Text{
                verticalAlignment   : Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                elide: Text.ElideRight
                font.pixelSize: 25
                font.family: FontManager.nanumGothicName

                text: styleData.index === 0 ? qsTr("S") :
                      styleData.index === 1 ? qsTr("M") :
                      styleData.index === 2 ? qsTr("T") :
                      styleData.index === 3 ? qsTr("W") :
                      styleData.index === 4 ? qsTr("T") :
                      styleData.index === 5 ? qsTr("F") : qsTr("S")
                anchors.centerIn: parent
                color: styleData.index === 0 ? "#D9001B" :
                       styleData.index === 1 ? "#FFFFFF" :
                       styleData.index === 2 ? "#FFFFFF" :
                       styleData.index === 3 ? "#FFFFFF" :
                       styleData.index === 4 ? "#FFFFFF" :
                       styleData.index === 5 ? "#FFFFFF" : "#0085FF"
            }
        }

        dayDelegate: Item {

            Rectangle{
                anchors.fill: parent
                radius      : width / 2
                gradient: Gradient {
                    GradientStop {
                        position: 0.00
                        color: "#0085FF"
                    }
                    GradientStop {
                        position: 1.00
                        color: "#86C5FF"
                    }

                    orientation: Gradient.Horizontal
                }

                visible: styleData.selected
            }

            Text
            {
                verticalAlignment   : Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                elide: Text.ElideRight
                font.pixelSize: 25
                font.family: FontManager.nanumGothicName

                text: styleData.date.getDate()
                anchors.centerIn: parent
                color: styleData.date.getMonth() !== control.visibleMonth ? "#29FFFFFF" :
                                                (styleData.index) % 7 === 0 ? "#D9001B" :
                                                (styleData.index) % 7 === 1 ? "#FFFFFF" :
                                                (styleData.index) % 7 === 2 ? "#FFFFFF" :
                                                (styleData.index) % 7 === 3 ? "#FFFFFF" :
                                                (styleData.index) % 7 === 4 ? "#FFFFFF" :
                                                (styleData.index) % 7 === 5 ? "#FFFFFF" : "#0085FF"
            }
        }
    }

    Connections {
        target: MouseEventSpy
        onMouseEventDetected: {
        }
    }
}
