import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./ProductSetting"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import PanelProductSettingModel 1.0
import ProductSettingItemModel 1.0

UiPanel {

    property bool isViewMode : false
    id: panel

    width : 1518
    height : 997

    Component.onCompleted:
    {
        var selectIdx = 0;

        for(var i = 0; i < productSettingModel.productCount; i ++)
        {
            var itemModel = productSettingModel.onCommandGetItemModel(i);
            listModel.append({"seq":itemModel.seq})

            if(productSettingModel.selectedProductSeq === itemModel.seq)
            {
                selectIdx = i;
            }
        }

        productList.positionViewAtIndex(selectIdx, ListView.Beginning)
    }

    PanelProductSettingModel
    {
        id : productSettingModel

        onSignalEventResultSaveProductSetting: {
            //busyIndi.visible = false;

            if(error === EnumDefine.SQL_ERROR)
            {
                ViewManager.toast.show(qsTr("SQL error is occured."))
            }
            else if(error === EnumDefine.NOT_EXIST_SEQ)
            {
                ViewManager.toast.show(qsTr("This product dose not exist."))
            }
            else if(error === EnumDefine.ALREADY_NO_ERROR)
            {
                ViewManager.toast.show(qsTr("The Product no already exists."))
            }
            else if(error === EnumDefine.EMPTY_PRODUCT_NO)
            {
                ViewManager.toast.show(qsTr("Please enter product no."))
            }
            else if(error === EnumDefine.ZERO_PRODUCT_LENGTH)
            {
                ViewManager.toast.show(qsTr("Invalid product length."))
            }
            else if(error === EnumDefine.ZERO_PRODUCT_SEPPD)
            {
                ViewManager.toast.show(qsTr("Invalid product speed."))
            }
            else if(error === EnumDefine.INVAILD_WEIGHT_CHECKER_SETTING)
            {
                ViewManager.toast.show(qsTr("Invalid weight checker setting."))
            }
            else if(error === EnumDefine.INVAILD_METAL_DETECTOR_SETTING)
            {
                ViewManager.toast.show(qsTr("Invalid metal detector setting."))
            }
            else if(error === EnumDefine.REMOVE_SEL_PRODUCT)
            {
                ViewManager.toast.show(qsTr("can not remove selected product."))
            }
            else
            {
                ViewManager.toast.show(qsTr("Your settings have been saved."))
            }
        }

        onSignalEventRemoveProductSetting:
        {
            for(var i = 0; i < listModel.count; i ++)
            {
                if( listModel.get(i).seq === seq)
                {
                    listModel.remove(i);
                    break;
                }
            }
        }

        onSignalEventAddProductSetting:
        {
            listModel.clear()

            for(var i = 0; i < productSettingModel.productCount; i ++)
            {
                var itemModel = productSettingModel.onCommandGetItemModel(i);
                listModel.append({"seq":itemModel.seq})
            }
        }
    }

    ListView {
        id: productList
        width: 493
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: btnAddProduct.top
        anchors.bottomMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        model: listModel
        clip: true

        delegate: UiPanel
        {
            property ProductSettingItemModel itemModel : productSettingModel.onCommandFindItemModel(seq)

            height : 100
            width : 495
            type : productSettingModel.lookProductSeq === itemModel.seq ? EnumDefine.PANEL_TYPE_SELECT : EnumDefine.PANEL_TYPE_NONE

            MouseArea{
                anchors.fill: parent

                onClicked:
                {
                    productSettingModel.onCommandSetLookProduct(itemModel.seq)
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
                isSelect : productSettingModel.selectedProductSeq === itemModel.seq

                onSignalEventClicked: {
                    productSettingModel.onCommandSetSelectProduct(itemModel.seq)
                    productSettingModel.onCommandSetLookProduct(itemModel.seq)
                }
            }

            UiLabelContent{
                width: 400
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: 80
                anchors.verticalCenter: parent.verticalCenter

                textValue: ("000" + itemModel.no).slice(-3) + "  " + itemModel.name
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

        isViewMode : panel.isViewMode
        itemModel : productSettingModel.onCommandGetEditViewItemModel()

        onSignalEventAddCliecked: {
            productSettingModel.onCommandApplyProduct()
        }

        onSignalEventCancleCliecked: {
            productSettingModel.onCommandCancleProduct()
        }

        onSignalEventRemoveCliecked: {
            productSettingModel.onCommandRemoveProduct()
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:8;anchors_width:430}
}
##^##*/
