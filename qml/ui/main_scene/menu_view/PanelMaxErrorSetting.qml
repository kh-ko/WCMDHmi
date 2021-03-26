import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelMaxErrorSettingModel 1.0

UiPanel
{
    property var maxError: settingModel.mMaxError
    property var averageError :  settingModel.mAverage
    property var times  : settingModel.mTimes
    property var min    : settingModel.mMin
    property var max    : settingModel.mMax
    property var sd     : settingModel.mSD

    width : 1518
    height: 987

    id : panel

    PanelMaxErrorSettingModel{
        id : settingModel

        onSignalEventAddedEvent : {
            listModel.append({"weight" : value})
            measureList.positionViewAtEnd()
        }

        onSignalEventRefreshedList : {
            listModel.clear()
            for(var i = 0; i < onCommandGetListCnt(); i ++)
            {
                var weight = onCommandGetWeight(i)
                listModel.append({"weight" : weight})
            }
        }

    }

    UiInputFloat{
        id: inputMaxError
        width: 400
        height: 60
        anchors.left: parent.left
        anchors.top: parent.top
        labelText: qsTr("Max error")
        postfix: "g"
        inputWidth: 250
        anchors.leftMargin: 40
        anchors.topMargin: 40

        isHighlight: settingModel.mIsEditMaxError
        min : 0
        max : 99999999
        realValue: panel.maxError / 1000

        onSignalChangeValue: {
            settingModel.onCommandEditMaxError(value * 1000)
        }
    }

    UiButton {
        id: btnApply
        width: 160
        height: 60
        anchors.verticalCenter: inputMaxError.verticalCenter
        anchors.left: inputMaxError.right
        anchors.leftMargin: 20
        textValue: qsTr("Apply")

        onSignalEventClicked: {
            settingModel.onCommandApply()
        }
    }

    UiLabelSystem{
        id : labelTextTh
        width: 150
        height: 60
        anchors.left: parent.left
        anchors.top: inputMaxError.bottom
        textValue: qsTr("Times")
        anchors.leftMargin: 40
        anchors.topMargin: 10
    }

    Text {
        id: textTh
        color: "#ffffff"
        text: ""+panel.times
        anchors.verticalCenter: labelTextTh.verticalCenter
        anchors.left: labelTextTh.right
        horizontalAlignment: Text.AlignRight
        anchors.leftMargin: 0
        font.pointSize: 25
    }

    UiLabelSystem{
        id : labelTextAvg
        width: 150
        height: 60
        anchors.left: parent.left
        anchors.top: labelTextTh.bottom
        textValue: qsTr("Average")
        anchors.leftMargin: 40
        anchors.topMargin: 10
    }

    Text {
        id: textAvg
        color: "#ffffff"
        text: (panel.averageError/1000).toLocaleString(ViewManager.locale, 'f', 3)
        anchors.verticalCenter: labelTextAvg.verticalCenter
        anchors.left: labelTextAvg.right
        horizontalAlignment: Text.AlignRight
        anchors.leftMargin: 0
        font.pointSize: 25
    }

    UiLabelSystem{
        id : labelTextMax
        width: 150
        height: 60
        anchors.left: parent.left
        anchors.top: labelTextAvg.bottom
        textValue: qsTr("Max")
        anchors.leftMargin: 40
        anchors.topMargin: 10
    }

    Text {
        id: textMax
        color: "#ffffff"
        text:  (panel.max/1000).toLocaleString(ViewManager.locale, 'f', 3)
        anchors.verticalCenter: labelTextMax.verticalCenter
        anchors.left: labelTextMax.right
        horizontalAlignment: Text.AlignRight
        anchors.leftMargin: 0
        font.pointSize: 25
    }

    UiLabelSystem{
        id : labelTextMin
        width: 150
        height: 60
        anchors.left: parent.left
        anchors.top: labelTextMax.bottom
        textValue: qsTr("Min")
        anchors.leftMargin: 40
        anchors.topMargin: 10
    }

    Text {
        id: textMin
        color: "#ffffff"
        text: (panel.min/1000).toLocaleString(ViewManager.locale, 'f', 3)
        anchors.verticalCenter: labelTextMin.verticalCenter
        anchors.left: labelTextMin.right
        horizontalAlignment: Text.AlignRight
        anchors.leftMargin: 0
        font.pointSize: 25
    }

    UiLabelSystem{
        id : labelTextSD
        width: 150
        height: 60
        anchors.left: parent.left
        anchors.top: labelTextMin.bottom
        textValue: qsTr("SD")
        anchors.leftMargin: 40
        anchors.topMargin: 10
    }

    Text {
        id: textSD
        color: "#ffffff"
        text: (panel.sd/1000).toLocaleString(ViewManager.locale, 'f', 3)
        anchors.verticalCenter: labelTextSD.verticalCenter
        anchors.left: labelTextSD.right
        horizontalAlignment: Text.AlignRight
        anchors.leftMargin: 0
        font.pointSize: 25
    }

    UiButton {
        id: btnSort
        width: 160
        height: 60
        anchors.top: labelTextSD.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        textValue: qsTr("Sort")

        onSignalEventClicked: {
            settingModel.onCommandSortList()
        }
    }

    ListView {
        id: measureList

        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.bottom: btnStop.top
        anchors.rightMargin: 40
        spacing: 10
        anchors.bottomMargin: 40
        width: 740
        anchors.right: parent.right

        model: listModel
        clip: true


        delegate: UiPanel
        {
            height : 80
            width : 700
            type : QmlEnumDef.PANEL_TYPE_UP_PANEL

            UiLabelContent{
                id : textWeight
                width: 250
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                horizontalAlignment : Text.AlignRight
                textValue: (weight/1000).toLocaleString(ViewManager.locale, 'f', 3)
            }

            UiLabelContent{
                id : textGab
                width: 250
                height: parent.height
                anchors.left: textWeight.right
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                horizontalAlignment : Text.AlignRight
                textValue: ((weight - settingModel.mAverage)/1000).toLocaleString(ViewManager.locale, 'f', 3)
            }

            UiButton{
                id : btnSet
                width: 100
                height: parent.height - 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                type : QmlEnumDef.BUTTON_TYPE_UP_PANEL

                textValue: qsTr("Set")

                onSignalEventClicked: {
                    var gab = weight - settingModel.mAverage;

                    var absGab = gab < 0 ? -1 * gab : gab

                    settingModel.onCommandEditMaxError(absGab)
                }
            }
        }

        ListModel{
            id: listModel
        }
    }


    UiButton{
        id : btnStop
        height: 80
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.rightMargin: 20

        textValue: qsTr("Stop")

        onSignalEventClicked: {
            settingModel.onCommandStop()
        }

    }

    UiButton {
        id: btnStart
        height: 80
        anchors.right: btnStop.left
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        textValue: qsTr("Start")
        anchors.bottomMargin: 20

        onSignalEventClicked: {
            settingModel.onCommandStart()
        }
    }
}




