#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>

#include "contouranalysis.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    contourAnalysis.reset(new ContourAnalysis);

    connect(ui->limitAreasCheckBox, &QCheckBox::clicked, [this]
    {
        const bool isChecked = ui->limitAreasCheckBox->isChecked();

        ui->minLabel->setEnabled(isChecked);
        ui->minSpinBox->setEnabled(isChecked);
        ui->maxLabel->setEnabled(isChecked);
        ui->maxSpinBox->setEnabled(isChecked);
    });

    connect(ui->openFileButton, &QPushButton::clicked, [this]
    {
        const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/oleg/Desktop/testImages", tr("Image Files (*.png *.jpg *.bmp)"));
        QPixmap pixmap(fileName);

        ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));

        contourAnalysis->setFileName(fileName);
        contourAnalysis->setCellsFoundLabel(ui->cellsFoundLabel);
    });

    connect(ui->analyzeButton, &QPushButton::clicked, [this]
    {
        contourAnalysis->run(static_cast<double>(ui->minSpinBox->value()), static_cast<double>(ui->maxSpinBox->value()), ui->limitAreasCheckBox->isChecked());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
