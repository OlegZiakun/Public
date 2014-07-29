/*
   Copyright (C) Oleg Ziakun
*/

#include <QUrl>
#include "streetviewmanager.h"
#include "mainwindow.h"

StreetViewManager::StreetViewManager(Ui::MainWindow *mw, QObject *parent) :
    QObject(parent),
    mainWindow(mw),
    mainUrl("http://maps.googleapis.com/maps/api/streetview?size=600x600")
{
    init();
}

void StreetViewManager::init()
{
    streetViewHistory.reset(new StreetViewHistory(mainWindow));

    reset();

    streetViewHistory->load();

    if(!streetViewHistory->inUse())
        addDefault();

    setLocation();
    setConnections();
}

void StreetViewManager::setConnections()
{
    connect(mainWindow->viewButton, SIGNAL(clicked()), this, SLOT(viewButtonClicked()));
    connect(mainWindow->headingDial, SIGNAL(sliderReleased()), this, SLOT(slidersReleased()));
    connect(mainWindow->fovSlider, SIGNAL(sliderReleased()), this, SLOT(slidersReleased()));
    connect(mainWindow->pitchSlider, SIGNAL(sliderReleased()), this, SLOT(slidersReleased()));
    connect(mainWindow->locationEdit, SIGNAL(returnPressed()), mainWindow->viewButton, SIGNAL(clicked()));
    connect(streetViewHistory.data(), SIGNAL(historyItemClicked(const QString&)), this, SLOT(historyItemClicked(const QString&)));
    connect(mainWindow->defaultButton, SIGNAL(clicked()), this, SLOT(defaultButtonClicked()));
}

void StreetViewManager::addDefault()
{
    setExampleLocations();
    streetViewHistory->markItem(0);
}

void StreetViewManager::reset()
{
    heading = 0;
    fov = 90;
    pitch = 0;

    mainWindow->pitchSlider->setValue(heading);
    mainWindow->fovSlider->setValue(fov);
    mainWindow->headingDial->setValue(pitch);
}

void StreetViewManager::viewButtonClicked()
{
    reset();
    setLocation();

    streetViewHistory->add(mainWindow->locationEdit->text());
}

void StreetViewManager::slidersReleased()
{
    heading = mainWindow->headingDial->value();
    fov = mainWindow->fovSlider->value();
    pitch = mainWindow->pitchSlider->value();

    setLocation();
}

void StreetViewManager::setLocation()
{
    if(mainWindow->locationEdit->text().isEmpty())
        return;

    QUrl url;
    QString urlString = mainUrl;

    urlString += QString("&location=%1&fov=%2&heading=%3&pitch=%4&sensor=false").arg(mainWindow->locationEdit->text()).arg(fov).arg(heading).arg(pitch);
    url.setUrl(urlString);

    mainWindow->webView->load(url);

    mainWindow->headingValueLabel->setText(QString::number(heading));
    mainWindow->fovValueLabel->setText(QString::number(fov));
    mainWindow->pitchValueLabel->setText(QString::number(pitch));
}

void StreetViewManager::historyItemClicked(const QString &itemText)
{
    mainWindow->locationEdit->setText(itemText);

    reset();
    setLocation();
}

void StreetViewManager::defaultButtonClicked()
{
    streetViewHistory->reset(false);
    init();
}

void StreetViewManager::setExampleLocations()
{
    streetViewHistory->add("Ottawa, Rideau Street");
    streetViewHistory->add("Hong Kong, So Lang Kwai Fong");
    streetViewHistory->add("Dallas, Texas, West Village");
    streetViewHistory->add("Toronto, Yonge Street");
    streetViewHistory->add("Wellington, New Zealand, Cuba Street");
    streetViewHistory->add("Kiev, Khreshchatyk");
    streetViewHistory->add("Los Angeles, Beverly Hills");
    streetViewHistory->add("Portland, OR Maywood Park");
    streetViewHistory->add("London, Oxford Street");
    streetViewHistory->add("New York, Broadway");

    mainWindow->locationEdit->setText("New York, Broadway");
}
