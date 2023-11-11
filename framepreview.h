#ifndef FRAMEPREVIEW_H
#define FRAMEPREVIEW_H

#include <QWidget>
#include <QTimer>
#include "framemodel.h"

namespace Ui {
class FramePreview;
}

class FramePreview : public QWidget
{
    Q_OBJECT

public:
    explicit FramePreview(QWidget *parent = nullptr);
    ~FramePreview();

public slots:
    void startAnimation(FrameModel* frameModel);
    void stopAnimation();

private slots:
    void updatePreview();

private:
    Ui::FramePreview *ui;
    QTimer* animationTimer;
    FrameModel* frameModel;
    int currentFrameIndex;

signals:

};

#endif // FRAMEPREVIEW_H
