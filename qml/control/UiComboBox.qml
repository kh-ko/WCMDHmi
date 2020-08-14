import QtQuick 2.0
import QtGraphicalEffects 1.0
import "."
import QtQuick.Controls 2.3
import ViewManager 1.0
import FontManager 1.0
import MouseEventSpy 1.0

Item {
    property ListModel listModel

    property bool      isUpMode : false
    property bool      isHighlight: false
    property bool      isPressed: false
    property bool      isDisable : false
    property bool      isExtend : false
    property color     bgColor  : "#232323"
    property string    labelText : ""
    property int       comboWidth : -1


    property int       selIdx : 0

    signal signalEventChangedSel(int itemIdx)

    id:control

    width : 220
    height : 60

    UiLabelSystem
    {
        id : label
        width: parent.width - comboWidth
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter

        visible: comboWidth === -1 ? false : true
        textValue: labelText
    }


    Rectangle{
        id :bg
        color: control.bgColor
        radius: 20
        border.width: 0
        width: comboWidth === -1 ? parent.width : comboWidth
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        visible: false
    }

    InnerShadow{
        anchors.fill: bg
        horizontalOffset: 5
        verticalOffset: 5
        radius: 5.0
        samples: 17
        color: "#59000000"
        source: bg
        cached: true

        visible: !isDisable
    }

    Rectangle{
        id :bgShadow
        anchors.fill: bg
        color: "#20000000"
        radius: 20
        border.width: 0

        //visible: !control.isDisable
    }

    Text{
        id:selectedValue
        anchors.verticalCenter: bg.verticalCenter
        anchors.left: bg.left
        anchors.leftMargin: 20
        anchors.right: btnExtend.left
        anchors.rightMargin: 20

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment : Text.AlignLeft
        font.pixelSize: 25
        font.family: FontManager.nanumGothicName
        elide: Text.ElideRight

        color : isHighlight ? "#0085FF" : "#FFFFFF"
        text: listModel.get(selIdx).itemText
    }

    Rectangle{
        id : btnExtend
        width : height
        anchors.right: bg.right
        anchors.rightMargin: 2
        anchors.top: bg.top
        anchors.topMargin: 2
        anchors.bottom: bg.bottom
        anchors.bottomMargin: 2

        color : control.bgColor
        radius: 20
        border.width: 0

        Image{
            rotation: control.isExtend ? 180 : 0
            source: "img_uicombobox/down_01.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        visible: false
    }

    DropShadow {
        anchors.fill: btnExtend
        horizontalOffset: 2
        verticalOffset: 2
        radius: 2
        samples: 17
        color: "#000000"
        source: btnExtend
        visible: !control.isDisable
    }

    Rectangle {

        property bool isHover : mouseAreaBg.containsMouse
        id: panelExtend
        visible: control.isExtend
        color: "#d9000000"
        radius: bg.radius
        border.width: 1
        border.color: "#39000000"
        anchors.top: isUpMode ? undefined : bg.bottom
        anchors.topMargin: isUpMode ? undefined :10
        anchors.bottom: isUpMode ? bg.top : undefined
        anchors.bottomMargin: isUpMode ? 10 :undefined
        anchors.left: bg.left
        anchors.leftMargin: 0
        anchors.right: bg.right
        anchors.rightMargin: 0
        height: (control.listModel.count * 60) + 40

        MouseArea{
            id : mouseAreaBg
            anchors.fill: parent

            onPressed: { panelExtend.isHover = true}
            onReleased: { panelExtend.isHover = false}
        }

        ListView {
            id: productList
            spacing: 0
            interactive: false
            anchors.fill : parent
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            model: control.listModel
            clip: true

            delegate: Rectangle{
                id : comboItem
                height: 60
                radius: 10
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                color : "#00000000"

                UiLabelContent
                {
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    textValue : itemText
                }

                MouseArea{
                    id : mouseAreaItem
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: {panelExtend.isHover = true ; parent.color = "#33000000"}
                    onReleased: {panelExtend.isHover = false;  parent.color = "#00000000"}
                    onClicked: {control.isExtend = false; control.signalEventChangedSel(itemIdx);}
                }
            }
        }
    }

    MouseArea{
        anchors.fill: bg
        onPressed: {if(control.isDisable)return; panelExtend.isHover = true ; control.isPressed = true;}
        onReleased:{if(control.isDisable)return; panelExtend.isHover = false; control.isPressed = false;}
        onClicked: {if(control.isDisable)return; control.isExtend = !control.isExtend; }
    }

    Connections {
        target: MouseEventSpy
        onMouseEventDetected: {

            if(panelExtend.isHover == false)
            {
                control.isExtend = false
            }
        }
    }
}



