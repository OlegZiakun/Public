/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: Button component */

Rectangle {
    id: button
    width: 80;
    height: 35
    border.width: 1
    radius: 10
    border.color: "black"
    smooth: true

    property alias text: buttonText.text
    property color buttonColor: "lightblue"
    property color onHoverColor: "gold"
    property color borderColor: "white"

    signal buttonClick()
    onButtonClick: {}

    gradient: Gradient {
        GradientStop { position: 0.0; color: "lightgray" }
        GradientStop { position: 0.5; color: "gray" }
        GradientStop { position: 1.0; color: "lightgray" }
    }

    Text {
        id: buttonText
        anchors.centerIn: parent
        font.pointSize: 10
        color: "white"        
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: parent.border.color = onHoverColor
        onExited:  parent.border.color = borderColor
        onClicked: buttonClick()
    }
}
