/*
 * Michael Ekstorm u1170312
 * CS 3505
 * A8: Sprite Editor Implementation
 */

#ifndef DRAWINGTOOL_H
#define DRAWINGTOOL_H

#include <QWidget>

/**
 * @brief The DrawingTool class - Superclass for storing tool information for drawing. By default behaves as a pen
 */
class DrawingTool
{
private:
    QColor brushColor;
    int brushSize;

public:
    /**
     * @brief DrawingTool - Default behavior sets color to black
     */
    DrawingTool();

    /**
     * @brief DrawingTool - Initializes colors
     * @param red - [0-255] red color component
     * @param green - [0-255] green color component
     * @param blue - [0-255] blue color component
     * @param alpha - [0-255] alpha color component
     */
    DrawingTool(int red, int green, int blue, int alpha);

    /**
     * @brief DrawingTool - Initializes colors
     * @param color - Color for the tool
     */
    DrawingTool(QColor color);

    /**
     * @brief getToolColor - Getter for tool color
     * @return Color of tool
     */
    QColor getToolColor();

    /**
     * @brief setToolColor - Setter for tool color
     * @param color - Color to set
     */
    void setToolColor(QColor color);

    /**
     * @brief getColor - Getter for current brush color
     * @return The current brush color
     */
    QColor getColor();

    /**
     * @brief setBrushSize - Setter for the brush size
     * @param size - Size of the brush to set
     */
    void setBrushSize(int size);

    /**
     * @brief getBrushSize - Getter for brush size
     * @return Size of brush
     */
    int getBrushSize();
};
#endif // DRAWINGTOOL_H
