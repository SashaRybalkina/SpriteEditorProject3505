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

Frame::Frame(int size, QColor backgroundColor)
    : QWidget(nullptr)
{
    qDebug("Frame created");

    setAttribute(Qt::WA_StaticContents);
    this->image_size = size;
    this->backgroundColor = backgroundColor;
    this->createImage();
}

void Frame::createImage() {
    image = QImage(image_size, image_size, QImage::Format_RGB32);
    image.fill(backgroundColor);
    update();
    qDebug("Update Called");
    this->setPenColor(Qt::black);
}

void Frame::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void Frame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
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
    if (event->button() == Qt::LeftButton && filling) {
        filling = false;
    }
}

void Frame::paintEvent(QPaintEvent *event)
{
    qDebug("Frame painted");

    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image);
}

void Frame::fill(const QPoint &point) {
    // think 0, 0 top left
    int x = point.x();
    int y = point.y();
    QSize widget_size = size();
    int x_len = widget_size.rwidth();
    int y_len = widget_size.rheight(); // should be same as x
    double pixel_size = (double) x_len / image_size;
    int image_x = (int)(x / pixel_size);
    int image_y = (int)(y / pixel_size);

    image.setPixelColor(image_x, image_y, myPenColor);
    update(); //this->paint();
}

QColor Frame::getBackgroundColor()
{
    return backgroundColor;
}
