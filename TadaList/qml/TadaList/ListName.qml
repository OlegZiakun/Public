/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: Label with initial bullet (spot), whose size reflects the size of the list */

Rectangle {

    id: listName

    property int spotDiameter
    property int index

    property alias text: listNametext.text
    property int textXOffset: listName.x + 30
    property int spotY: height / 2 - spotDiameter / 2

    width: parent.width / 2
    height: listNametext.font.pixelSize + 4

    Rectangle {
        id: spot

        x: parent.x
        y: spotY
        width: spotDiameter
        height: spotDiameter

        border.width: 1

        color: "#000000"
        radius: spotDiameter / 2
    }

    Text {
        id: listNametext

        x: textXOffset

        font.pointSize: 12
        textFormat: Text.RichText

        onLinkActivated: {
            currentItemIndex = index

            loadRecords(currentItemIndex)
            switchToListScreen()
        }
    }

}
