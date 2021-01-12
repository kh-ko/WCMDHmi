import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import "../../../control"
import QmlEnumDef 1.0
import ViewManager 1.0
import PanelPDSelectModel 1.0

Dialog {
    property var value
    property var max

    id: dialog
    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside

    anchors.centerIn : parent

    onVisibleChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();

        console.debug("destory");
    }

    function loadList()
    {
        if(selectModel.onCommandGetPDListSize() < 8 )
            panel.width = 540 / ViewManager.scale
        else if(selectModel.onCommandGetPDListSize() < 15)
            panel.width = 1050 / ViewManager.scale
        else
            panel.width = 1560 / ViewManager.scale


        for(var i = 0; i < containerItem.children.length; i ++)
        {
            containerItem.children[i].destroy();
        }

        for(var j = 0; j < selectModel.onCommandGetPDListSize(); j ++)
        {
            pdItemComponent.createObject(containerItem, {"productSeq": selectModel.onCommandGetPDSeq(j), "productNo": selectModel.onCommandGetPDNum(j), "productName": selectModel.onCommandGetPDName(j)})
        }
    }

    PanelPDSelectModel{
        id : selectModel

        Component.onCompleted: {
            loadList();
        }

        onOrderChanged: {
            loadList();
        }
    }

    background: Rectangle
    {
        color : "#59000000"
        radius : 10
    }

    UiPanel{
        id :panel

        anchors.centerIn: parent
        height: 900 / ViewManager.scale
        scale: ViewManager.scale

        UiComboBox {
            id: comboOrder
            height: 60
            width: 300
            z: 1

            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            bgColor: panel.bgColor

            selIdx: selectModel.order
            listModel: comboOrderOption
            ListModel {
                id : comboOrderOption
                ListElement {
                    itemText : qsTr("Order by name")
                    itemIdx : 0
                }
                ListElement {
                    itemText : qsTr("Order by number")
                    itemIdx : 1
                }
            }

            onSignalEventChangedSel: {
                selectModel.onCommandSetOrder(itemIdx)
            }
        }

        UiButton{
            height: 60
            width: 180
            textValue : qsTr("Close")
            type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            onSignalEventClicked: {
                dialog.close();
            }

        }

        UiScrollView{
            id : scrollView
            clip: true
            anchors.top :comboOrder.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            ScrollBar.horizontal.interactive: false
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            Flow{
                id : containerItem
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left : parent.left
                anchors.leftMargin: 20

                width: scrollView.width - 20

                spacing: 10
            }
        }
    }

    Component{
        id : pdItemComponent

        UiPanel
        {
            property var productSeq
            property var productNo
            property var productName

            id : pdItem

            height : 80
            width : 500
            type : mouseArea.isPress ? QmlEnumDef.PANEL_TYPE_SELECT : QmlEnumDef.PANEL_TYPE_UP_PANEL

            MouseArea{
                property bool isPress : false

                id : mouseArea
                anchors.fill: parent
                hoverEnabled: true

                onContainsMouseChanged:
                {
                    if(!containsMouse)
                        isPress = false
                }

                onPressed:
                {
                    isPress = true
                }

                onReleased: {
                    isPress = false
                }

                onClicked:
                {
                    selectModel.onCommandSetSelectProduct(pdItem.productSeq)
                    dialog.close();
                }
            }

            UiLabelContent{
                width: parent.width
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                textValue: ("000" + pdItem.productNo).slice(-3) + "  " + pdItem.productName
            }
        }
    }
}

