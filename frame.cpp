#include "frame.h"
#include <iostream>
#include <QFile>
#include <QImage>
#include <QPainter>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>

Frame::Frame(int size, QColor backgroundColor, DrawingTool *currentTool)
    : QWidget(nullptr)
{
    setAttribute(Qt::WA_StaticContents);
    this->tool = currentTool;
    this->image_size = size;
    this->backgroundColor = backgroundColor;
    this->createImage();
}

void Frame::createImage()
{
    image = QImage(image_size, image_size, QImage::Format_ARGB32);
    image.fill(backgroundColor);
    update();
}

void Frame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        fill(event->position().toPoint());
        filling = true;
    }
}

void Frame::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && filling)
        fill(event->position().toPoint());
}

void Frame::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && filling)
    {
        filling = false;
    }
}

void Frame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image);
}

void Frame::fill(const QPoint &point)
{
    // 0, 0 top left
    int radius = tool->getBrushSize() - 1;
    QPoint centerPosition = getPixelLocationFromMousePosition(point);
    for (int x = centerPosition.x() - radius; x <= centerPosition.x() + radius; x++)
    {
        for (int y = centerPosition.y() - radius; y <= centerPosition.y() + radius; y++)
        {
            image.setPixelColor(x, y, tool->getToolColor());
        }
    }

    update();
}

QColor Frame::getBackgroundColor()
{
    return backgroundColor;
}

void Frame::changeTool(DrawingTool *tool)
{
    this->tool = tool;
}

QPoint Frame::getPixelLocationFromMousePosition(const QPoint &point)
{
    // 0, 0 top left
    int x = point.x();
    int y = point.y();
    QSize widget_size = size();
    int x_len = widget_size.rwidth();
    int y_len = widget_size.rheight(); // Should be same as x
    double pixel_size = (double)x_len / image_size;
    int image_x = (int)(x / pixel_size);
    int image_y = (int)(y / pixel_size);
    return QPoint(image_x, image_y);
}
