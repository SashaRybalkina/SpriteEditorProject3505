/*
 * Alan Mo u1022249
 * CS 3505
 * A8: Sprite Editor Implementation
 */

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

namespace Ui
{
    class FramePreview;
}

/**
 * @brief The FramePreview class - Displays a preview of animated frames in the Sprite Editor
 */
class FramePreview : public QWidget
{
    Q_OBJECT

private:
    Ui::FramePreview *ui;
    FrameModel *frameModel;
    QTimer timer;
    QStackedWidget *frameStack;
    QGraphicsScene *scene;

    int currentFrameIndex;
    int currentFPS = 12;
    bool isPlaying = false;
    bool atActualSize = false;

    QPushButton *playPauseButton;
    QSlider *fpsSlider;
    QSpinBox *fpsBox;
    QCheckBox *actualSizeBox;

    /**
     * @brief updateAnimation - Manipulate the list of frames
     */
    void updateAnimation();

    /**
     * @brief updateCurrentFrame - Manipulate the current frame
     */
    void updateCurrentFrame();

private slots:
    /**
     * @brief hideFramePreview - Hide the frame preview window
     */
    void hideFramePreview();

public:
    /**
     * @brief FramePreview - Constructor for the FramePreview class
     * @param parent - The parent widget
     */
    explicit FramePreview(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~FramePreview();

    /**
     * @brief populateFrameStackModel - Makes frameStack and frameModel usable in framePreview
     * @param frameStack - The stack of frames
     * @param frameModel - The class that handles frames
     */
    void populateFrameStackModel(QStackedWidget *frameStack, FrameModel *frameModel);

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
};
#endif // FRAMEPREVIEW_H
