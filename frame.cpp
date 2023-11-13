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

Frame::Frame(int size)
    : QWidget(nullptr)
{
    qDebug("Frame created");

    setAttribute(Qt::WA_StaticContents);
    this->image_size = size;
    this->createImage();
}

void Frame::createImage() {
    image = QImage(image_size, image_size, QImage::Format_RGB32);
    image.fill(myPenColor);
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

void Frame::saveFile()
{
    if (fileName.isEmpty())
    {
        QStringList selectedFiles = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("JSON Files (*.ssp)"));
        fileName = selectedFiles.at(0);
    }

    QJsonObject content;
    content.insert("Image Size", image_size);
    QString str;
    int index = 1;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QJsonObject pixel;
            QColor currentColor(image.pixel(x, y));
            pixel.insert("a", currentColor.alpha());
            pixel.insert("b", currentColor.blue());
            pixel.insert("g", currentColor.green());
            pixel.insert("r", currentColor.red());
            pixel.insert("y", y);
            pixel.insert("x", x);
            content.insert("Pixel " + str.setNum(index), pixel);
            index++;
        }
    }
    QJsonDocument document(content);
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        file.write(document.toJson());
    }
    else
    {
        std::cout << "file open failed" << std::endl;
    }
    file.close();
}

void Frame::openFile()
{
    QStringList selectedFiles = QFileDialog::getOpenFileNames(this, tr("Open File"), "/path/to/file/", tr("JSON Files (*.ssp)"));
    QFile file(selectedFiles.at(0));
    QString str;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray valuesArray = file.readAll();
        file.close();
        QJsonDocument valuesDocument(QJsonDocument::fromJson(valuesArray));
        QJsonObject json = valuesDocument.object();
        foreach(const QString& jsonObject, json.keys())
        {
            if (jsonObject == "Image Size")
            {
                emit setSize(str.setNum(json.value(jsonObject).toInt()));
            }
            else
            {
                QStringList pixelValues;
                QJsonObject pixelValue = json.value(jsonObject).toObject();
                foreach(const QString& pixelValueKey, pixelValue.keys())
                {
                    pixelValues.push_back(str.setNum(pixelValue.value(pixelValueKey).toInt()));
                }
                int x = pixelValues[4].toInt();
                int y = pixelValues[5].toInt();
                int red = pixelValues[3].toInt();
                int green = pixelValues[2].toInt();
                int blue = pixelValues[1].toInt();
                int alpha = pixelValues[0].toInt();
                QRgba64 color = qRgba64(red, green, blue, alpha);
                image.setPixel(x, y, color);
            }
        }
    }
}
