/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: New ListName screen */

Rectangle {
    id: newListNameRectangle

    width: mainScreenWidth
    height: mainScreenHeight

    property string createButtonText: "Create this list"
    property string cancelButtonText: "Cancel"

    // check editor and clear it
    function switchToMainScreenWithCheck()
    {
        if(newListNameEditor.text != "")
            switchToMainScreen();

        newListNameEditor.text = ""
    }

    Header {
        id: header

        homeText: mainLinkTitle;
        onHeaderHomeTextClick: switchToMainScreen()
    }

    Button {
        id: createButton

        x: 43
        y: 174
        width: 113
        height: 24

        text: createButtonText

        onButtonClick: {
            tdlObject.addItem(newListNameEditor.text)
            switchToMainScreenWithCheck()
        }
    }

    Button {
        id: cancelButton

        x: 192
        y: 174
        width: 113
        height: 24

        text: cancelButtonText

        onButtonClick: switchToMainScreen()
    }

    Rectangle {
        width: newListNameEditor.width
        height: newListNameEditor.height
        x: newListNameEditor.x
        y: newListNameEditor.y

        border.width: 1
    }

    TextEdit {
        id: newListNameEditor

        x: 40
        y: 127
        width: 518
        height: 26

        anchors.left: parent.left
        anchors.leftMargin: 43
        anchors.top: parent.top
        anchors.topMargin: 128

        font.pixelSize: 18
        cursorVisible: true
    }

    Text {
        id: text1

        x: 203
        y: 103
        width: 233
        height: 14

        text: "(Ex: Things I need to do today)"

        font.pixelSize: 10
    }

    Text {
        id: text2

        x: 41
        y: 99

        text: "Name your new list"

        font.bold: true
        font.pixelSize: 16
    }

    Text {
        id: text3

        x: 168
        y: 179

        text: "or"

        font.pixelSize: 12
    }

    onVisibleChanged: {
        newListNameEditor.focus = true;
    }
}
