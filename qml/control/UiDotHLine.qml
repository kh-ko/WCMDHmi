import QtQuick 2.0

Item {
    id : control
    property color lineColor

    Component.onCompleted: {
        if(canvas.available )
        {
            canvas.requestPaint()
        }
    }

    Canvas{
        id: canvas

        anchors.fill: parent

        enabled: false
        antialiasing: false
        smooth: false

        renderTarget : Canvas.FramebufferObject


        onPaint :{

            var ctx = canvas.getContext("2d")

            ctx.reset();
            ctx.lineWidth = control.height
            ctx.strokeStyle = control.lineColor
            ctx.fillStyle = "#00000000"
            //ctx.lineCap = "round"
            ctx.setLineDash([0.5,0.5]);

            ctx.beginPath()
            ctx.moveTo(0,0);
            ctx.lineTo(control.width,0)
            ctx.stroke();

        }
    }
}
