#pragma once

#include "dataconnector.h"
#include <QWidget>
#include <memory>

class RenderArea : public QWidget, public DataConnectorObserver
{
public:
    explicit RenderArea(const QSize& area, QWidget *parent = 0);
    ~RenderArea();

public:
    void sendRequest(const int maxResults);

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void pointDataComplete() override;
    void errorOccurred(DataConnectorErrors e) override;
    void mapDataComplete() override;

private:
    struct RenderAreaPrivate;
    std::unique_ptr <RenderAreaPrivate> d;
};
