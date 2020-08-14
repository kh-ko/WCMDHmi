import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import EnumDefine 1.0
import ViewManager 1.0
import FontManager 1.0
import MainViewModel 1.0
import "../../control/"
import PanelDebuggingModel 1.0
import MainSceneModel 1.0

Rectangle {
    property MainSceneModel mainSceneModel : null

    id: panel
    color: "#59000000"
    border.width: 0

    width: 1920
    height: 1080

    visible: false

    MouseArea{
        anchors.fill: parent

        onClicked: {}
    }

    PanelDebuggingModel{
        id: debuggingModel
    }

    Rectangle
    {
        id: rectangle1
        width: 1500
        height: 901
        radius: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#d9000000"
        border.width: 0

        UiLabelTitle{
            width: 200
            height: 60
            textValue: qsTr("Alarm State")
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40
        }

        Text{
            width: 200
            height: 60
            color: mainSceneModel.IsSensorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("Sensor alarm")
            anchors.topMargin: 102

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 40
        }


        Text
        {
            width: 200
            height: 60
            color: mainSceneModel.IsPhotoAlarm ? "#FF0000" :"#acacac"
            text: qsTr("Photo alarm")
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 102
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 246
        }

        Text
        {
            width: 200
            height: 60
            color: mainSceneModel.IsMortorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("Motor alarm")
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 102
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 463
            elide: Text.ElideRight
        }

        UiLabelTitle {
            width: 200
            height: 60
            anchors.left: parent.left
            anchors.top: parent.top
            textValue: qsTr("DSP Setting")
            anchors.topMargin: 193
            anchors.leftMargin: 40
        }

        Text {
            width: (parent.width - 80) / 3
            height: 40
            color: debuggingModel.mDiffLampTime ? "#FF0000" :"#acacac"
            text: qsTr("Lamp time : ") + debuggingModel.mLampTime.toLocaleString(ViewManager.locale, 'f', 0) + " ms"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 259
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffBuzzerTime ? "#FF0000" :"#acacac"
            text: qsTr("Buzzer time : ") + debuggingModel.mBuzzerTime.toLocaleString(ViewManager.locale, 'f', 0) + " ms"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 304
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 40
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffSpeedConverter ? "#FF0000" :"#acacac"
            text: qsTr("m/min → Hz : ") + debuggingModel.mSpeedConverter.toLocaleString(ViewManager.locale, 'f', 0)
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 350
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMotorDirection ? "#FF0000" :"#acacac"
            text: qsTr("Transfer direction : ") + (debuggingModel.mMotorDirection == EnumDefine.MOTOR_DIRECTION_LEFT_TO_RIGHT ? "Left -> Rigth" : "Left <- Right")
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 397
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }

        /*
        Text {
            width: 483
            height: 40
            color: debuggingModel.mDiffIsDebugMode ? "#FF0000" :"#acacac"
            text: qsTr("Is Debug Mode : ") + (debuggingModel.mIsDebugMode ? "true" : "false")
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 443
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }
        */
        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffSensorLength ? "#FF0000" :"#acacac"
            text: qsTr("Loadcell length : ") + debuggingModel.mSensorLength.toLocaleString(ViewManager.locale, 'f', 0) + " mm"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 443
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 40
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDistanceToRejector ? "#FF0000" :"#acacac"
            text: qsTr("Dist to rejector : ") + debuggingModel.mDistanceToRejector.toLocaleString(ViewManager.locale, 'f', 0) + " mm"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 489
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffRejectorRunTimeRatio ? "#FF0000" :"#acacac"
            text: qsTr("Rejector run time ratio : ") + (debuggingModel.mRejectorRunTimeRatio/ 10) + " %"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 627
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 40
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffStaticFactor ? "#FF0000" :"#acacac"
            text: qsTr("Static factor : ") + debuggingModel.mStaticFactor
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 673
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDynamicFactor ? "#FF0000" :"#acacac"
            text: qsTr("Dynamic factor : ") + debuggingModel.mDynamicFactor
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 718
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 40
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffScaler ? "#FF0000" :"#acacac"
            text: qsTr("Display unit : ") + debuggingModel.mScaler.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 758
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 40
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDisplayStability ? "#FF0000" :"#acacac"
            text: qsTr("Display stability : ") + (debuggingModel.mDisplayStability/ 10) + " %"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 804
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 40
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMeasureCueSign ? "#FF0000" :"#acacac"
            text: qsTr("Measure cue sign : ") + debuggingModel.mMeasureCueSign.toLocaleString(ViewManager.locale, 'f', 0) + " ms"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 259
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 519
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMinStaticWeight ? "#FF0000" :"#acacac"
            text: qsTr("Min static weight : ") + debuggingModel.mMinStaticWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 305
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 519
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMinStaticWeight ? "#FF0000" :"#acacac"
            text: qsTr("Min dynamic weight : ") + debuggingModel.mMinDynamicWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 351
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 519
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMode ? "#FF0000" :"#acacac"
            text: qsTr("Metal detect mode : ") +(debuggingModel.mMode === EnumDefine.INDEPENDENT ? "Independent" : "noise reduction")
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 397
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 524
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDistanceBtwSensor ? "#FF0000" :"#acacac"
            text: qsTr("Distance btw sensor : ") + debuggingModel.mDistanceBtwSensor.toLocaleString(ViewManager.locale, 'f', 0) + " mm"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 443
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 519
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDetectDetectTime ? "#FF0000" :"#acacac"
            text: qsTr("Detect-Detect time : ") + debuggingModel.mDetectDetectTime.toLocaleString(ViewManager.locale, 'f', 0) + " ms"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 489
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 519
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffRunDetectTime ? "#FF0000" :"#acacac"
            text: qsTr("Run-Detect time : ") + debuggingModel.mRunDetectTime.toLocaleString(ViewManager.locale, 'f', 0) + " ms"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 535
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 519
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDistanceToWeightChecker ? "#FF0000" :"#acacac"
            text: qsTr("Dist to weight checker : ") + debuggingModel.mDistanceToWeightChecker.toLocaleString(ViewManager.locale, 'f', 0) + " mm"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 581
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 524
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDistancePhotoToSensor ? "#FF0000" :"#acacac"
            text: qsTr("Dist btw photo to sensor : ") + debuggingModel.mDistancePhotoToSensor.toLocaleString(ViewManager.locale, 'f', 0) + " mm"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 627
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 524
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffSignalDelayTime ? "#FF0000" :"#acacac"
            text: qsTr("Signal delay time : ") + debuggingModel.mSignalDelayTime.toLocaleString(ViewManager.locale, 'f', 0) + " ms"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 673
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 524
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffSeq ? "#FF0000" :"#acacac"
            text: qsTr("Product seq :") + debuggingModel.mSeq
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 259
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 1003
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffSpeed ? "#FF0000" :"#acacac"
            text: qsTr("Speed : ") + debuggingModel.mSpeed + " m/min"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 351
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 1003
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffNormalWeight ? "#FF0000" :"#acacac"
            text: qsTr("Normal weight : ") + debuggingModel.mNormalWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 397
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 1003
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffUnderWeight ? "#FF0000" :"#acacac"
            text: qsTr("Under weight : ") + debuggingModel.mUnderWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 443
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 1003
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffUnderWarningWeight ? "#FF0000" :"#acacac"
            text: qsTr("Under warning weight : ") + debuggingModel.mUnderWarningWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 489
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 1003
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffOverWarningWeight ? "#FF0000" :"#acacac"
            text: qsTr("Over warning weight : ") + debuggingModel.mOverWarningWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 535
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 1003
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffOverWeight ? "#FF0000" :"#acacac"
            text: qsTr("Over weight : ") + debuggingModel.mOverWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 581
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 1003
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffTareWeight ? "#FF0000" :"#acacac"
            text: qsTr("Tare weight : ") + debuggingModel.mTareWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 627
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 1003
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffWCNGMotion ? "#FF0000" :"#acacac"
            text: qsTr("Weight NG motion : ") + (debuggingModel.mWCNGMotion === EnumDefine.NG_MOTION_NON ? "None" : debuggingModel.mWCNGMotion === EnumDefine.NG_MOTION_STOP ? "Stop" : debuggingModel.mWCNGMotion === EnumDefine.NG_MOTION_REJECT_01 ? "Rejecter 01" : debuggingModel.mWCNGMotion === EnumDefine.NG_MOTION_REJECT_02 ? "Rejector 02" : "Unknow")
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 673
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 1003
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMDSenstivity ? "#FF0000" :"#acacac"
            text: qsTr("Metal senstivity : ") + debuggingModel.mMDSenstivity
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 713
            horizontalAlignment: Text.AlignLeft
            anchors.leftMargin: 1003
            elide: Text.ElideRight
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMDNGMotion ? "#FF0000" :"#acacac"
            text: qsTr("Metal NG motion : ") + (debuggingModel.mMDNGMotion === EnumDefine.NG_MOTION_NON ? "None" : debuggingModel.mMDNGMotion === EnumDefine.NG_MOTION_STOP ? "Stop" : debuggingModel.mMDNGMotion === EnumDefine.NG_MOTION_REJECT_01 ? "Rejecter 01" : debuggingModel.mMDNGMotion === EnumDefine.NG_MOTION_REJECT_02 ? "Rejector 02" : "Unknow")
            font.family: FontManager.nanumGothicName
            anchors.top: parent.top
            anchors.left: parent.left
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 758
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.leftMargin: 1003
        }

        UiButton{
            height: 60
            textValue: qsTr("Close")
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            type : EnumDefine.BUTTON_TYPE_BLUE

            onSignalEventClicked:
            {
                panel.visible = false
            }
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffMDPhotoIsOn ? "#FF0000" :"#acacac"
            text: qsTr("MD Photo mode on : ") + (debuggingModel.mMDPhotoIsOn ? "true" : "false")
            anchors.topMargin: 535
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            font.pixelSize: 25
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 40
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffWCPhotoIsOn ? "#FF0000" :"#acacac"
            text: qsTr("WC Photo mode on : ") + (debuggingModel.mWCPhotoIsOn ? "true" : "false")
            anchors.topMargin: 581
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            elide: Text.ElideRight
            font.pixelSize: 25
            anchors.leftMargin: 40
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffStaticStandardWeight ? "#FF0000" :"#acacac"
            text: qsTr("Std Weight : ") + debuggingModel.mStaticStandardWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            anchors.topMargin: 713
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            font.pixelSize: 25
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 524
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDynamicBaseWeight ? "#FF0000" :"#acacac"
            text: qsTr("Dynamic Std Weight : ") + debuggingModel.mDynamicBaseWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            anchors.topMargin: 759
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            elide: Text.ElideRight
            font.pixelSize: 25
            anchors.leftMargin: 524
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffSensorCnt ? "#FF0000" :"#acacac"
            text: qsTr("SensorCnt : ") + debuggingModel.mSensorCnt + " EA"
            anchors.topMargin: 305
            anchors.top: parent.top
            horizontalAlignment: Text.AlignLeft
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            font.pixelSize: 25
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 1003
        }

        Text {
            width: 473
            height: 40
            color: debuggingModel.mDiffDynamicBaseWeight ? "#FF0000" :"#acacac"
            text: qsTr("Dynamic Std Weight : ") + debuggingModel.mDynamicBaseWeight.toLocaleString(ViewManager.locale, 'f', 0) + " mg"
            font.family: FontManager.nanumGothicName
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 805
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            font.pixelSize: 25
            anchors.leftMargin: 524
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
