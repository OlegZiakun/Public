/*
   Copyright (C) Oleg Ziakun
*/

#ifndef TADALISTENGINE_H
#define TADALISTENGINE_H

#include <QObject>
#include <QtDeclarative>
#include <QStack>

#define MIN_SPOT_SIZE 4
#define MAX_SPOT_SIZE 20
#define MAX_ITEMS_COUNT 20
#define MAX_LIST_ITEMS_COUNT 40
#define UNKNOWN_INDEX - 1

/*
* class TadaListEngine
*/

class TadaListEngine : public QObject
{
    Q_OBJECT
public:
    explicit TadaListEngine(QDeclarativeView &view, QObject *parent = 0);
    ~TadaListEngine();

    /*
    * struct TDLRecord
    *
    * Item record
    */
    struct TDLRecord
    {
        int index;    // index
        int pos;      // position in ListBox (to insert in the previous place)
        QString name; // name of a record
        bool checked; // checked state
    };

    /*
    * struct TDLData
    *
    * Item
    */
    struct TDLData
    {
        QString name;          // name
        QString description;   // description of an item
        QList<TDLRecord> item; // list of dependent records
    };

public slots:
    void loadView(const QString &viewResStr);
    void createItems(void);
    int getSpotDiameter(int index) const;
    int getItemsCount(void) const;
    void undoDeletedRecord(int index);
    QString getItemName(int index) const;
    void addRecord(int itemIndex, const QString &recordText);
    QString getRecordName(int itemIndex, int recordIndex) const;
    bool getRecordState(int itemIndex, int recordIndex) const;
    int getRecordsCount(int index) const;
    QString getItemDescription(int index) const;
    void deleteRecord(int itemIndex, int recordIndex);
    bool addItemDescription(int index, const QString &description);
    void setRecordState(int itemIndex, int recordIndex, bool state);
    bool isUndoListEmpty(void);
    void addItem(const QString &itemName);

signals:  
    void createItemsSignal(const QString &data, int spotDiameter);  // signal for the creation of items

private:
    void msg(const QString& msg);
    int getFirstCheckedRecordIndex(int itemIndex, int recordIndex) const;
    int getNearestRecordIndex(int itemIndex, int recordIndex) const;
    bool isRecordIndexValid(int itemIndex, int recordIndex) const;
    bool isItemIndexValid(int index) const;
    void moveRecord(int itemIndex, int recordIndex, bool state);
    void moveCheckedRecord(int itemIndex, int recordIndex);
    void moveUnCheckedRecord(int itemIndex, int recordIndex);
    void showInfo();

private:
    QDeclarativeView &declarativeView; // for displaying a Qt Declarative user interface
    QList<TDLData> items;              // container for items
    QStack<TDLRecord> undoRecords;     // container for undo records
};

#endif // TADALISTENGINE_H
