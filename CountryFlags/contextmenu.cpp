/*
   Copyright (C) Oleg Ziakun
*/

#include "contextmenu.h"
#include "ui_contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent) :
    QDialog(parent, Qt::Popup),
    ui(new Ui::ContextMenu)
{
    ui->setupUi(this);
    connect(ui->menuWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotItemClicked(QListWidgetItem*)));
}

ContextMenu::~ContextMenu()
{
    delete ui;
}

/* adds item to context menu */

void ContextMenu::addItem(QIcon &icon, const QString &text, const QString &whatsThis)
{
    QListWidgetItem *item = new QListWidgetItem(icon, text);

    item->setWhatsThis(whatsThis);
    ui->menuWidget->addItem(item);
}

void ContextMenu::slotItemClicked(QListWidgetItem *item)
{
    hide();
    emit currentCountryCode(item->whatsThis());
}

void ContextMenu::clear()
{
    ui->menuWidget->clear();
}
