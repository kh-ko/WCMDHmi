import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QmlEnumDef 1.0
import EnumDef 1.0
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
            id : alarmTitle
            width: 200
            height: 60
            textValue: qsTr("Alarm State")
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 40
        }

        Text{
            id : wcSensorAlarmValue
            height: 60
            color: mainSceneModel.isWCSensorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("WC Sensor alarm")

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.top: alarmTitle.bottom
            anchors.leftMargin: 40
        }


        Text
        {
            id : wcPhotoAlarmValue
            height: 60
            color: mainSceneModel.isWCPhotoAlarm ? "#FF0000" :"#acacac"
            text: qsTr("WC Photo alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: wcSensorAlarmValue.verticalCenter
            anchors.left: wcSensorAlarmValue.right; anchors.leftMargin: 40
        }

        Text
        {
            id : wcMotorAlarmValue
            height: 60
            color: mainSceneModel.isWCMortorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("WC Motor alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: wcSensorAlarmValue.verticalCenter
            anchors.left: wcPhotoAlarmValue.right; anchors.leftMargin: 40
        }

        Text
        {
            id : wcRJMotorAlarmValue
            height: 60
            color: mainSceneModel.isWCRJMortorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("WC RJ Motor alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: wcSensorAlarmValue.verticalCenter
            anchors.left: wcMotorAlarmValue.right; anchors.leftMargin: 40
        }

        Text
        {
            id : wcMeasureSectionAlarm
            height: 60
            color: mainSceneModel.isWCMeasureAlarm ? "#FF0000" :"#acacac"
            text: qsTr("WC Measure section alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: wcSensorAlarmValue.verticalCenter
            anchors.left: wcRJMotorAlarmValue.right; anchors.leftMargin: 40
        }

        Text{
            id : mdSensorAlarmValue
            height: 60
            color: mainSceneModel.isMDSensorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("MD Sensor alarm")

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.top: wcSensorAlarmValue.bottom
            anchors.leftMargin: 40
        }


        Text
        {
            id : mdPhotoAlarmValue
            height: 60
            color: mainSceneModel.isMDPhotoAlarm ? "#FF0000" :"#acacac"
            text: qsTr("MD Photo alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: mdSensorAlarmValue.verticalCenter
            anchors.left: mdSensorAlarmValue.right; anchors.leftMargin: 40
        }

        Text
        {
            id : mdMotorAlarmValue
            height: 60
            color: mainSceneModel.isMDMortorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("MD Motor alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: mdSensorAlarmValue.verticalCenter
            anchors.left: mdPhotoAlarmValue.right; anchors.leftMargin: 40
        }

        Text
        {
            id : mdRJMotorAlarmValue
            height: 60
            color: mainSceneModel.isMDRJMortorAlarm ? "#FF0000" :"#acacac"
            text: qsTr("MD RJ Motor alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: mdSensorAlarmValue.verticalCenter
            anchors.left: mdMotorAlarmValue.right; anchors.leftMargin: 40
        }

        Text
        {
            id : mdSpeedAlarm
            height: 60
            color: mainSceneModel.isMDSpeedAlarm ? "#FF0000" :"#acacac"
            text: qsTr("MD speed setting alarm")
            font.family: FontManager.nanumGothicName
            font.pixelSize: 25
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.verticalCenter: mdRJMotorAlarmValue.verticalCenter
            anchors.left: mdRJMotorAlarmValue.right; anchors.leftMargin: 40
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
            text: qsTr("Transfer direction : ") + (debuggingModel.mMotorDirection === EnumDef.MOTOR_DIRECTION_LEFT_TO_RIGHT ? "Left -> Rigth" : "Left <- Right")
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

        /*
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
        }   */

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
            text: qsTr("Metal detect mode : ") +(debuggingModel.mMode ===  EnumDef.SENS_MODE_INDEPENDENT ? "Independent" : "noise reduction")
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
            text: qsTr("Weight NG motion : ") + (debuggingModel.mWCNGMotion === EnumDef.NG_MOTION_NON ? "None" : debuggingModel.mWCNGMotion === EnumDef.NG_MOTION_STOP ? "Stop" : debuggingModel.mWCNGMotion === EnumDef.NG_MOTION_SORTER_01 ? "Sorter 01" : debuggingModel.mWCNGMotion === EnumDef.NG_MOTION_SORTER_02 ? "Sorter 02" : debuggingModel.mWCNGMotion === EnumDef.NG_MOTION_SORTER_03 ? "Sorter 03" : debuggingModel.mWCNGMotion === EnumDef.NG_MOTION_SORTER_04 ? "Sorter 04" : "Unknow")
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
            text: qsTr("Metal NG motion : ")  + (debuggingModel.mMDNGMotion === EnumDef.NG_MOTION_NON ? "None" : debuggingModel.mMDNGMotion === EnumDef.NG_MOTION_STOP ? "Stop" : debuggingModel.mMDNGMotion === EnumDef.NG_MOTION_SORTER_01 ? "Sorter 01" : debuggingModel.mMDNGMotion === EnumDef.NG_MOTION_SORTER_02 ? "Sorter 02" : debuggingModel.mMDNGMotion === EnumDef.NG_MOTION_SORTER_03 ? "Sorter 03" : debuggingModel.mMDNGMotion === EnumDef.NG_MOTION_SORTER_04 ? "Sorter 04" : "Unknow")
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
            type : QmlEnumDef.BUTTON_TYPE_BLUE

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
