import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import LoggingDataModel 1.0

Item {
    property bool isSelected : model.selIdx === idx
    property bool isWeightColumVisible : true
    property LoggingDataModel model : null
    property int idx : 0

    id : listItem

    Rectangle{
        anchors.fill: parent
        color : "#0085FF"
        visible: listItem.model.setIdx == listItem.idx
    }

    RowLayout{
        id : title
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        spacing: 0

        UiLabelContent{
            Layout.preferredWidth: 403
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue:  model.onCommandGetDateTimeItem(idx)
        }

        UiLabelContent{
            Layout.preferredWidth: 472
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue: model.onCommandGetProductItem(idx)
        }

        UiLabelContent{
            id: contentEvent
            Layout.preferredWidth: 434
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue: model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_NORMAL_TYPE           ? qsTr("PASS"               ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_UNDER_WARNING_TYPE    ? qsTr("UNDER WARNING"      ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_OVER_WARNING_TYPE     ? qsTr("OVER WARNING"       ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_UNDER_TYPE            ? qsTr("UNDER NG"           ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_OVER_TYPE             ? qsTr("OVER NG"            ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ETCERROR_TYPE         ? qsTr("ETC NG"             ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ETC_METAL_ERROR_TYPE  ? qsTr("ETC NG"             ):
                       model.onCommandGetEventItem(idx) === EnumDefine.APP_START_TYPE               ? qsTr("POWER ON"           ):
                       model.onCommandGetEventItem(idx) === EnumDefine.APP_EXIT_TYPE                ? qsTr("POWER OFF"          ):
                       model.onCommandGetEventItem(idx) === EnumDefine.METAL_CHECKUP_TYPE           ? qsTr("CHECK"              ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_STATIC_CARI_TYPE      ? qsTr("STATIC CALIBRATION" ):
                       model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_DYNAMIC_CARI_TYPE     ? qsTr("DYNAMIC CALIBRATION"):
                       model.onCommandGetEventItem(idx) === EnumDefine.RUN_TYPE                     ? qsTr("RUN"                ):
                       model.onCommandGetEventItem(idx) === EnumDefine.STOP_TYPE                    ? qsTr("STOP"               ):
                       model.onCommandGetEventItem(idx) === EnumDefine.METAL_TRADE_TYPE             ? qsTr("PASS"               ):
                       model.onCommandGetEventItem(idx) === EnumDefine.METAL_DETECT_TYPE            ? qsTr("NG"                 ):""


            Image{
                source: model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_UNDER_WARNING_TYPE   ? "img_eventicon/down_01_yellow.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_OVER_WARNING_TYPE    ? "img_eventicon/down_01_yellow.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_UNDER_TYPE           ? "img_eventicon/wc_down.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_OVER_TYPE            ? "img_eventicon/wc_up.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ETCERROR_TYPE        ? "img_eventicon/etc_error.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ETC_METAL_ERROR_TYPE ? "img_eventicon/etc_error.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.METAL_CHECKUP_TYPE          ? (model.onCommandGetWeightItem(idx) === "FAIL" ?"img_eventicon/md_checkup_fail.png":"img_eventicon/md_checkup_pass.png") :
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_STATIC_CARI_TYPE     ? "img_eventicon/static_calib.png" :
                        model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_DYNAMIC_CARI_TYPE    ? "img_eventicon/dynamic_calibsvg.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.RUN_TYPE                    ? "img_eventicon/run_small.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.STOP_TYPE                   ? "img_eventicon/stop_small.png":
                        model.onCommandGetEventItem(idx) === EnumDefine.METAL_DETECT_TYPE           ? "img_eventicon/metaldetect.png":""

                //rotation: model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ERROR_OVER || model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ERROR_OVERWARNING ? 180 : 0
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        UiLabelSystem{
            Layout.preferredWidth: 169
            Layout.fillHeight: true
            Layout.fillWidth: true

            horizontalAlignment : model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_NORMAL_TYPE            ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_UNDER_WARNING_TYPE     ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_OVER_WARNING_TYPE      ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_UNDER_TYPE             ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_OVER_TYPE              ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ETCERROR_TYPE          ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_ETC_METAL_ERROR_TYPE   ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.APP_START_TYPE                ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.APP_EXIT_TYPE                 ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.METAL_CHECKUP_TYPE            ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_STATIC_CARI_TYPE       ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.WEIGHT_DYNAMIC_CARI_TYPE      ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.RUN_TYPE                      ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.STOP_TYPE                     ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDefine.METAL_TRADE_TYPE              ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDefine.METAL_DETECT_TYPE             ? Text.AlignRight: Text.AlignHCenter

            textValue: model.onCommandGetWeightItem(idx)
        }
    }

    MouseArea{
        anchors.fill: parent
        onPressed:
        {
            model.onCommandSetSelect(idx)
        }
    }
}
