import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import FontManager 1.0
import EnumDefine 1.0
import "."
import "../../control/"

Item {

    width: 1920
    height: 1080

    function close()
    {
        settingContainer.clear();
    }

    function showMDSetting()
    {
        settingContainer.clear();
        settingContainer.push(mdSetting)
    }

    function showWCSetting()
    {
        settingContainer.clear();
        settingContainer.push(wcSetting)
    }

    StackView{
        id : settingContainer
        anchors.fill: parent
    }


    Component
    {
        id : mdSetting;

        PanelMDSettingInHome{
            anchors.fill: parent

            onSignalEventClose :
            {
                settingContainer.clear();
            }
        }
    }

    Component
    {
        id : wcSetting;

        PanelWCSettingInHome{
            anchors.fill: parent

            onSignalEventClose :
            {
                settingContainer.clear();
            }
        }
    }


}
