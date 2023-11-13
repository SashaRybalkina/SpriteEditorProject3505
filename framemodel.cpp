#include "framemodel.h"
#include "frame.h"
#include <QMessageBox>
#include <QString>

FrameModel::FrameModel(QObject *parent) : QObject(parent), size(4) {
}

void FrameModel::attachStackWidget(QStackedWidget* frameStackWidget) {
    this->frameStack = frameStackWidget;
    qDebug() << frameStack->count();
    this->add_image();
}

// method
void FrameModel::add_image() {
    Frame* frame = new Frame(this->size);
    frameStack->addWidget(frame);
    qDebug() << frameStack->count();
}

QImage FrameModel::getImageAt(int index) {
    if (index >= 0 && index < frameStack->count()) {
        return qobject_cast<Frame*>(frameStack->widget(index))->getImage();
    }
    return QImage();
}

// slot
void FrameModel::addFrame() {
    this->add_image();
}

void FrameModel::deleteFrame() {
    if(frameStack->count() > 1) {
        QWidget *currentWidget = frameStack->currentWidget();
        frameStack->removeWidget(currentWidget);
        // Delete the widget
        delete currentWidget;


        // Now, update the current index
        int currentIndex = frameStack->currentIndex();
        if (currentIndex == frameStack->count()) {  // last widget in the stack
            frameStack->setCurrentIndex(frameStack->count() - 1);  // Move to the new last widget
        } else {
            // The current index is automatically perserved. Means it is set to the next widget after the one that was removed.
            frameStack->setCurrentIndex(currentIndex);
        }
    }
}

void FrameModel::nextFrame() {
    int currentIndex = frameStack->currentIndex();
    int nextIndex = (currentIndex + 1) % frameStack->count();
    frameStack->setCurrentIndex(nextIndex);
}

void FrameModel::priorFrame() {
    int currentIndex = frameStack->currentIndex();
    int nextIndex = (currentIndex - 1) % frameStack->count();
    frameStack->setCurrentIndex(nextIndex);
}

void FrameModel::sizeChanged(QString size_) {
    //    // choose first and second reminder
    //    QString replyText("");
    //    if(this->size == size_.toInt()) {
    //        replyText = "Are you sure?";
    //    }
    //    else {
    //        replyText = "If you proceed progress will be delted and size will be adjusted. Would you like to proceed?";
    //    }
    // generate popup for reminder
    //    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Changing Frame Size Warning", replyText,
    //                                                              QMessageBox::Yes|QMessageBox::No);

    //    if (reply == QMessageBox::Yes) {
    this->size = size_.toInt();
    // create new empty frame of size
    this->addFrame();
    // remove all prior frames
    while (frameStack->count() > 1) {
        QWidget *widget = frameStack->widget(0); // Get the first widget
        frameStack->removeWidget(widget); // Remove the widget from the stack
        delete widget; // Delete the widget
    }
    //    }
    //    else {
    //        qDebug("ran2");
    //        // changeSizeComboBox(QString::number(this->size));
    //    }
}
