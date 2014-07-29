/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1
import "TDL.js" as TDL

/* Description: Main file. Entry point for the app */

Rectangle {
    id: main

    property string mainLinkTitle:  linkBeforeStr +"My Lists" + linkAfterStr;
    property string createNewText: linkBeforeStr + "Create a new list" +linkAfterStr;
    property string addThisItem: "Add this item";
    property string mainUCTitle: "MY TADA LISTS"
    property string linkBeforeStr: "<a href=\" \">"
    property string linkAfterStr: "</a>"
    property string authorTitle: "Written by: Oleg Ziakun"
    property int itemsInitialIndex: 0
    property int itemsOffset: 0
    property int mainScreenWidth: 800
    property int mainScreenHeight: 768
    property int currentItemIndex: -1
    property int margin: 10

    width: mainScreenWidth
    height: mainScreenHeight

    signal listNameSignal(int index)

    // add dynamically created items (pointers) into array
    function addToListNamesListNamesArray(component) { TDL.listNamesArray.push(component); }

    // delete dynamically created items (pointers)
    function deleteListNamesArray()
    {
        var count = TDL.listNamesArray.length;

        for(var i = 0; i < count ; ++i)
            TDL.listNamesArray.pop();
    }

    // clear ListBox
    function clearListNames()
    {
        contactModel.clear()
        deleteListNamesArray();
    }

    // loads the records in ListBox
    function loadRecords(itemIndex)
    {
        var count = tdlObject.getRecordsCount(itemIndex);

        clearListNames();

        for(var i = 0;i < count;++i)
            contactModel.append( { name: tdlObject.getRecordName(itemIndex, i), isChecked: tdlObject.getRecordState(itemIndex, i) } )
    }

    // switch to Main screen
    function switchToMainScreen()
    {
        mainScreen.visible = true;
        newListNameScreen.visible = false;
        listScreen.visible = false;
        itemsInitialIndex = 0;
        itemsOffset = 0;

        clearListNames();

        tdlObject.createItems()
    }

    // switch to NewListName screen
    function switchToNewListNameScreen()
    {
        mainScreen.visible = false;
        newListNameScreen.visible = true;
        listScreen.visible = false;
    }

    // switch to List screen
    function switchToListScreen()
    {
        mainScreen.visible = false;
        newListNameScreen.visible = false;
        listScreen.visible = true;
    }


    ListModel { id: contactModel }

    // screens
    Item {
        id: views

        MainScreen {
            id: mainScreen
            visible: true
        }

        NewListNameScreen {
            id: newListNameScreen
            visible: false
        }

        ListScreen {
            id: listScreen
            visible: false
        }
    }
}
