#include "framemodel.h"
#include "frame.h"
#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QImage>
#include <QPainter>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>

FrameModel::FrameModel(QObject *parent)
    : QObject(parent),
      size(4),
      backgroundColor(Qt::blue),
      tools(),
      currentToolIndex(0)
{
    tools.push_back(DrawingTool(QColor(backgroundColor))); // Add eraser
    addPen();
}

void FrameModel::attachStackWidget(QStackedWidget *frameStackWidget)
{
    this->frameStack = frameStackWidget;
    addImage();
}

void FrameModel::addImage()
{
    Frame *frame = new Frame(size, backgroundColor, &tools[currentToolIndex]);
    frameStack->addWidget(frame);
}

QImage FrameModel::getImageAt(int index)
{
    if (index >= 0 && index < frameStack->count())
    {
        return qobject_cast<Frame *>(frameStack->widget(index))->getImage();
    }
    return QImage();
}

void FrameModel::addFrame()
{
    addImage();
}

void FrameModel::deleteFrame()
{
    if (frameStack->count() > 1)
    {
        QWidget *currentWidget = frameStack->currentWidget();
        frameStack->removeWidget(currentWidget);
        delete currentWidget;

        int currentIndex = frameStack->currentIndex();
        if (currentIndex == frameStack->count())
        {                                                         // Last widget in the stack
            frameStack->setCurrentIndex(frameStack->count() - 1); // Move to the new last widget
        }
        else
        {
            // The current index is automatically perserved. Means it is set to the next widget after the one that was removed.
            frameStack->setCurrentIndex(currentIndex);
        }
    }
}

void FrameModel::nextFrame()
{
    int currentIndex = frameStack->currentIndex();
    int nextIndex = (currentIndex + 1) % frameStack->count();
    frameStack->setCurrentIndex(nextIndex);
    updateFrameProperties();
}

void FrameModel::priorFrame()
{
    int currentIndex = frameStack->currentIndex();
    int nextIndex = (currentIndex - 1) % frameStack->count();
    frameStack->setCurrentIndex(nextIndex);
    updateFrameProperties();
}

void FrameModel::sizeChanged(QString size)
{
    this->size = size.toInt();
    addFrame();
    while (frameStack->count() > 1)
    {
        QWidget *widget = frameStack->widget(0); // Get the first widget
        frameStack->removeWidget(widget);        // Remove the widget from the stack
        delete widget;                           // Delete the widget
    }
}

void FrameModel::backgroundColorChanged(QString color)
{
    this->backgroundColor = QColor(color);
}

void FrameModel::saveFile()
{
    // Save the file name
    if (fileName.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(new QWidget, tr("Open File"), "/path/to/file/", tr("JSON Files (*.ssp)"));
    }

    QJsonObject content;
    content.insert("Image Size", size);
    QString str;

    // Insert every frame into json content
    for (int f = 0; f < frameStack->count(); f++)
    {
        QJsonObject frame;
        int index = 1;
        // Insert every pixel into frame object
        for (int y = 0; y < dynamic_cast<Frame *>(frameStack->widget(f))->getImage().height(); y++)
        {
            for (int x = 0; x < dynamic_cast<Frame *>(frameStack->widget(f))->getImage().width(); x++)
            {
                QJsonObject pixel;
                QColor currentColor(dynamic_cast<Frame *>(frameStack->widget(f))->getImage().pixelColor(x, y));

                // Insert every pixel element into pixel object
                pixel.insert("a", currentColor.alpha());
                pixel.insert("b", currentColor.blue());
                pixel.insert("g", currentColor.green());
                pixel.insert("r", currentColor.red());
                pixel.insert("y", y);
                pixel.insert("x", x);
                frame.insert("Pixel " + str.setNum(index), pixel);
                index++;
            }
        }
        content.insert("Frame " + str.setNum(f + 1), frame);
    }

    // Create json document and write to it
    QJsonDocument document(content);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        file.write(document.toJson());
    }
    else
    {
        std::cout << "file open failed" << std::endl;
    }
    file.close();
}

void FrameModel::openFile()
{
    QStringList selectedFiles = QFileDialog::getOpenFileNames(new QWidget, tr("Open File"), "/path/to/file/", tr("JSON Files (*.ssp)"));
    if (selectedFiles.isEmpty())
    {
        return; // No file was selected, so return early
    }

    QFile file(selectedFiles.at(0));
    QString str;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray valuesArray = file.readAll();
        file.close();

        QJsonDocument valuesDocument(QJsonDocument::fromJson(valuesArray));
        QJsonObject json = valuesDocument.object();

        QString imageSizeKey("Image Size");
        emit setSize(str.setNum(json.value(imageSizeKey).toInt()));

        int biggestIndex = 0;
        foreach (const QString &jsonObject, json.keys())
        {
            if (jsonObject != "Image Size")
            {
                QString stringIndex = jsonObject.mid(6, 7);
                int index = stringIndex.toInt();
                // Add frames so index doesn't go out of bounds
                while (index > frameStack->count())
                {
                    addImage();
                }

                QJsonObject frame = json.value(jsonObject).toObject();
                foreach (const QString &pixelKey, frame.keys())
                {
                    QStringList pixelValues;
                    QJsonObject pixel = frame.value(pixelKey).toObject();
                    foreach (const QString &pixelValue, pixel.keys())
                    {
                        pixelValues.push_back(str.setNum(pixel.value(pixelValue).toInt()));
                    }
                    // Set pixel values
                    int x = pixelValues[4].toInt();
                    int y = pixelValues[5].toInt();
                    int red = pixelValues[3].toInt();
                    int green = pixelValues[2].toInt();
                    int blue = pixelValues[1].toInt();
                    int alpha = pixelValues[0].toInt();
                    QColor color = QColor(red, green, blue, alpha);
                    dynamic_cast<Frame *>(frameStack->widget(index - 1))->image.setPixelColor(x, y, color);
                }
                biggestIndex++;
            }
        }
        // Remove excessive frames
        while (biggestIndex < frameStack->count())
        {
            frameStack->removeWidget(frameStack->widget(frameStack->count() - 1));
        }
    }
}

void FrameModel::toolChanged(int currentRow)
{
    currentToolIndex = currentRow;
    updateFrameProperties();
    updateSliders();
}

void FrameModel::colorChanged(QColor newColor)
{
    if (currentToolIndex > 0) // Eraser
        tools[currentToolIndex].setToolColor(newColor);

    updateFrameProperties();
    updateSliders();
}

void FrameModel::updateFrameProperties()
{
    // Update the pen color
    Frame *currentFrame = qobject_cast<Frame *>(frameStack->widget(frameStack->currentIndex()));
    currentFrame->changeTool(&(tools[currentToolIndex]));
}

void FrameModel::updateSliders()
{
    int red, green, blue, alpha;
    QColor color = tools[currentToolIndex].getToolColor();
    red = color.red();
    green = color.green();
    blue = color.blue();
    alpha = color.alpha();

    emit changeColorSliders(red, green, blue, alpha);
    emit updateBrushSize(tools[currentToolIndex].getBrushSize());
}

QColor FrameModel::getBackgroundColorOfCurrentFrame()
{
    Frame *currentFrame = qobject_cast<Frame *>(frameStack->widget(frameStack->currentIndex()));
    return currentFrame->getBackgroundColor();
}

void FrameModel::addPen()
{
    tools.push_back(DrawingTool());
}

void FrameModel::brushSizeChanged(int newSize)
{
    tools[currentToolIndex].setBrushSize(newSize);
    updateFrameProperties();
}

int FrameModel::getTotalFrames() const
{
    return frameStack->count();
}

int FrameModel::getCurrentFrame() const
{
    return frameStack->currentIndex() + 1;
}
