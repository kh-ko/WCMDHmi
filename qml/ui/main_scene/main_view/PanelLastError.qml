import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDef 1.0
import ViewManager 1.0


Item {
    property int    viewMode           : EnumDef.WC_VIEWMODE_CURRENT
    property string errorTime          : "23:10:10"
    property int    errorType          : EnumDef.ET_WEIGHT_UNDER
    property int    errorValue         : 999999
    property int    normalWeight       : 50
    property int    senstivity         : 99

    property real   value              :  viewMode === EnumDef.WC_VIEWMODE_DELTA ? ((errorValue - normalWeight) / 1000) : ((errorValue) / 1000)

    signal signalEventClickedLastError();
    id : panel

    width: 339
    height: 168

    UiPanel{
        id : bg
        anchors.fill: parent

        UiLabelSystem{
            id : labelLastNG
            width : 132
            height : 30
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            textValue: qsTr("Last NG")
        }

        Image{
            id : clockIcon
            width: 18
            height: 18
            source: "img_lasterror/clock.png"
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

            visible: panel.errorType === EnumDef.ET_WEIGHT_NORMAL || panel.errorType === EnumDef.ET_NONE ? false : true
            fillMode: Image.PreserveAspectFit
        }


        UiLabelContent{
            id :labelTime
            height : 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: clockIcon.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            visible: panel.errorType === EnumDef.ET_WEIGHT_NORMAL || panel.errorType === EnumDef.ET_NONE  ? false : true
            textValue : panel.errorTime
        }

        Image{
            id : eventIcon
            width: 30
            height: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            source: panel.errorType === EnumDef.ET_WEIGHT_UNDER    ? "img_panelevent/wc_down.png" :
                    panel.errorType === EnumDef.ET_WEIGHT_OVER     ? "img_panelevent/wc_up.png" :
                    panel.errorType === EnumDef.ET_METAL_DETECT    ? "img_panelevent/metaldetect.png" : ""

            fillMode: Image.PreserveAspectFit

            visible: panel.errorType === EnumDef.ET_WEIGHT_NORMAL || panel.errorType === EnumDef.ET_NONE  ? false : true
        }


        UiLabelContent{
            height : 30
            anchors.left: eventIcon.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: eventIcon.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : (panel.errorType === EnumDef.ET_WEIGHT_UNDER || panel.errorType === EnumDef.ET_WEIGHT_OVER)? viewMode === EnumDef.WC_VIEWMODE_DELTA && value > 0 ? "+" + value.toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g": value.toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g":
                        panel.errorType === EnumDef.ET_METAL_DETECT  ? qsTr("Metal detect") :
                        panel.errorType === EnumDef.ET_WEIGHT_ETCERROR || panel.errorType === EnumDef.ET_WEIGHT_ETC_METAL_ERROR? qsTr("Etc error") : ""
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                panel.signalEventClickedLastError();
            }
        }
    }
}



