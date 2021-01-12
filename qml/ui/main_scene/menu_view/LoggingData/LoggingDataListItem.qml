import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDef 1.0
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

            textValue: model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_NORMAL           ? qsTr("PASS"               ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_UNDER_WARNING    ? qsTr("UNDER WARNING"      ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_OVER_WARNING     ? qsTr("OVER WARNING"       ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_UNDER            ? qsTr("UNDER NG"           ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_OVER             ? qsTr("OVER NG"            ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_ETCERROR         ? qsTr("ETC NG"             ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_ETC_METAL_ERROR  ? qsTr("ETC NG"             ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_APP_START               ? qsTr("POWER ON"           ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_APP_EXIT                ? qsTr("POWER OFF"          ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_CHECKUP           ? qsTr("CHECK"              ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_STATIC_CARI      ? qsTr("STATIC CALIBRATION" ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_DYNAMIC_CARI     ? qsTr("DYNAMIC CALIBRATION"):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_RUN                     ? qsTr("RUN"                ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_STOP                    ? qsTr("STOP"               ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_TRADE             ? qsTr("PASS"               ):
                       model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_DETECT            ? qsTr("NG"                 ):""


            Image{
                source: model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_UNDER_WARNING   ? "img_eventicon/down_01_yellow.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_OVER_WARNING    ? "img_eventicon/down_01_yellow.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_UNDER           ? "img_eventicon/wc_down.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_OVER            ? "img_eventicon/wc_up.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_ETCERROR        ? "img_eventicon/etc_error.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_ETC_METAL_ERROR ? "img_eventicon/etc_error.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_CHECKUP          ? (model.onCommandGetWeightItem(idx) === "FAIL" ?"img_eventicon/md_checkup_fail.png":"img_eventicon/md_checkup_pass.png") :
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_STATIC_CARI     ? "img_eventicon/static_calib.png" :
                        model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_DYNAMIC_CARI    ? "img_eventicon/dynamic_calibsvg.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_RUN                    ? "img_eventicon/run_small.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_STOP                   ? "img_eventicon/stop_small.png":
                        model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_DETECT           ? "img_eventicon/metaldetect.png":""

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

            horizontalAlignment : model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_NORMAL            ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_UNDER_WARNING     ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_OVER_WARNING      ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_UNDER             ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_OVER              ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_ETCERROR          ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_ETC_METAL_ERROR   ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_APP_START                ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_APP_EXIT                 ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_CHECKUP            ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_STATIC_CARI       ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_WEIGHT_DYNAMIC_CARI      ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_RUN                      ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_STOP                     ? Text.AlignHCenter:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_TRADE              ? Text.AlignRight:
                                  model.onCommandGetEventItem(idx) === EnumDef.ET_METAL_DETECT             ? Text.AlignRight: Text.AlignHCenter

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
