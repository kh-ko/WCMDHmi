import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../control"
import "./graph"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0

UiPanel
{

    property var isWCEnable
    property var isMDEnable
    property var selDev : isWCEnable === true && isMDEnable === false ? QmlEnumDef.DEVICE_WEIGHT_CHECKER : ViewManager.mainScene.selDevGraphMenu
    id : panel

    width : 1519
    height: 997

    StackView
    {
        id: viewContainer
        anchors.fill : parent
        initialItem: selDev === QmlEnumDef.DEVICE_WEIGHT_CHECKER ? panelWCGraph : panelMDGraph
    }

    UiComboBox {
        id: comboSelDev
        z : 2
        height: 60
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width : 300

        visible: panel.isWCEnable && isMDEnable
        bgColor: panel.bgColor
        selIdx: selDev

        listModel: comboSelDevOption
        ListModel {
            id : comboSelDevOption
            ListElement {
                itemText : qsTr("Metal detector")
                itemIdx : QmlEnumDef.DEVICE_METAL_DETECTOR
            }
            ListElement {
                itemText : qsTr("Weight checker")
                itemIdx : QmlEnumDef.DEVICE_WEIGHT_CHECKER
            }
        }

        onSignalEventChangedSel: {

            if(ViewManager.mainScene.selDevGraphMenu === itemIdx)
                return;

            viewContainer.clear()

            ViewManager.mainScene.selDevGraphMenu = itemIdx

            if(itemIdx == QmlEnumDef.DEVICE_METAL_DETECTOR)
            {
                viewContainer.push(panelMDGraph)
            }
            else
            {
                viewContainer.push(panelWCGraph)
            }
        }
    }

    Component{ id : panelWCGraph; PanelWCGraph{anchors.fill: parent} }
    Component{ id : panelMDGraph; PanelMDGraph{anchors.fill: parent} }
}
