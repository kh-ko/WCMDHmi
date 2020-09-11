import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import FontManager 1.0
import EnumDefine 1.0
import ViewManager 1.0

Item {
    property bool isWait        : false
    property bool isDevMode     : false
    property int  currWeight    : 9199000
    property int  currEventType :EnumDefine.WEIGHT_OVER_TYPE
    //property int  avgWeight     : 9199000
    //property int  avgEventType  :EnumDefine.WEIGHT_OVER_TYPE
    property int  under         : 100
    property int  underWarning  : 200
    property int  normal        : 300
    property int  overWarning   : 450
    property int  over          : 800
    //property int  averageNValue : 1000
    property int  tare          : 1000

    id : panel
    width: 1505
    height: 549

    states: [
        State {
            name: "blinking"
            when: panel.isWait
        },
        State {
            name: ""
            when: panel.isWait == false
            PropertyChanges { target: textWeight; opacity : 1}
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "blinking"

            SequentialAnimation {
                loops: Animation.Infinite
                PropertyAnimation {target: textWeight; property: "opacity"; from: 1.0; to: 0.0; duration: 500 }
                PropertyAnimation {target: textWeight; property: "opacity"; from: 0.0; to: 1.0; duration: 500 }
            }
       }
    ]
    Item{
        id : panelWeight
        height: 300
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter

        Text{
            id :labelNet
            height: 57
            color: "#acacac"
            width: 125
            anchors.left: labelGram.left
            anchors.top: parent.top
            anchors.leftMargin: 0
            anchors.topMargin: 0

            text: "NET"
            font.pointSize: 40
            font.family: FontManager.nanumGothicBName
            font.bold: true
        }

        Text{
            id : textWeight
            property real value : isDevMode ? ((panel.currWeight - panel.normal)/1000) : (panel.currWeight / 1000)
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: labelGram.left
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            text: panel.currWeight == 0 ? "0.0" :
                  isDevMode && value > 0 ? "+"+value.toLocaleString(ViewManager.locale, 'f', 1) : value.toLocaleString(ViewManager.locale, 'f', 1)
            font.letterSpacing: 0
            color: currEventType === EnumDefine.WEIGHT_OVER_TYP ? "#F59A23":
                   currEventType === EnumDefine.WEIGHT_UNDER_TYPE ? "#D9001B" : "#FFFFFF"
            horizontalAlignment: Text.AlignRight
            fontSizeMode: Text.FixedSize
            verticalAlignment: Text.AlignVCenter
            font.pointSize: isDevMode? 220 : 250
            font.family: FontManager.nanumGothicBName
            font.bold: true
        }

        Text{
            id :labelGram
            width: 50
            height: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 30

            color: "#acacac"
            text: "g"
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 50
            font.family: FontManager.nanumGothicBName
            font.bold: true
        }
    }

    WeightCheckerGauge{
        height: 65
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (((parent.height / 2) - (panelWeight.height / 2)) / 2 ) - height / 2
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.rightMargin: 20
        anchors.leftMargin: 20

        weight       : panel.currWeight
        eventType    : panel.currEventType
        //avgWeight    : panel.avgWeight
        //avgEventType : panel.avgEventType
        under        : panel.under
        underWarning : panel.underWarning
        normal       : panel.normal
        overWarning  : panel.overWarning
        over         : panel.over


    }
/*
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Item
        {
            id: element
            Layout.fillHeight: true
            Layout.preferredHeight: 344
            Layout.fillWidth: true

            UiDigitalLabel{
                id: digiCurrWeight
                height: 344
                anchors.verticalCenterOffset: 50
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                fontSize: 330

                value : panel.currWeight
                eventType: panel.currEventType
            }
        }

        Item
        {
            Layout.fillHeight: true
            Layout.preferredHeight: 219
            Layout.fillWidth: true

            WeightCheckerGauge{
                height: 108
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.rightMargin: 130
                anchors.leftMargin: 130

                weight       : panel.currWeight
                eventType    : panel.currEventType
                avgWeight    : panel.avgWeight
                avgEventType : panel.avgEventType
                under        : panel.under
                underWarning : panel.underWarning
                normal       : panel.normal
                overWarning  : panel.overWarning
                over         : panel.over


            }
        }


        Item{
            id: element1
            Layout.fillHeight: true
            Layout.preferredHeight: 138
            Layout.fillWidth: true

            UiLabelSystemBig{
                width : 361
                anchors.right: digiAvgWeight.left
                anchors.rightMargin: 40
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                horizontalAlignment : Text.AlignRight
                textValue: "AVG("+panel.averageNValue.toLocaleString(ViewManager.locale, 'f', 0)+")"

            }

            UiDigitalLabel{
                id: digiAvgWeight
                width : 300
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                fontSize: 65

                visibleNet : false
                value : panel.avgWeight
                eventType: panel.avgEventType
            }
        }

    }
*/
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:1;anchors_height:100;anchors_width:50}D{i:3;anchors_width:125}
}
##^##*/
