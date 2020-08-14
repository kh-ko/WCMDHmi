pragma Singleton
import QtQuick 2.0

Item {

    property  alias godoBName: godoB.name
    property  alias digitalName: digital.name
    property  alias nanumGothicName: nanumGothic.name
    property  alias nanumGothicBName: nanumGothicB.name

    FontLoader{
        id: godoB
        source: "qrc:uiengine/font/GodoB.ttf"
    }

    FontLoader{
        id: digital
        source: "qrc:uiengine/font/digital-7.ttf"
    }

    FontLoader{
        id: nanumGothic
        source: "qrc:uiengine/font/NanumBarunGothic.ttf"
    }

    FontLoader{
        id: nanumGothicB
        source: "qrc:uiengine/font/NanumBarunGothicBold.ttf"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
