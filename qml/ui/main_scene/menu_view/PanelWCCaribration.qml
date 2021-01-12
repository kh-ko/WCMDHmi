import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../control"
import "./WCCaribraion"
import QtQuick.Layouts 1.3
import PanelMDCheckupModel 1.0

Item {
    id: uiPanel
    width : 1519
    height: 997


    function move(viewName)
    {
        if(viewName === "StaticCaribraion")
        {
            wcCalibrationMenu.visible = false
            wcDynamicCaribraion.visible  = false
            wcStaticCaribraion.visible = true
        }
        else if(viewName === "DynamicCaribration")
        {
            wcCalibrationMenu.visible = false
            wcDynamicCaribraion.visible  = true
            wcStaticCaribraion. visible = false
        }
        else
        {
            wcCalibrationMenu.visible = true
            wcDynamicCaribraion.visible  = false
            wcStaticCaribraion.visible = false
        }

    }

    PanelWCCalibarationMenu
    {
        id : wcCalibrationMenu
        anchors.fill: parent

       onSignalEventMenuClicked: {
            uiPanel.move(menuName)
       }
    }

    PanelWCStaticCaribraion
    {
        id : wcStaticCaribraion
        anchors.fill: parent
        visible: false

        onSignalEventCloseClicked: {
             uiPanel.move("")
        }
    }

    PanelWCDynamicCaribraion
    {
        id :wcDynamicCaribraion
        anchors.fill: parent
        visible: false

        onSignalEventCloseClicked: {
             uiPanel.move("")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
