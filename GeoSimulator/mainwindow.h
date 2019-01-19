#pragma once

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class MainWindow;
}

class RenderArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScopedPointer<RenderArea> renderArea;
};
