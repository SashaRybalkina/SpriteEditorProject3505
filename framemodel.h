#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QObject>
#include "frame.h"
#include <QStackedWidget>
#include "drawingtool.h"

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

    /**
     * @brief toolChanged gets a new tool when the list changes tools
     * @param current
     * @param previous
     */
    void toolChanged(int currentRow);
    /**
     * @brief colorChanged updates drawing color when a slider is changed.
     * @param newColor
     */
    void colorChanged(QColor newColor);



    QImage getImageAt(int index);

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
    /**
     * @brief sizeChanged gets new size of frames. Warns user drawings will be reset and then changes frame size.
     */
    void sizeChanged(QString size);
    /**
     * @brief backgroundColorChanged gets new backgorund color and sets it
     * @param color
     */
    void backgroundColorChanged(QString color);
    void saveFile();
    void openFile();

    void addPen();

signals:
    /**
     * @brief changeSizeComboBox sends signal to change size
     * @param size
     */
    void changeSizeComboBox(QString size);
    void setSize(QString size);

    /**
     * @brief changeColorSliders - Signal for setting the color sliders when tool changes
     * @param red - [0-255] red color component
     * @param green - [0-255] green color component
     * @param blue - [0-255] blue color component
     * @param alpha - [0-255] alpha color component
     */
    void changeColorSliders(int red, int green, int blue, int alpha);

private:
    QStackedWidget* frameStack;
    int size;
    QColor backgroundColor;
    QString fileName;

    /**
     * @brief Contains a list of all tools currently open
     */
    std::vector<DrawingTool> tools;
    /**
     * @brief currentToolIndex contains the index of the current tool
     */
    int currentToolIndex;
    /**
     * @brief updateFrameProperties updates the frames colorPen to match the current tool
     */
    void updateFrameProperties();
    /**
     * @brief updateSliders - updates the color sliders to have the same rgb values as the current tool
     */
    void updateSliders();
    /**
     * @brief getBackgroundColorOfCurrentFrame - the eraser tool is constatntly locked on the background color.
     * This helper method gets the background color of the current frame.
     * @return
     */
    QColor getBackgroundColorOfCurrentFrame();
};

#endif // FRAMEMODEL_H
