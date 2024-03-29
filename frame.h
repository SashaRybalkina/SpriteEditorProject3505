/*
 * Brendon Gorleik u1403766
 * CS 3505
 * A8: Sprite Editor Implementation
 */

#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include <QMouseEvent>
#include <QWidget>
#include "drawingtool.h"

/**
 * @brief The Frame class - Represents a frame for drawing in the Sprite Editor
 */
class Frame : public QWidget
{
    Q_OBJECT

private:
    bool filling = false;
    int imageSize;
    QColor backgroundColor;
    DrawingTool *tool;

    /**
     * @brief getPixelLocationFromMousePosition - Getter for pixel location based on mouse position
     * @param Point - Location of mouse
     * @return Location of pixel
     */
    QPoint getPixelLocationFromMousePosition(const QPoint &Point);

public:
    QImage image;
    /**
     * @brief Frame data structure for Widget that holds image as internal strucutre and paints it onto itself
     * @param size - Pixel dimension for underlying image
     * @param backgroundColor - Color of the background
     * @param tool - A tool object
     */
    Frame(int size = 4, QColor backgroundColor = Qt::blue, DrawingTool *tool = nullptr);

    /**
     * @brief createImage - Creates a frame default filled in
     */
    void createImage();

    /**
     * @brief getImage - Getter for image
     * @return The image
     */
    QImage getImage() const { return image; }

    /**
     * @brief getBackgroundColor - Getter for background color
     * @return The background color
     */
    QColor getBackgroundColor();

    /**
     * @brief changeTool - Chages the current tool
     * @param newTool - The new tool
     */
    void changeTool(DrawingTool *newTool);

protected:
    /**
     * @brief mousePressEvent - Adjusts the undelrying image with new color at the location pressed and paints it
     * @param event - The mouse event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief mouseMoveEvent - Adjusts the undelrying image with new color at the location moved over and paints it
     * @param event - The mouse event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief mouseReleaseEvent - Stops adjusting image and painting changes
     * @param event - The mouse event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * @brief paintEvent - Trigger by update to scale image and display it on frame widget
     * @param event - The paint event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief fill - Fills a point
     * @param point - Point to fill
     */
    void fill(const QPoint &point);
};
#endif // FRAME_H
