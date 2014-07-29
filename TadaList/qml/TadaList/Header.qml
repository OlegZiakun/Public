/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: Header component */

Rectangle {
    id: header

    x: parent.x + 10
    y: parent.y + 4
    width: parent.width - 20
    height: 80
    radius: 10

    color: "transparent"
    opacity: 1.0

    //some animation
    PropertyAnimation {id: animateColor; target: header; properties: "color"; to: "lightgray"; duration: 1500}

    NumberAnimation {
        id: animateOpacity

        target: header

        properties: "opacity"
        from: 0.99
        to: 1.0

        loops: Animation.Infinite

        easing { type: Easing.OutBack; overshoot: 500 }
    }

    property alias homeText: headerHomeText.text
    property alias link1Text: headerLink1.text
    property alias homeFontSize: headerHomeText.font.pointSize

    function animate()
    {
        animateColor.start()
        animateOpacity.start()
    }

    signal headerHomeTextClick()
    signal headerLink1Click()

    onHeaderHomeTextClick:{}
    onHeaderLink1Click:{}

    //start animation
    Component.onCompleted : {
        animate()
    }

    //load logo image
    Image {
        id: headerLogo

        x: 16
        y: 12
        width: 55
        height: 56

        smooth: true
        fillMode: Image.PreserveAspectCrop
        source: "images/tada logo.gif"
    }

    Text {
        id: headerHomeText

        x: 99
        y: parent.height / 2 - font.pixelSize / 2

        font.pointSize: 12
        textFormat: Text.RichText

        onLinkActivated: headerHomeTextClick()
    }

    Text {
        id: headerLink1

        x: 187
        y: parent.height / 2 - font.pixelSize / 4

        font.pointSize: 10
        textFormat: Text.RichText

        onLinkActivated: headerLink1Click()
    }

}
