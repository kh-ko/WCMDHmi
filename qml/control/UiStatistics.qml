import QtQuick 2.0
import QtGraphicalEffects 1.0
import ViewManager 1.0
import "."

Item {
    property bool   isIcon        : true
    property alias  imgSrc        : imageIcon.source
    property string title         : "Metal"
    property string value01       : "10 mv"
    property int    total         : 10
    property int    value02       : 20
    property color  bgColor       : "#59000000"
    property color  graphColor    : "#D9001B"
    property bool   isDetail      : false
    property int    barLength     : total ===0 ? 0 :
                                    isDetail ? (bg.height - 10) * (value02 / total) : (bg.width - 10) * (value02 / total)
    signal signalEventClicked()

    id : panel

    width: 206
    height: 100


    Component.onCompleted: {
        if(panel.isDetail)
        {
            panel.height = 213;
            textPercent.opacity = 1;
            textCount.opacity = 1;
        }
        else
        {
            panel.height = 100;
            textPercent.opacity = 0;
            textCount.opacity = 0;
        }

        trans.enabled = true
    }

    states: State
    {
        name: "detail"
        when: panel.isDetail
        PropertyChanges { target: panel; height : 213}
        PropertyChanges { target: textPercent; opacity : 1}
        PropertyChanges { target: textCount  ; opacity : 1}
    }

    transitions: Transition
    {
        id : trans
        enabled : false
        from: ""
        to: "detail"
        reversible: true
        ParallelAnimation {
            NumberAnimation { target: panel; properties: "height"; duration: 250; easing.type: Easing.InOutQuad}
            NumberAnimation { target: textPercent; properties: "opacity"; duration: 250; easing.type: Easing.InExpo}
            NumberAnimation { target: textCount; properties: "opacity"; duration: 250; easing.type: Easing.InExpo}
        }
    }

    Image
    {
        id: imageIcon
        width: 30
        height: 30
        anchors.verticalCenter: labelTitle.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0

        fillMode: Image.PreserveAspectFit
    }

    UiLabelSystem{
        id: labelTitle
        height: 30
        anchors.left: panel.isIcon === false ? parent.left : imageIcon.right
        anchors.leftMargin: panel.isIcon === false ? 0 : 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        textValue: panel.title
    }

    Rectangle{
        id: bg
        color: panel.bgColor
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: labelTitle.bottom
        anchors.topMargin: 10

        radius      : 10
        clip        : true
        border.width: 0

        Rectangle{
            id: bar
            height: panel.isDetail ? barLength : parent.height - 10
            width: panel.isDetail ? parent.width - 10 : barLength
            anchors.top: panel.isDetail ? undefined : parent.top
            anchors.topMargin: panel.isDetail ? undefined : 5
            anchors.right: panel.isDetail ? parent.right : undefined
            anchors.rightMargin: panel.isDetail ? 5 : undefined
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5

            radius: 10
            color : panel.graphColor
        }


        Glow {
            opacity: 0.3
            anchors.fill: bar
            radius: 15
            samples: 17
            source: bar
            color: bar.color
            visible: bar.visible
        }

        UiLabelContent{
            height: 30
            anchors.top: parent.top
            anchors.topMargin: 12
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            horizontalAlignment: Text.AlignHCenter
            textValue: panel.value01
        }

        UiLabelContent{
            id : textPercent
            height: 30
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            textValue: panel.total == 0 ? "0.0 %" :((panel.value02/panel.total) * 100).toLocaleString(ViewManager.locale, 'f', 1) + " %"
            opacity : 0
        }

        UiLabelContent{
            id : textCount
            width: 160
            height: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 12

            horizontalAlignment: Text.AlignRight
            textValue: (panel.value02).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
            opacity : 0
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            panel.signalEventClicked()
        }
    }

}
