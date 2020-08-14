import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import PanelWCDynamicCalibrationModel 1.0

UiPanel
{
    id : panel
    signal signalEventMenuClicked(string menuName)

    UiButton{
        id : btnStaticCaribraion
        height: 80
        width: 300
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 40

        textValue: qsTr("Static calibration")

        onSignalEventClicked: {
            panel.signalEventMenuClicked("StaticCaribraion")
        }
    }

    UiButton{
        id : btnDynamicCaribraion
        height: 80
        width: 300
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: btnStaticCaribraion.bottom
        anchors.topMargin: 40

        textValue: qsTr("Dynamic calibration")

        onSignalEventClicked: {
            panel.signalEventMenuClicked("DynamicCaribration")
        }
    }
}
