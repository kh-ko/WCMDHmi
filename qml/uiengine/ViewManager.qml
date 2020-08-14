pragma Singleton
import QtQuick 2.0
import "../ui/main_scene/."
Item {
    property  var windows : null
    property MainScene mainScene : null
    property PopupTrendsOption popupTrendsOption : null
    property PanelVKeypad keypad : null
    property PanelToastMessage  toast : null
    property PopupConfirm popupConfirm : null
    property var locale : Qt.locale("en-US")
    property color defaultColor : "#FFFFFF"
    property color systemLabelColor : "#ACACAC"
    property color mainColor : "#0085FF"
    property color warningColor : "#F59A23"
    property color errorColor : "#D9001B"
    property color disableColor : "#3B3B3B"
    property color bgColor :  "#131313"
    property color panelColor :  "#232323"
    property color panelBtnColor :  "#333333"
    property color popupColor :  "#434343"
    property color popupBtnColor :  "#535353"
    property color selPanelColor :  "#00294F"
    property color popuplInputColor : "#393939"
    property color panelInputColor : "#1C1C1C"
    property color panelSelInputColor : "#00203E"

    function setWindows(win)
    {
        windows = win;
    }

    function setMainScene(value)
    {
        mainScene = value
    }

    function setKeypad(value)
    {
        keypad = value;
    }

    function setToast(value)
    {
        toast = value
    }

    function setPopupTrendsOption(value){
        popupTrendsOption = value;
    }

    function setPopupConfirm(value){
        popupConfirm = value;
    }

    function getWidth()
    {
        return 1920;
    }

    function getHeight()
    {
       return 1080;
    }

    function isWindowOs()
    {
        return false;
    }

    function minimizeWindow()
    {
        windows.minimizeWindow();
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
