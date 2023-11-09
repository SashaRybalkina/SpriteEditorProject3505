#include "framemodel.h"
#include "frame.h"

FrameModel::FrameModel(QObject *parent) : QObject(parent) {
}

void FrameModel::attachStackWidget(QStackedWidget* frameStackWidget) {
    this->frameStack = frameStackWidget;
    qDebug() << frameStack->count();
    this->add_image();
}

void FrameModel::add_image() {
    Frame* frame = new Frame();
    frameStack->addWidget(frame);
    qDebug() << frameStack->count();
}

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
