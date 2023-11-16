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
    explicit FramePreview(QWidget *parent = nullptr);
    ~FramePreview();

    /**
     * @brief populateFrameStackModel - Makes frameStack and frameModel usable in framePreview
     * @param frameStack - The stack of frames
     * @param frameModel - The class that handles frames
     */
    void populateFrameStackModel(QStackedWidget* frameStack, FrameModel* frameModel);

private slots:
    /**
     * @brief hideFramePreview - Hide the frame preview window
     */
    void hideFramePreview();

public slots:
    /**
     * @brief togglePlayPause - Play and pause the animation
     */
    void togglePlayPause();

    /**
     * @brief changeFPS - Change frames per second of animation
     * @param fps - The fps
     */
    void changeFPS(int fps);

    /**
     * @brief toggleActualSize - Toggle between scaled size and actual size
     */
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

    /**
     * @brief updateAnimation - Manipulate the list of frames
     */
    void updateAnimation();

    /**
     * @brief updateCurrentFrame - Manipulate the current frame
     */
    void updateCurrentFrame();
};
#endif // FRAMEPREVIEW_H
