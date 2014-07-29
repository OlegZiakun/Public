/*
   Copyright (C) Oleg Ziakun
*/

#include <QMessageBox>
#include <QUrl>
#include <QTableWidgetItem>
#include "streetviewhistory.h"

StreetViewHistory::StreetViewHistory(Ui::MainWindow *mw, QObject *parent) :
    QObject(parent),
    mainWindow(mw),
    idsCountValueString("Ids count"),
    idNumberString("Id number")
{
    init();
}

void StreetViewHistory::setConnections()
{
    connect(mainWindow->historyTableView, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(historyItemClicked(QTableWidgetItem*)));
    connect(mainWindow->removeButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));
    connect(mainWindow->removeAllButton, SIGNAL(clicked()), this, SLOT(removeAllButtonClicked()));
}

void StreetViewHistory::init()
{
    settings.reset(new QSettings("Oleg Ziakun", "Google Street View"));
    setConnections();
}

void StreetViewHistory::setTabView()
{
    QStringList labels;

    labels << tr("Addresses");

    mainWindow->historyTableView->setColumnCount(2);
    mainWindow->historyTableView->verticalHeader()->hide();
    mainWindow->historyTableView->hideColumn(1);
    mainWindow->historyTableView->setHorizontalHeaderLabels(labels);
    mainWindow->historyTableView->setRowCount(itemsCount);
}

void StreetViewHistory::setItems()
{
    QStringList addressesList = settings->allKeys();

    for(int i = addressesList.count() - 1, j = 0; i >= 0; --i)
    {
        if(addressesList[i].startsWith(idNumberString))
        {
            mainWindow->historyTableView->setItem(j, 0, new QTableWidgetItem(settings->value(addressesList[i]).toString()));
            mainWindow->historyTableView->setItem(j, 1, new QTableWidgetItem(addressesList[i]));

            ++j;
        }
    }
}

void StreetViewHistory::load()
{
    itemsCount = settings->value(idsCountValueString, QVariant(qlonglong(0))).toLongLong();

    setTabView();

    if(itemsCount == 0)
        return;

    mainWindow->removeButton->setEnabled(true);
    mainWindow->removeAllButton->setEnabled(true);

    setItems();
    markItem(0);

    mainWindow->locationEdit->setText(mainWindow->historyTableView->item(0, 0)->text());
}

void StreetViewHistory::markItem(int index)
{
    mainWindow->historyTableView->setFocus();
    mainWindow->historyTableView->selectRow(index);
}

void StreetViewHistory::add(const QString &address)
{
    if(address.isEmpty())
    {
        QMessageBox::critical(0, tr("Address"), tr("Address string is empty. Please enter an address."), QMessageBox::Ok);
        return;
    }

    if(mainWindow->historyTableView->rowCount() == 0)
    {
        mainWindow->removeButton->setEnabled(true);
        mainWindow->removeAllButton->setEnabled(true);
    }

    qlonglong count = settings->value(idsCountValueString, QVariant(qlonglong(0))).toLongLong();
    itemsCount = count;

    for(int i = 0; i < itemsCount; ++i)
    {
        if(mainWindow->historyTableView->item(i, 0)->text() == address)
        {
            markItem(i);
            return;
        }
    }

    mainWindow->historyTableView->insertRow(0);

    mainWindow->historyTableView->setItem(0, 0, new QTableWidgetItem(address));
    mainWindow->historyTableView->setItem(0, 1, new QTableWidgetItem(QString::number(count)));

    settings->setValue(idNumberString + QString::number(count), address);
    settings->setValue(idsCountValueString, ++count);
}

void StreetViewHistory::historyItemClicked(QTableWidgetItem *item)
{
    emit historyItemClicked(item->text());
}

void StreetViewHistory::removeButtonClicked()
{
    if(mainWindow->historyTableView->rowCount() > 0)
    {
        if(mainWindow->historyTableView->currentRow() == -1)
            markItem(0);

        settings->remove(mainWindow->historyTableView->item(mainWindow->historyTableView->currentRow(), 1)->text());
        mainWindow->historyTableView->removeRow(mainWindow->historyTableView->currentRow());

        if(mainWindow->historyTableView->rowCount() > 0)
        {
            markItem(mainWindow->historyTableView->currentRow());
            emit historyItemClicked(mainWindow->historyTableView->currentItem()->text());
        }
        else
            reset();
    }
}

void StreetViewHistory::reset(bool inUseFlag)
{
    clear();
    load();
    setUseFlag(inUseFlag);
}

void StreetViewHistory::removeAllButtonClicked()
{
    if(mainWindow->historyTableView->rowCount() > 0)
        if(QMessageBox::question(0, tr("Remove All"), tr("Are you sure?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            reset();
}

void StreetViewHistory::clear()
{
    mainWindow->historyTableView->clear();
    settings->clear();
    mainWindow->locationEdit->clear();

    mainWindow->historyTableView->setRowCount(0);
    mainWindow->webView->load(QUrl());

    mainWindow->removeButton->setEnabled(false);
    mainWindow->removeAllButton->setEnabled(false);
}

void StreetViewHistory::setUseFlag(bool inUseFlag)
{
    settings->setValue("In use", inUseFlag);
}

bool StreetViewHistory::inUse() const
{
    return settings->value("In use", false).toBool();
}

