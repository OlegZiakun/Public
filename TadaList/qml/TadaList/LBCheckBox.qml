/*
   Copyright (C) Oleg Ziakun
*/

import QtQuick 1.1

/* Description: ListBox with checkboxes */

Rectangle {
    id: lbCheckBox

    color: "white"
    border.width: 1

    function getCurrentIndex() { return listView.currentIndex; }
    function setCurrentIndex(index) { return listView.currentIndex = index; }
    function incIndex() { listView.incrementCurrentIndex(); }
    function decIndex() { listView.decrementCurrentIndex(); }
    function delIndex(index) { listView.remove(index); }

    Component {
        id: delegate

        Item {
            id: wrapper

            width: parent.width;
            height: 14
            x: 1;

            Row {
                id: row

                Image {
                    id: checkBox

                    source: isChecked ? "images/Checked.png" : "images/Unchecked.png"

                    MouseArea
                    {
                        anchors.fill: parent;

                        onClicked: {
                            // save all the necessary values and update ListBox
                            contactModel.setProperty(index, "isChecked", !contactModel.get(index).isChecked);
                            setCurrentIndex(index)

                            tdlObject.setRecordState(currentItemIndex ,getCurrentIndex(), isChecked)
                            loadRecords(currentItemIndex)
                        }
                    }
                }

                Column {
                    Text { text: name }
                }
            }
        }
    }

    ListView {
        id: listView

        width: parent.width;
        height: parent.height

        model: contactModel
        delegate: delegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
}

