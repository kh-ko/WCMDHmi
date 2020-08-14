import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.11

Item {

    id : control
    width: 20
    height: 20

    property alias itemColor : trianglePath.fillColor

    Shape {
        id : triangle
        layer.samples: 16
        layer.enabled: true
        //vendorExtensionsEnabled: false
        //layer.smooth: true
        antialiasing: true
        anchors.fill: parent

        ShapePath {
            id : trianglePath
            strokeColor: "#00000000"
            strokeWidth: 0
            capStyle: ShapePath.RoundCap
            startX: 0; startY: control.height
            PathLine { x: 0; y: control.height }
            PathLine { x: control.width; y: 0 }
            PathLine { x: control.width; y: control.height }

        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:6}
}
##^##*/
