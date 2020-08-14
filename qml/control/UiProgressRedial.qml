import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Shapes 1.11

Item {
    property alias arcWidth : angelArcPath.strokeWidth
    property alias itemColor : angelArcPath.strokeColor
    property alias bgColor : bgAngelArcPath.strokeColor
    property real min : 10
    property real max : 20
    property real value : 15

    property real barArc : value < min ? 0.01 : value > max ? 270 : ((value - min) / (max - min)) * 270

    id : control
    width: 200
    height: 200
    antialiasing: true

    Shape{
        id : shape

        layer.samples: 16
        layer.enabled: true
        anchors.fill: parent

        ShapePath{
            id : bgAngelArcPath
            fillColor: "#00000000"
            strokeWidth: angelArcPath.strokeWidth

            capStyle: ShapePath.RoundCap


            startX: control.width - (control.arcWidth / 2)
            startY: control.height / 2
            PathAngleArc {
                moveToStart: true
                startAngle: 135
                sweepAngle: 270
                centerX: control.width / 2; centerY: control.height / 2
                radiusX: (control.width - control.arcWidth) / 2; radiusY: (control.height - control.arcWidth) / 2
            }
        }

        ShapePath{
            id : angelArcPath
            fillColor: "#00000000"
            strokeWidth: 10
            capStyle: ShapePath.RoundCap

            startX: control.width - (control.arcWidth / 2)
            startY: control.height / 2
            PathAngleArc {
                moveToStart: true
                startAngle: 135
                sweepAngle : control.barArc
                centerX: control.width / 2; centerY: control.height / 2
                radiusX: (control.width - control.arcWidth) / 2; radiusY: (control.height - control.arcWidth) / 2
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/
