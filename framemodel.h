#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QObject>
#include "frame.h"
#include <QStackedWidget>

class FrameModel : public QObject
{
    Q_OBJECT
public:
    explicit FrameModel(QObject *parent = nullptr);
    void attachStackWidget(QStackedWidget* frameStackWidget);
    void add_image();

public slots:
    void addFrame();
    void deleteFrame();
    void nextFrame();
    void priorFrame();

signals:

private:
    QList<Frame*> images;
    QStackedWidget* frameStack;
};

#endif // FRAMEMODEL_H
