#ifndef FRAMEPREVIEW_H
#define FRAMEPREVIEW_H

#include <QWidget>
#include <QTimer>
#include <QStackedWidget>
#include <QGraphicsScene>
#include <QCheckBox>
#include <QSlider>
#include <QSpinBox>

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
    //void togglePlayPause();
    //void changeFPS(int fps);
    //void toggleActualSize();

private:
    Ui::FramePreview *ui;
    QTimer timer;
    QStackedWidget* frameStack;
    QGraphicsScene* scene;

    bool isPlaying = false;
    bool atActualSize = false;
    int currentFPS = 12;

    QSlider* fpsSlider;
    QSpinBox* fpsBox;
    QCheckBox* actualSizeCheckbox;
};

#endif // FRAMEPREVIEW_H
