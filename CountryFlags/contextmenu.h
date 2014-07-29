/*
   Copyright (C) Oleg Ziakun
*/

#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QDialog>
#include <QListWidgetItem>

/* Content menu class */

namespace Ui {
class ContextMenu;
}

class ContextMenu : public QDialog
{
    Q_OBJECT
    
public:
    explicit ContextMenu(QWidget *parent = 0);
    ~ContextMenu();

public:
    void addItem(QIcon &icon, const QString &text, const QString &whatsThis);
    void clear();

signals:
    void currentCountryCode(const QString &code);

private slots:
        void slotItemClicked(QListWidgetItem *item);
    
private:
    Ui::ContextMenu *ui;
};

#endif // CONTEXTMENU_H
