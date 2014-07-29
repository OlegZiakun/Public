/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: Main screen */

Rectangle {
    id: mainRectangle

    width: mainScreenWidth
    height: mainScreenHeight

    property string mainTitle: "My Lists"
    property int itemsMargin: 30
    property int itemsX: margin
    property int itemsY: 110
    property int upSeparatorY: header.y + header.height + header.height / 2
    property int downSeparatorY: mainRectangle.height - margin*2

    Header {
        id: header

        homeFontSize: 16;
        homeText: mainTitle;
        link1Text: createNewText;

        onHeaderLink1Click: switchToNewListNameScreen()
    }

    // connecting with C++ object (receiving signal)
    Connections {
        target: tdlObject
        onCreateItemsSignal: container.createItem(linkBeforeStr + data + linkAfterStr, spotDiameter)
    }

    Separator { y: upSeparatorY; title: mainUCTitle }
    Separator { y: downSeparatorY; title: authorTitle }

    Item {
        id: container

        // dynamically create items
        function createItem(text, spotDiameter)
        {
            var component = Qt.createComponent("ListName.qml");

            addToListNamesListNamesArray(component) ;

            if (component.status === Component.Ready)
            {
                var listName = component.createObject(container);

                itemsOffset += itemsMargin;

                listName.index = itemsInitialIndex;

                listName.x = itemsX;
                listName.y = itemsY + itemsOffset;

                listName.text = text;
                listName.spotDiameter = spotDiameter;

                ++itemsInitialIndex;
            }
        }
    }
}
