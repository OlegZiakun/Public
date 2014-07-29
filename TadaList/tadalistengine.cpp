/*
   Copyright (C) Oleg Ziakun
*/

#include "tadalistengine.h"
#include <QDebug>

TadaListEngine::TadaListEngine(QDeclarativeView &view, QObject *parent) :
    QObject(parent), declarativeView(view)
{
}

TadaListEngine::~TadaListEngine()
{
}

/*
* loads main view which controls all the screens
*/

void TadaListEngine::loadView(const QString &viewResStr)
{
    declarativeView.setSource(QUrl::fromLocalFile(viewResStr));
    declarativeView.show();
}

/*
* get initial bullet size, whose size reflects the size of the list
*/

int TadaListEngine::getSpotDiameter(int index) const
{
    int size = 0;

    if(isItemIndexValid(index))
    {
        size = MIN_SPOT_SIZE + items[index].item.count();

        if(size > MAX_SPOT_SIZE)
            size = MAX_SPOT_SIZE;

        return size;
    }
}

/*
* get items count
*/

int TadaListEngine::getItemsCount(void) const
{
    return items.count();
}

/*
* get records count
*/

int TadaListEngine::getRecordsCount(int index) const
{
    int count = 0;

    if(isItemIndexValid(index))
        count = items[index].item.count();

    return count;
}

/*
* add new item
*/

void TadaListEngine::addItem(const QString &itemNameText)
{
    if(itemNameText.isEmpty())
        msg("Item name is required");
    else if(items.count() < MAX_ITEMS_COUNT)
    {
        TDLData itemToAdd;

        itemToAdd.name = itemNameText;
        items.push_back(itemToAdd);
    }
    else
        msg("Sorry, 0.000001 version. " + QString::number(MAX_ITEMS_COUNT) +" items allowed only. Maybe in the future versions :)");
}

/*
* displays message box
*/

void TadaListEngine::msg(const QString &msg)
{
    QMessageBox msgBox;

    msgBox.setText(msg);
    msgBox.exec();
}

/*
* add a new record
*/

void TadaListEngine::addRecord(int itemIndex, const QString &recordText)
{
    if(recordText.isEmpty())
        msg("A name is required");
    else if(isItemIndexValid(itemIndex))
    {
        if(items[itemIndex].item.count() > MAX_LIST_ITEMS_COUNT)
            msg("Items scrolling not implemented. So this is a maximum items allowed");
        else
        {
            TDLRecord recordToAdd;

            recordToAdd.checked = false;
            recordToAdd.name = recordText;
            recordToAdd.index = items[itemIndex].item.count();
            recordToAdd.pos = recordToAdd.index;

            items[itemIndex].item.push_back(recordToAdd);
        }
    }
}

/*
* delete record and add it into undo records array
*/

void TadaListEngine::deleteRecord(int itemIndex, int recordIndex)
{  
    if(isRecordIndexValid(itemIndex, recordIndex))
    {
        undoRecords.push_back(items[itemIndex].item[recordIndex]);
        items[itemIndex].item.erase(items[itemIndex].item.begin() + recordIndex);
    }
}

/*
* undo previously deleted records
*/

void TadaListEngine::undoDeletedRecord(int index)
{
    if(isItemIndexValid(index))
        if(!undoRecords.isEmpty())
            items[index].item.push_back(undoRecords.pop());
}

/*
* is undo records array empty or not
*/

bool TadaListEngine::isUndoListEmpty(void)
{
    return undoRecords.isEmpty();
}

/*
* signals to QML objects signal for the creation of items
*/

void TadaListEngine::createItems(void)
{
    for(int i = 0; i < items.count(); ++i)
        emit createItemsSignal(items[i].name, getSpotDiameter(i));
}

/*
* get item name
*/

QString TadaListEngine::getItemName(int index) const
{
    QString str;

    if(isItemIndexValid(index))
        str = items[index].name;

    return str;
}

/*
* check is item index valid
*/

bool TadaListEngine::isItemIndexValid(int index) const
{
    return (index >= 0 && index < items.count());
}

/*
* check is record index valid
*/

bool TadaListEngine::isRecordIndexValid(int itemIndex, int recordIndex) const
{
    bool isValid = false;

    if(isItemIndexValid(itemIndex))
        if(recordIndex >= 0 && recordIndex < items[itemIndex].item.count())
            isValid = true;

    return isValid;
}

/*
* get record name
*/

QString TadaListEngine::getRecordName(int itemIndex, int recordIndex) const
{
    QString str;

    if(isRecordIndexValid(itemIndex, recordIndex))
        str = items[itemIndex].item[recordIndex].name;

    return str;
}

/*
* get record state (checked or unchecked)
*/

bool TadaListEngine::getRecordState(int itemIndex, int recordIndex) const
{
    bool state = false;

    if(isRecordIndexValid(itemIndex, recordIndex))
        state = items[itemIndex].item[recordIndex].checked;

    return state;
}

/*
* set record state (checked or unchecked)
*/

void TadaListEngine::setRecordState(int itemIndex, int recordIndex, bool state)
{
    if(isRecordIndexValid(itemIndex, recordIndex))
    {
        items[itemIndex].item[recordIndex].checked = state;
        moveRecord(itemIndex, recordIndex, state);
    }
}

/*
* add item description
*/

bool TadaListEngine::addItemDescription(int index, const QString &description)
{
    bool descriptionState = false;

    if(index >= 0 && index < items.count())
    {
        if(!description.isEmpty())
            descriptionState = true;

        items[index].description = description;
    }

    return descriptionState;
}

/*
* get item description
*/

QString TadaListEngine::getItemDescription(int index) const
{
    QString description;

    if(index >= 0 && index < items.count())
        description = items[index].description;

    return description;
}

/*
* move record to a new place in list box
*/

void TadaListEngine::moveRecord(int itemIndex, int recordIndex, bool state)
{
    if(state)
        moveCheckedRecord(itemIndex, recordIndex);
    else
        moveUnCheckedRecord(itemIndex, recordIndex);
}

/*
* move checked record to a new place in list box
*/

void TadaListEngine::moveCheckedRecord(int itemIndex, int recordIndex)
{    
    showInfo();

    if(isRecordIndexValid(itemIndex, recordIndex))
    {
        int firstRecordIndex = getFirstCheckedRecordIndex(itemIndex, recordIndex + 1);

        if(firstRecordIndex == UNKNOWN_INDEX)
            firstRecordIndex = items[itemIndex].item.count();

        if((firstRecordIndex > (recordIndex + 1)))
        {
            int curIndex = items[itemIndex].item[recordIndex].index;

            items[itemIndex].item[recordIndex].index =  items[itemIndex].item[firstRecordIndex - 1].index;
            items[itemIndex].item[firstRecordIndex - 1].index = curIndex;

            items[itemIndex].item.move(recordIndex, firstRecordIndex - 1);
        }
    }
}

/*
* show info message
*/

void TadaListEngine::showInfo()
{
    static bool showThisMsg = true;

    if(showThisMsg)
    {
        msg("Note: all checked items moves to the bottom of the list");
        showThisMsg = false;
    }
}

/*
* move unchecked record to previous place in list box
*/

void TadaListEngine::moveUnCheckedRecord(int itemIndex, int recordIndex)
{
    if(isRecordIndexValid(itemIndex, recordIndex))
    {
        int  firstRecordIndex = getFirstCheckedRecordIndex(itemIndex, 0);

        if(firstRecordIndex < items[itemIndex].item[recordIndex].pos && firstRecordIndex != UNKNOWN_INDEX)
            items[itemIndex].item[recordIndex].pos = getNearestRecordIndex(itemIndex, recordIndex);

        int prevIndex = items[itemIndex].item[recordIndex].pos;

        items[itemIndex].item[recordIndex].index = prevIndex;
        items[itemIndex].item.move(recordIndex, prevIndex);
        items[itemIndex].item[prevIndex].pos = items[itemIndex].item[prevIndex].index;
    }
}

/*
* get right index to move unchecked record to previous place in list box
*/

int TadaListEngine::getNearestRecordIndex(int itemIndex, int recordIndex) const
{
    int nearestIndex = UNKNOWN_INDEX;

    int firstRecordIndex = getFirstCheckedRecordIndex(itemIndex, 0);

    if(isItemIndexValid(itemIndex))
    {
        for(int i = 0; i < items[itemIndex].item.count(); ++i)
        {
            if(isRecordIndexValid(itemIndex, i))
            {
                if(items[itemIndex].item[i].checked)
                {
                    if(isRecordIndexValid(itemIndex, recordIndex))
                    {
                        if(items[itemIndex].item[i].pos > items[itemIndex].item[recordIndex].pos)
                        {
                            nearestIndex = i;
                            break;
                        }
                    }
                }
            }
        }
    }

    return (nearestIndex == UNKNOWN_INDEX) ? nearestIndex = (firstRecordIndex - 1) : 0;
}

/*
* get first checked record index to move record to the right place in list box
*/

int TadaListEngine::getFirstCheckedRecordIndex(int itemIndex, int recordIndex) const
{
    int firstRecordIndex = UNKNOWN_INDEX;

    if(isRecordIndexValid(itemIndex, recordIndex))
    {
        for(int i = recordIndex; i < items[itemIndex].item.count(); ++i)
        {
            if(items[itemIndex].item[i].checked)
            {
                firstRecordIndex = i;
                break;
            }
        }
    }

    return firstRecordIndex;
}






