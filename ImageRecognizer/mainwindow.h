#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ContourAnalysis;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScopedPointer<ContourAnalysis> contourAnalysis;
};

#endif // MAINWINDOW_H
