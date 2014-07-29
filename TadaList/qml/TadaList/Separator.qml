/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: Seperator */

Rectangle {   
    id: seperator

    property int margin: 10
    property alias title: title.text
    property alias fontSize: title.font.pointSize

    x: parent.x + margin

    height: 1
    width: parent.width - margin * 2

    color: "lightgray"

    Text {
        id: title

        x: parent.x + margin
        y: -margin * 2

        font.pointSize: 10
        color: parent.color
    }
}
