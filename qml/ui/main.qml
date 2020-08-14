import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import ViewManager 1.0
import MainModel 1.0
import "intro_scene/"
import "main_scene/"
//import "factoryreset_scene/"

Window {
    id: window
    visible: true
    width: ViewManager.getWidth();
    height: ViewManager.getHeight();
    title: "Weight cheker and alu scan"

    flags : ViewManager.isWindowOs() ? Qt.Window:  Qt.FramelessWindowHint

    function moveScene(sceneName)
    {
        console.debug("moveScene")

        sceneContainer.clear();

        if(sceneName === "introScene")
            sceneContainer.push(introScene);
        else if(sceneName === "mainScene")
            sceneContainer.push(mainScene);
        //else if(sceneName === "factoryResetScene")
        //    sceneContainer.push(factoryResetScene);
    }

    function minimizeWindow()
    {
        window.showMinimized()
    }

    function onSizeChanged()
    {
        sceneContainer.scale = window.height / ViewManager.getHeight();
        sceneContainer.width = window.width / sceneContainer.scale;
    }

    onWidthChanged: {window.onSizeChanged()}
    onHeightChanged: {window.onSizeChanged()}

    onVisibilityChanged:
    {
        if(visibility === Window.Windowed && ViewManager.isWindowOs() === false)
            window.showFullScreen();
    }

    Component.onCompleted:
    {
        console.debug("create")

        ViewManager.setWindows(window);

        if(ViewManager.isWindowOs() === false)
            window.showFullScreen();
    }

    Component.onDestruction:
    {
        console.debug("[main.qml] destroy")
    }

    MainModel
    {
        id : model
    }

    Rectangle{
        anchors.fill: parent
        color : "#000000"
    }

    StackView
    {
        id: sceneContainer
        width: ViewManager.getWidth()
        height: ViewManager.getHeight()
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        initialItem: introScene

        Component
        {
            id : introScene

            IntroScene
            {
                onSignalNotifyCompleted:
                {
                    window.moveScene("mainScene");
                }
            }
        }

        Component
        {
            id : mainScene

            MainScene{
                //onSignalEventClickFactoryReset: {
                //    window.moveScene("factoryResetScene");
                //}
            }
        }
    }
/*
    Component
    {
        id : factoryResetScene;

        FactoryResetScene
        {
            onSignalEventCompletedFactoryReset: {
                window.moveScene("introScene");
            }
        }
    }
    */
/*
    PopupPanel
    {
        id : popup
    }*/

}


/*##^##
Designer {
    D{i:1;anchors_height:0;anchors_width:0}
}
##^##*/
