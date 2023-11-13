#ifndef FRAMEPREVIEW_H
#define FRAMEPREVIEW_H

#include "framemodel.h"
#include <QWidget>
#include <QTimer>
#include <QStackedWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>

namespace Ui {
class FramePreview;
}

class FramePreview : public QWidget
{
    Q_OBJECT

public:
    explicit FramePreview(QStackedWidget* frameStack, FrameModel* frameModel, QWidget *parent = nullptr);
    ~FramePreview();

    void populateFrameStackModel(QStackedWidget* frameStack, FrameModel* frameModel);

public slots:
    void togglePlayPause();
    void changeFPS(int fps);
    void toggleActualSize();

private:
    Ui::FramePreview *ui;
    FrameModel* frameModel;
    QTimer timer;
    QStackedWidget* frameStack;
    QGraphicsScene* scene;

    int currentFrameIndex;
    int currentFPS = 12;
    bool isPlaying = false;
    bool atActualSize = false;

    QPushButton* playPauseButton;
    QSlider* fpsSlider;
    QSpinBox* fpsBox;
    QCheckBox* actualSizeBox;

    void updateAnimation();
    void updateCurrentFrame();
};

#endif // FRAMEPREVIEW_H
