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
