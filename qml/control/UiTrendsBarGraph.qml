import QtQuick 2.0

Item {
    id : control
    property var maxValue
    property var maxCnt


    clip: true

    function clearValue()
    {
        for(var i = 0; i < barContainer.children.length; i ++)
        {
            barContainer.children[i].value = 0;
        }
    }

    function addValue(idx, value, gradient)
    {
        if(idx > maxCnt - 1)
            return;

        var lastIdx = (barContainer.children.length);

        for(var i = lastIdx; i <= idx; i ++)
        {
            bar.createObject(barContainer, {"value":0, "idx":i, "gradient":gradient})
        }

        barContainer.children[idx].value =  value;
        barContainer.children[idx].gradient = gradient;
    }

    Rectangle{
        id : baseline
        height: 2
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        color: "#59FFFFFF"
    }

    Item{
        id : barContainer
        anchors.fill: parent

        onChildrenChanged:
        {
            for(var i = 0; i < barContainer.children.length; i ++)
            {
                barContainer.children[i].idx = i;
            }
        }
    }

    Component{
        id : bar

        Rectangle{
            property var value
            property var idx

            x : ((parent.width / control.maxCnt) * idx) + ((parent.width / control.maxCnt) / 2) - (width / 2)
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -1 * (width / 2)
            height: parent.height * (value / control.maxValue) + width / 2
            width : 20
            radius: width / 2

        }
    }
}
