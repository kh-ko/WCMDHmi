import QtQuick 2.12
import QtQuick.Controls 2.5
import IntroSceneModel 1.0
import QmlEnumDef 1.0

Item {
    property bool isSplashDone : false
    id: scene

    signal signalNotifyCompleted()

    IntroSceneModel{
        id : model

        onSignalEventChangedProgressValue: {
            if(isSplashDone === true && model.progressValue == 100)
            {
                signalNotifyCompleted();
            }
        }
    }

    ParallelAnimation {
        id :introAni

        NumberAnimation {
            target: splash
            properties: "opacity"
            duration: 1000
            from : 0.3
            to: 1.0
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: splash
            properties: "scale"
            duration: 1000
            to: 1.0
            from : 0.9
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: splash
            properties: "yPosition"
            duration: 1000
            from: 20
            to : 0
            easing.type: Easing.InOutQuad
        }

        onStopped:
        {
            isSplashDone = true;

            if(isSplashDone === true && model.progressValue == 100)
            {
                signalNotifyCompleted();
            }
        }
    }

    Component.onCompleted:
    {
        console.debug("Create")
        introAni.start();
        model.onCommandLoadLanguage();
    }

    Component.onDestruction:
    {
        console.debug("[IntroScene.qml] Destruct")
    }


    Rectangle
    {
        color: "#ffffff"
        anchors.fill: parent

        Image {
            property int yPosition

            id: splash
            width: parent.width
            height: parent.height
            anchors.verticalCenterOffset: yPosition
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            source: model.company === QmlEnumDef.COMPANY_NOVASEN? "novasen_logo.png": "DONGNAM-LOGO_FIT.jpg"
        }
    }

    BusyIndicator{
        x: 310
        y: 332
        width: 108
        height: 81
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        visible: isSplashDone
        running: true
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
