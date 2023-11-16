#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QObject>
#include "frame.h"
#include <QStackedWidget>
#include "drawingtool.h"

/**
 * @brief The FrameModel class - Manages frames in the Sprite Editor and handles user interactions
 */
class FrameModel : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief FrameModel - Holds frames in QStackWidget and manipulates this strucutre accoridng to instructions from UI interactions
     * @param parent - Models parent
     */
    explicit FrameModel(QObject *parent = nullptr);

    /**
     * @brief attachStackWidget - Gets the stack from the UI
     * @param frameStackWidget - Created in Designer
     */
    void attachStackWidget(QStackedWidget *frameStackWidget);

    /**
     * @brief add_image - Creates new frame and pushes to the stack. Used upon startup, and by 'add' slots
     */
    void add_image();

    /**
     * @brief toolChanged - Gets a new tool when the list changes tools
     * @param currentRow - The current tool
     */
    void toolChanged(int currentRow);

    /**
     * @brief colorChanged - Updates drawing color when a slider is changed.
     * @param newColor - Color to change to
     */
    void colorChanged(QColor newColor);

    /**
     * @brief getImageAt - Gets image at index
     * @param index - Index to get from
     * @return The image at given index
     */
    QImage getImageAt(int index);

    /**
     * @brief getTotalFrames - Getter for total number of frames
     * @return Total number of frames
     */
    int getTotalFrames() const;

    /**
     * @brief getCurrentFrame - getter for current frame index
     * @return Index of current frame
     */
    int getCurrentFrame() const;

public slots:
    /**
     * @brief addFrame - Calls add_image to add new Sprite frame
     */
    void addFrame();

    /**
     * @brief deleteFrame - Removes current frame and sets current frame to next frame. If there is no next frame (dleted frame was last frame)
     * shows prior frame
     */
    void deleteFrame();

    /**
     * @brief nextFrame - Move to next frame (cyclic)
     */
    void nextFrame();

    /**
     * @brief priorFrame - Move to prior frame cyclic
     */
    void priorFrame();

    /**
     * @brief sizeChanged - Gets new size of frames. Warns user drawings will be reset and then changes frame size.
     * @param size - New size of frame
     */
    void sizeChanged(QString size);

    /**
     * @brief backgroundColorChanged - Gets new background color and sets it
     * @param color - The new color
     */
    void backgroundColorChanged(QString color);

    /**
     * @brief saveFile - Saves the file to json
     */
    void saveFile();

    /**
     * @brief openFile - Opens a json file
     */
    void openFile();

    /**
     * @brief addPen - Adds a custom pen
     */
    void addPen();

    /**
     * @brief brushSizeChanged - Changes brush size
     * @param newSize - Size to change to
     */
    void brushSizeChanged(int newSize);

signals:
    /**
     * @brief changeSizeComboBox - Sends signal to change size
     * @param size - The new size
     */
    void changeSizeComboBox(QString size);

    /**
     * @brief setSize - Setter for new size
     * @param size - The new size
     */
    void setSize(QString size);

    /**
     * @brief changeColorSliders - Signal for setting the color sliders when tool changes
     * @param red - [0-255] red color component
     * @param green - [0-255] green color component
     * @param blue - [0-255] blue color component
     * @param alpha - [0-255] alpha color component
     */
    void changeColorSliders(int red, int green, int blue, int alpha);

    /**
     * @brief updateBrushSize - Changes brush size
     * @param value - The new size
     */
    void updateBrushSize(int value);

private:
    QStackedWidget *frameStack;
    int size;
    QColor backgroundColor;
    QString fileName;
    std::vector<DrawingTool> tools;
    int currentToolIndex;

    /**
     * @brief updateFrameProperties updates the frames colorPen to match the current tool
     */
    void updateFrameProperties();

    /**
     * @brief updateSliders - Updates the color sliders to have the same rgb values as the current tool
     */
    void updateSliders();

    /**
     * @brief getBackgroundColorOfCurrentFrame - the eraser tool is constatntly locked on the background color.
     * This helper method gets the background color of the current frame.
     * @return The background color
     */
    QColor getBackgroundColorOfCurrentFrame();
};
#endif // FRAMEMODEL_H
