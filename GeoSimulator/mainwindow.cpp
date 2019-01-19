#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderarea.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pointsSpinBox->setFocusPolicy(Qt::NoFocus);
    renderArea.reset(new RenderArea(QSize(800, 420), centralWidget()));

    connect(ui->getDataButton, &QPushButton::clicked, [this] { renderArea->sendRequest(ui->pointsSpinBox->value()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
