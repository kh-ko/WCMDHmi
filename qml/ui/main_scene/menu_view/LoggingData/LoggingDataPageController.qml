import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0


Item {
    property int totalPageCnt : 0
    property int currentPageIdx : 0

    property int pageCntPerSceen : 9
    property int page01 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 1
    property int page02 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 2
    property int page03 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 3
    property int page04 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 4
    property int page05 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 5
    property int page06 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 6
    property int page07 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 7
    property int page08 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 8
    property int page09 : (((currentPageIdx / pageCntPerSceen) >> 0) * pageCntPerSceen) + 9

    signal signalEventMovePage(int pageIdx)

    id: compnonet
    width : 1518
    height: 100

    RowLayout{
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        spacing: 10
        anchors.fill: parent
        UiButton{
            textValue: qsTr("First")
            isDisable: totalPageCnt == 0
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(0)
            }
        }

        UiButton{
            textValue: qsTr("Pre")
            isDisable: page01 === 1
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page01 - 2)
            }
        }

        UiToggleBtn{
            textValue: page01
            isOn: page01 == currentPageIdx + 1 ? true : false
            isDisable: page01 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page01 - 1)
            }
        }

        UiToggleBtn{
            textValue: page02
            isOn: page02 == currentPageIdx + 1 ? true : false
            isDisable: page02 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page02 - 1)
            }
        }

        UiToggleBtn{
            textValue: page03
            isOn: page03 == currentPageIdx + 1 ? true : false
            isDisable: page03 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page03 - 1)
            }
        }

        UiToggleBtn{
            textValue: page04
            isOn: page04 == currentPageIdx + 1 ? true : false
            isDisable: page04 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page04 - 1)
            }
        }

        UiToggleBtn{
            textValue: page05
            isOn: page05 == currentPageIdx + 1 ? true : false
            isDisable: page05 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page05 - 1)
            }
        }

        UiToggleBtn{
            textValue: page06
            isOn: page06 == currentPageIdx + 1 ? true : false
            isDisable: page06 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page06 - 1)
            }
        }

        UiToggleBtn{
            textValue: page07
            isOn: page07 == currentPageIdx + 1 ? true : false
            isDisable: page07 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page07 - 1)
            }
        }

        UiToggleBtn{
            textValue: page08
            isOn: page08 == currentPageIdx + 1 ? true : false
            isDisable: page08 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page08 - 1)
            }
        }

        UiToggleBtn{
            textValue: page09
            isOn: page09 == currentPageIdx + 1 ? true : false
            isDisable: page09 > totalPageCnt
            Layout.preferredWidth: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page09 - 1)
            }
        }

        UiButton{
            textValue: qsTr("Next")
            isDisable: page09 >= totalPageCnt
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(page09)
            }
        }

        UiButton{
            textValue: qsTr("Last")
            isDisable: totalPageCnt == 0
            Layout.preferredWidth: 3
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSignalEventClicked: {
                compnonet.signalEventMovePage(totalPageCnt - 1)
            }
        }
    }
}
