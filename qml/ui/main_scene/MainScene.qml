import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.4
import QtQuick.VirtualKeyboard.Settings 2.2
import ViewManager 1.0
import FontManager 1.0
import EnumDef 1.0
import QmlEnumDef 1.0
import "."
import "../../control/"
import "./main_view"
import "./menu_view"
import "./factoryreset_view"
import MainSceneModel 1.0

Item {
    property bool   isLock  : true
    property bool   isSuper : false
    property string currView : "mainView"
    property bool   isPreView : true
    property string toSettingMenuName : ""
    property var    selDevLoggingMenu : QmlEnumDef.DEVICE_METAL_DETECTOR
    property var    selDevGraphMenu   : QmlEnumDef.DEVICE_METAL_DETECTOR

    id: scene
    width : 1920
    height: 1080

    function backupData()
    {
        paenlBackup.backup()
    }

    function factoryReset(value)
    {
        popupProductSettingInHome.close();
        popupGroupSettingInHome.close();

        currView = "factoryresetView";
        viewContainer.clear();
        viewContainer.push(factoryResetView,{"isOnlyEvent" : value})
    }

    function moveProductView()
    {
        popupProductSettingInHome.close();
        popupGroupSettingInHome.close();

        currView = "menuView";
        viewContainer.clear();
        viewContainer.push(menuView, {"isProductVew" : true, "selMenu" : QmlEnumDef.MENU_PRODUCT_SETTING})
    }

    function moveLoggingDataView()
    {
        popupProductSettingInHome.close();
        popupGroupSettingInHome.close();

        currView = "menuView";
        viewContainer.clear();
        viewContainer.push(menuView, {"isWCEnable" : model.isWCEnable, "isMDEnable" : model.isMDEnable, "selMenu" : QmlEnumDef.MENU_LOGGING_DATA, "isLoggingVew" : true})
    }

    function moveMenuView(selMenu, isSuper)
    {
        popupProductSettingInHome.close();
        popupGroupSettingInHome.close();

        currView = "menuView";
        viewContainer.clear();
        viewContainer.push(menuView, {"isWCEnable" : model.isWCEnable, "isMDEnable" : model.isMDEnable, "selMenu" : selMenu, "isSuper" : isSuper})
    }

    function moveMainView()
    {
        popupProductSettingInHome.close();
        popupGroupSettingInHome.close();

        currView = "mainView"
        viewContainer.clear();
        viewContainer.push(mainView)
    }

    function showMDSetting()
    {
        console.debug("showMDSetting")
        scene.toSettingMenuName = "Metal"
        inputPassword.textValue = ""
        //ViewManager.keypad.showKeypad(inputPassword.getVInputText())
        popupProductSettingInHome.showMDSetting()
    }

    function showWCSetting()
    {
        scene.toSettingMenuName = "Weight"
        inputPassword.textValue = ""
        //ViewManager.keypad.showKeypad(inputPassword.getVInputText())
        popupProductSettingInHome.showWCSetting()
    }

    function showGroupSetting()
    {
        scene.toSettingMenuName = "Group"
        inputPassword.textValue = ""
        //ViewManager.keypad.showKeypad(inputPassword.getVInputText())
        popupGroupSettingInHome.show()
    }


    Component.onCompleted: {
        console.debug("[MainScene.qml] : Create");

        currView = "mainView";

        ViewManager.weightFixedN = model.weightFixedN;
        ViewManager.setMainScene(scene);
        ViewManager.setPopupTrendsOption(popupTrendsOption);
        ViewManager.setKeypad(keypad);
        ViewManager.setCalendar(calendar);
        ViewManager.setToast(toast);
        ViewManager.setPopupConfirm(popupConfirm);
    }

    Component.onDestruction:
    {
        console.debug("[MainScene.qml] : Destruct");
    }

    MainSceneModel{
        id : model

        Component.onCompleted: {
            VirtualKeyboardSettings.locale = (language === EnumDef.LANG_ENG ? "en_GB" : "ko_KR")
        }

        onSignalEventChangedWeightFixedN :
        {
            ViewManager.weightFixedN = model.weightFixedN;
        }

        onLanguageChanged:
        {
            VirtualKeyboardSettings.locale = (language === EnumDef.LANG_ENG ? "en_GB" : "ko_KR")
        }

        onSignalEventChangedIsWait: {

            if(model.isWCEnable)
            {
                if(isWait)
                {
                    popupZeroProc.open()
                }
                else
                {
                    popupZeroProc.close()
                }
            }
        }
    }

    Rectangle{
        id : background
        color : isPreView? "#131313" : ViewManager.bgColor
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
    }

    PanelStatusBar
    {
        id : statusBar
        height: 63
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        currWeight  : (model.wcCurrWeight / 1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
        textCompany : model.company
        textTel: model.tel
        textClock: model.clock
        isZeroProc: model.isZeroProc
        isRun: model.isRun
        isComm : model.isComm
        isAlarm : model.isAlarm
        isInet: model.isInet
        isNeedBackup : paenlBackup.isNeedBackup
        isWCEnable : model.isWCEnable
        isPrinterEnable : model.isEanblePrinter
        isConnectedPrinter : model.isConnectedPrinter
        onSignalEventAlarmClicked :{
            panelDebug.visible = true;
        }
    }

    StackView
    {
        id: viewContainer
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: mainButtonPanel.left
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: statusBar.bottom
        anchors.topMargin: 10

        initialItem: mainView
    }


    PanelMainButton
    {
        id : mainButtonPanel
        width : 140
        anchors.top: statusBar.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        visiblePowerOff:  model.swPowerOff
        visible: scene.currView != "factoryresetView"

        onSignalEventHomeClicked: {
            if(currView == "mainView")
                return;

            moveMainView();
        }

        onSignalEventRunClicked: {
            model.onCommandSetRun(true);
        }

        onSignalEventStopClicked: {
            model.onCommandSetRun(false);
        }

        onSignalEventMenuClicked: {

            if(currView == "menuView")
                return;

            menuPassword.textValue = ""
            ViewManager.keypad.showKeypad(menuPassword.getVInputText())
        }

        onSignalEventShutdownClicked: {
            model.onCommandShutdown();
        }

/*
        onSignalEventLockClicked: {

            if(scene.isLock === true)
            {
                inputPassword.textValue = ""
                ViewManager.keypad.showKeypad(inputPassword.getVInputText())
                return;
            }

            scene.isSuper = false
            scene.isLock = true
        }
        */
    }

    UiInputPassword{
        id : inputPassword
        width: 0
        height: 0
        textValue: ""
        labelText : qsTr("Please enter your password.")

        onSignalChangeText: {
            if(model.onCommandCompareAdminPwd(value) || model.onCommandComparePwd(value))
            {
                if(scene.toSettingMenuName == "Metal")
                {
                    popupProductSettingInHome.showMDSetting()
                }
                else if(scene.toSettingMenuName == "Weight")
                {
                    popupProductSettingInHome.showWCSetting()
                }
                else if(scene.toSettingMenuName == "Group")
                {
                    popupGroupSettingInHome.show()
                }
            }
            else
            {
                toast.show(qsTr("Please check password"));
            }
        }
    }

    PanelBackup
    {
        id : paenlBackup
    }

    PopupProductSettingInHome{
        id : popupProductSettingInHome
        anchors.fill: parent
    }

    PopupGroupSettingInHome{
        id : popupGroupSettingInHome
        anchors.fill: parent
    }

    PopupTrendsOption
    {
        id : popupTrendsOption
        anchors.fill: parent
    }

    UiInputPassword{
        id : menuPassword
        width: 0
        height: 0
        textValue: ""
        labelText : qsTr("Please enter your password.")

        onSignalChangeText:
        {
            if(model.onCommandCompareAdminPwd(value))
            {
                moveMenuView(QmlEnumDef.MENU_PRODUCT_SETTING, true)
            }
            else if(model.onCommandComparePwd(value))
            {
                moveMenuView(QmlEnumDef.MENU_PRODUCT_SETTING, false)
            }
            else
            {
                toast.show(qsTr("Please check password"));
            }
        }
    }

    PopupConfirm
    {
        id : popupConfirm
        anchors.fill: parent
    }

    PopupZeroProc
    {
        id : popupZeroProc
    }

    PanelDebugging{
        id : panelDebug
        anchors.fill: parent
        mainSceneModel: model
    }

    PanelVKeypad
    {
        id : keypad
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
    }

    PanelCalendar
    {
        id : calendar
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

    }

    PanelToastMessage
    {
        id : toast
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

    }

    Component
    {
        id : mainView;

        MainView{
            anchors.fill: parent
        }
    }

    Component
    {
        id : menuView;

        MenuView{
            anchors.fill: parent
        }
    }

    Component
    {
        id : factoryResetView;

        FactoryResetView{
            anchors.fill: parent
            //onSignalEventClickFactoryReset: {
            //    scene.signalEventClickFactoryReset();
            //}
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:4;anchors_width:140}
}
##^##*/
