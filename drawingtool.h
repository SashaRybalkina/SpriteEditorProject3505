#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QWidget>

/**
 * @brief The DrawingTool class - Superclass for storing tool information for drawing. By default behaves as a pen
 */
class DrawingTool
{
public:
    /**
     * @brief DrawingTool - default bahvior sets color to black
     */
    DrawingTool();
    /**
     * @brief DrawingTool
     * @param red - [0-255] red color component
     * @param green - [0-255] green color component
     * @param blue - [0-255] blue color component
     * @param alpha - [0-255] alpha color component
     */
    DrawingTool(int red, int green, int blue, int alpha);

    /**
     * @brief DrawingTool
     * @param color
     */
    DrawingTool(QColor color);

    /**
     * @brief getToolColor
     * @return
     */
    QColor getToolColor();

    /**
     * @brief setToolColor
     * @param color
     */
    void setToolColor(QColor color);

    /**
     * @brief getColor - returns the current brush color
     * @return
     */
    QColor getColor();

    /**
     * @brief setBrushSize - sets the brush size
     * @param size
     */
    void setBrushSize(int size);

    /**
     * @brief getBrushSize - returns the current brush size
     * @return
     */
    int getBrushSize();

private:
    /**
     * @brief color_ - stores the current brush color
     */
    QColor color_;

    /**
     * @brief brushSize - stores the current brush size.
     */
    int brushSize;

};

#endif // DRAWINGTOOL_H
