#include "renderarea.h"

#include <QPainter>
#include <QMouseEvent>
#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QPixmap>
#include <assert.h>

struct RenderArea::RenderAreaPrivate
{
    void clear()
    {
        const QPointF outerPoint = QPointF(-10, -10);

        pointTimer.stop();
        connectedLine = QPair<QPointF, QPointF>(outerPoint, outerPoint);
        userPoint = outerPoint;
        points.clear();
    }

    QSize area;
    QVector<QPointF> points;
    QPointF userPoint;
    QPair<QPointF, QPointF> connectedLine;
    std::unique_ptr <DataConnector<float>> dataConnector;
    QTimer pointTimer;
    QPixmap pixmap;
};

RenderArea::RenderArea(const QSize& area, QWidget *parent)
    : QWidget(parent)
    , d(std::make_unique<RenderAreaPrivate>())
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    d->area = area;
    d->dataConnector = std::make_unique<DataConnector<float>>(*this);
    d->pixmap.load(":/images/map.png");
    d->clear();

    connect(&d->pointTimer, &QTimer::timeout, [this] { update(); });
}

RenderArea::~RenderArea() = default;

QSize RenderArea::sizeHint() const
{
    return d->area;
}

void RenderArea::sendRequest(const int maxResults)
{
    d->clear();
    d->dataConnector->requestData(DataRequest::Restaurant, d->area.width(), d->area.height(), maxResults);
}

void RenderArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    const int pointWidth = 8;
    static int pulseCounter = 0;

    auto pulsePoint = [] { return (++pulseCounter > 4) ? (pulseCounter = 0) : pulseCounter; };

    auto setPen = [&painter] (const QBrush &brush, const qreal width = 8, const Qt::PenStyle penStyle = Qt::SolidLine)
    {
        painter.setPen(QPen(brush, width, penStyle, Qt::RoundCap, Qt::RoundJoin));
    };

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(0, 0, d->pixmap);

    if(d->points.isEmpty())
        return;

    setPen(Qt::blue);

    for(const auto& point: d->points)
        painter.drawPoint(point);

    setPen(Qt::darkGreen, pointWidth);
    painter.drawPoint(d->userPoint);

    setPen(Qt::blue, 1, Qt::DashLine);
    painter.drawLine(d->connectedLine.first, d->connectedLine.second);

    setPen(Qt::blue, pointWidth + pulsePoint());
    painter.drawPoint(d->connectedLine.second);

    QPointF textPoint = d->connectedLine.second;
    const float x = textPoint.x();

    textPoint.setX((x >= d->area.width()/2) ? (x - 140) : (x + pointWidth));

    DataHandler<float>* const dataHandler = d->dataConnector->getDataHandler();
    assert(dataHandler);

    setPen(Qt::black);
    painter.drawText(textPoint, QString("distance: ") + QString::number(dataHandler->getDistance()));
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(d->points.isEmpty())
        return;

    d->userPoint.setX(static_cast<float>(event->x()));
    d->userPoint.setY(static_cast<float>(event->y()));

    const auto& nearestPoint = d->dataConnector->findNearestPoint(d->userPoint.x(), d->userPoint.y());
    d->connectedLine = QPair<QPointF, QPointF>(d->userPoint, QPointF(nearestPoint.first, nearestPoint.second));

    d->pointTimer.start(150);
}

void RenderArea::pointDataComplete()
{
    DataHandler<float>* const dataHandler = d->dataConnector->getDataHandler();
    assert(dataHandler);

    const auto& pointVector = dataHandler->getPoints();

    for(const auto& point: pointVector)
        d->points.push_back(QPoint(point.x, point.y));
}

void RenderArea::errorOccurred(DataConnectorErrors e)
{
    Q_UNUSED(e);
    // handle errors here
}

void RenderArea::mapDataComplete()
{
    // currently the map showing from the beginning for simulation purposes, but in real immlementation show a map in this method after analyzed points and loaded map
    update();
}

