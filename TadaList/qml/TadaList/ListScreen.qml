/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: List screen */

Rectangle {
    id: listScreenRectangle

    width: mainScreenWidth
    height: mainScreenHeight

    property int upSeparatorY: header.y + header.height + header.height / 2
    property int downSeparatorY: listScreenRectangle.height - margin * 2
    property bool isNotEmpty: false

    function setDescriptionVisibility(editorIsVisible, linkIsVisible)
    {
        addNewDescriptionLink.visible = linkIsVisible
        descriptionEditorFrame.visible = editorIsVisible
        descriptionEditor.visible = editorIsVisible
        descriptionEditor.focus = editorIsVisible
        saveDescriptionButton.visible = editorIsVisible

        if(editorIsVisible)
            descriptionEditor.text = "";
    }

    Header {
        id: header

        homeFontSize: 16;
        homeText: mainLinkTitle;
        link1Text: createNewText;

        onHeaderHomeTextClick: {
            switchToMainScreen()
            addThisItemEditor.text = ""
        }

        onHeaderLink1Click: {
            switchToNewListNameScreen()
            clearListNames()
        }
    }

    Separator { y: upSeparatorY;  title: tdlObject.getItemName(currentItemIndex) }
    Separator { y: downSeparatorY; title: authorTitle }

    LBCheckBox {
        id: lbCheckBox;

        x: margin * 2
        y: 134
        width: 712
        height: 570
    }

    Rectangle {
        width: addThisItemEditor.width
        height: addThisItemEditor.height
        x: addThisItemEditor.x
        y: addThisItemEditor.y

        border.width: 1
    }

    TextEdit {
        id: addThisItemEditor

        x: 270
        y: 715
        width: 310
        height: 20

        cursorVisible: true
        font.pixelSize: 15
    }

    Text {
        id: addNewDescriptionLink

        x: 678
        y: 105

        text: linkBeforeStr + "Add new description" + linkAfterStr
        font.pixelSize: 12

        onLinkActivated: setDescriptionVisibility(true, false)
    }

    Rectangle {
        id: descriptionEditorFrame

        width: descriptionEditor.width
        height: descriptionEditor.height
        x: descriptionEditor.x
        y: descriptionEditor.y

        border.width: 1
        visible: false
    }

    Text {
        id: descriptionText

        x: 350
        y: 17
        width: 428
        height: 54

        wrapMode: Text.WordWrap
        horizontalAlignment: TextEdit.AlignHCenter
        font.pixelSize: 12
    }

    TextEdit {
        id: descriptionEditor

        x: descriptionText.x
        y: descriptionText.y
        width: 380
        height: 26

        wrapMode: TextEdit.WordWrap
        horizontalAlignment: TextEdit.AlignHCenter
        cursorVisible: true
        visible: false
        font.pixelSize: 18
    }

    Button {
        id: addButton

        x: 620
        y: 715
        width: 152
        height: 24

        text: addThisItem

        onButtonClick: {
            if(addThisItemEditor.text != "")
                contactModel.append({name: addThisItemEditor.text, isChecked: false})

            tdlObject.addRecord(currentItemIndex, addThisItemEditor.text)
        }
    }

    Button {
        id: upButton

        x: 745
        y: 166
        width: 42
        height: 44

        text: "Up"

        onButtonClick: lbCheckBox.decIndex()
    }

    Button {
        id: downButton

        x: 745
        y: 219
        width: 42
        height: 44

        text: "Down"

        onButtonClick: lbCheckBox.incIndex();
    }

    Button {
        id: delButton

        x: 745
        y: 308
        width: 42
        height: 44

        text: "Del."

        onButtonClick: {
            undoButton.visible = true;

            var recordIndex = lbCheckBox.getCurrentIndex()

            contactModel.remove(recordIndex)
            tdlObject.deleteRecord(currentItemIndex, recordIndex)
        }
    }

    Button {
        id: undoButton

        x: 743
        y: 362
        width: 42
        height: 44

        text: "Undo"
        visible: false

        onButtonClick: {
            tdlObject.undoDeletedRecord(currentItemIndex)

            clearListNames()
            loadRecords(currentItemIndex)

            undoButton.visible = !tdlObject.isUndoListEmpty()
        }
    }

    Button {
        id: saveDescriptionButton

        x: 678
        y: 93
        width: 105
        height: 25

        text: "Save"
        visible: false

        onButtonClick: {
            isNotEmpty = tdlObject.addItemDescription(currentItemIndex,descriptionEditor.text)

            if(isNotEmpty)
                descriptionText.text = descriptionEditor.text

            setDescriptionVisibility(false, true)
        }
    }

    onVisibleChanged: {
        addThisItemEditor.focus = true
        descriptionText.text = tdlObject.getItemDescription(currentItemIndex)
        setDescriptionVisibility(false, true)
    }
}
