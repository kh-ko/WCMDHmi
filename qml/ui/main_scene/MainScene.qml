import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import FontManager 1.0
import EnumDefine 1.0
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

        currView = "factoryresetView";
        viewContainer.clear();
        viewContainer.push(factoryResetView,{"isOnlyEvent" : value})
    }

    function moveProductView()
    {
        popupProductSettingInHome.close();

        currView = "menuView";
        viewContainer.clear();
        viewContainer.push(menuView, {"isProductVew" : true, "selMenu" : EnumDefine.MENU_PRODUCT_SETTING})
    }

    function moveLoggingDataView(selDevice)
    {
        popupProductSettingInHome.close();

        currView = "menuView";
        viewContainer.clear();
        viewContainer.push(menuView, {"selDevice" : selDevice, "selMenu" : EnumDefine.MENU_LOGGING_DATA, "isLoggingVew" : true})
    }

    function moveMenuView(selDevice, selMenu, isSuper)
    {
        popupProductSettingInHome.close();

        currView = "menuView";
        viewContainer.clear();
        viewContainer.push(menuView, {"selDevice" : selDevice, "selMenu" : selMenu, "isSuper" : isSuper})
    }

    function moveMainView()
    {
        popupProductSettingInHome.close();

        currView = "mainView"
        viewContainer.clear();
        viewContainer.push(mainView)
    }

    function showMDSetting()
    {
        console.debug("showMDSetting")
        scene.toSettingMenuName = "Metal"
        inputPassword.textValue = ""
        ViewManager.keypad.showKeypad(inputPassword.getVInputText())
    }

    function showWCSetting()
    {
        scene.toSettingMenuName = "Weight"
        inputPassword.textValue = ""
        ViewManager.keypad.showKeypad(inputPassword.getVInputText())
    }


    Component.onCompleted: {
        console.debug("[MainScene.qml] : Create");

        currView = "mainView";
        ViewManager.setMainScene(scene);
        ViewManager.setPopupTrendsOption(popupTrendsOption);
        ViewManager.setKeypad(keypad);
        ViewManager.setToast(toast);
        ViewManager.setPopupConfirm(popupConfirm);
    }

    Component.onDestruction:
    {
        console.debug("[MainScene.qml] : Destruct");
    }

    MainSceneModel{
        id : model
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

        textCompany : model.company
        textTel: model.tel
        textClock: model.clock
        isRun: model.isRun
        isComm : model.isComm
        isAlarm : model.isAlarm
        isNeedBackup : paenlBackup.isNeedBackup
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

            popupSelMenu.visible = true;
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

    PopupTrendsOption
    {
        id : popupTrendsOption
        anchors.fill: parent
    }

    PopupSelectMenu
    {
        id : popupSelMenu
        anchors.fill: parent

        onSignalEventClose: {

            if(scene.isLock)
            {
                menuPassword.textValue = ""
                ViewManager.keypad.showKeypad(menuPassword.getVInputText())
            }
            else
            {
                moveMenuView(popupSelMenu.selDevice , EnumDefine.MENU_PRODUCT_SETTING, scene.isSuper)
            }
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
                    moveMenuView(popupSelMenu.selDevice, EnumDefine.MENU_PRODUCT_SETTING, true)
                }
                else if(model.onCommandComparePwd(value))
                {
                    moveMenuView(popupSelMenu.selDevice, EnumDefine.MENU_PRODUCT_SETTING, false)
                }
                else
                {
                    toast.show(qsTr("Please check password"));
                }
            }
        }
    }

    PopupConfirm
    {
        id : popupConfirm
        anchors.fill: parent
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
