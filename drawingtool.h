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

private:
    QColor color_;

};

#endif // DRAWINGTOOL_H
