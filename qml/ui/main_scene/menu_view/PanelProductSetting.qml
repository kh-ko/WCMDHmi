import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./ProductSetting"
import QtQuick.Layouts 1.3
import EnumDef 1.0
import QmlEnumDef 1.0
import PanelProductSettingModel 1.0
import ProductSettingItemModel 1.0

UiPanel {

    property bool isViewMode : false
    property bool isAdmin    : false
    id: panel

    width : 1518
    height : 997

    function loadList()
    {
        var selectIdx = 0;

        listModel.clear()

        for(var i = 0; i < productSettingModel.productCount; i ++)
        {
            var itemModel = productSettingModel.onCommandGetItemModel(i);
            listModel.append({"productSeq":itemModel.seq,"productNo":itemModel.no,"productName":itemModel.name})

            if(productSettingModel.lookProductSeq === itemModel.seq)
            {
                selectIdx = i;
            }
        }

        productList.positionViewAtIndex(selectIdx, ListView.Beginning)
    }

    Component.onCompleted:
    {
        loadList()
    }

    PanelProductSettingModel
    {
        id : productSettingModel

        onSignalEventResultSaveProductSetting: {
            //busyIndi.visible = false;

            if(isInvalidWC == false && isEmptyNo == false && svcErr == EnumDef.PDERR_NONE)
            {
                loadList()

                ViewManager.toast.show(qsTr("Your settings have been saved."))
            }
            else if(isInvalidWC == true)
            {
                ViewManager.toast.show(qsTr("Invalid weight checker setting."))
            }
            else if(isEmptyNo == true)
            {
                ViewManager.toast.show(qsTr("Please enter product no."))
            }
            else if(svcErr == EnumDef.PDERR_NOT_EXIST)
            {
                ViewManager.toast.show(qsTr("This product dose not exist."))
            }
            else if(svcErr == EnumDef.PDERR_SAME_PD_NUM)
            {
                ViewManager.toast.show(qsTr("The Product no already exists."))
            }
            else if(svcErr == EnumDef.PDERR_SELECTED)
            {
                ViewManager.toast.show(qsTr("can not remove selected product."))
            }
            else
            {
                ViewManager.toast.show(qsTr("SQL error is occured."))
            }
        }

        onOrderChanged: {
            loadList()
        }
    }

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

        selIdx: productSettingModel.order
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
            productSettingModel.onCommandSetOrder(itemIdx)
        }
    }

    ListView {
        id: productList
        width: 493
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: btnAddProduct.top
        anchors.bottomMargin: 20
        anchors.top: comboOrder.bottom
        anchors.topMargin: 20
        model: listModel
        clip: true

        delegate: UiPanel
        {
            height : 100
            width : 495
            type : productSettingModel.lookProductSeq === productSeq ? QmlEnumDef.PANEL_TYPE_SELECT : QmlEnumDef.PANEL_TYPE_NONE

            MouseArea{
                anchors.fill: parent

                onClicked:
                {
                    productSettingModel.onCommandSetSelectProduct(productSeq)
                    productSettingModel.onCommandSetLookProduct(productSeq)
                }
            }

            UiRadioBtn
            {
                width: 40
                height: 40
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                textValue : ""
                isSelect : productSettingModel.selectedProductSeq === productSeq

                onSignalEventClicked: {
                    productSettingModel.onCommandSetSelectProduct(productSeq)
                    productSettingModel.onCommandSetLookProduct(productSeq)
                }
            }

            UiLabelContent{
                width: 400
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 80
                anchors.verticalCenter: parent.verticalCenter

                textValue: ("000" + productNo).slice(-3) + "  " + productName
            }
        }

        ListModel{
            id: listModel
        }
    }

    UiButton{
        id:btnAddProduct
        height: 80
        anchors.right: productEditView.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        visible: !panel.isViewMode
        textValue: qsTr("New product")

        onSignalEventClicked: {
            productSettingModel.onCommandAddProduct()
        }
    }

    ProductEditView{
        id: productEditView
        anchors.left: productList.right
        anchors.leftMargin: -20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        isAdmin: panel.isAdmin
        isEnableWC: productSettingModel.isEnableWC
        isEnableMD: productSettingModel.isEnableMD
        isViewMode : panel.isViewMode
        itemModel : productSettingModel.onCommandGetEditViewItemModel()

        onSignalEventAddCliecked: {
            productSettingModel.onCommandApplyProduct()
        }

        onSignalEventCancleCliecked: {
            productSettingModel.onCommandCancleProduct()
        }

        onSignalEventRemoveCliecked: {
            var removeSeq = productSettingModel.selectedProductSeq;

            for(var i = 0; i < productSettingModel.productCount; i ++)
            {
                var itemModel = productSettingModel.onCommandGetItemModel(i);

                if(itemModel.seq !== productSettingModel.selectedProductSeq)
                {
                    productSettingModel.onCommandSetSelectProduct(itemModel.seq)
                    productSettingModel.onCommandSetLookProduct(itemModel.seq)
                    break;
                }
            }

            productSettingModel.onCommandRemoveProduct(removeSeq)
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:8;anchors_width:430}
}
##^##*/
