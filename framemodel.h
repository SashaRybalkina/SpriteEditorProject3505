#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QObject>
#include "frame.h"
#include <QStackedWidget>

class FrameModel : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief FrameModel holds frames in QStackWidget and manipulates this strucutre accoridng to instructions from UI interactions
     * @param parent models parent
     */
    explicit FrameModel(QObject *parent = nullptr);
    /**
     * @brief attachStackWidget gets the stack from the UI
     * @param frameStackWidget created in Designer
     */
    void attachStackWidget(QStackedWidget* frameStackWidget);
    /**
     * @brief add_image creates new frame and pushes to the stack. Used upon startup, and by 'add' slots
     */
    void add_image();

public slots:
    /**
     * @brief addFrame calls add_image to add new Sprite frame
     */
    void addFrame();
    /**
     * @brief deleteFrame removes current frame and sets current frame to next frame. If there is no next frame (dleted frame was last frame)
     * shows prior frame
     */
    void deleteFrame();
    /**
     * @brief nextFrame move to next frame (cyclic)
     */
    void nextFrame();
    /**
     * @brief priorFrame move to prior frame cyclic
     */
    void priorFrame();

signals:

private:
    QList<Frame*> images;
    QStackedWidget* frameStack;
};

#endif // FRAMEMODEL_H
