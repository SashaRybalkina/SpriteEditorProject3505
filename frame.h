#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include <QMouseEvent>
#include <QWidget>
#include "drawingtool.h"

class Frame : public QWidget
{
    Q_OBJECT
public:
    QImage image;
    /**
     * @brief Frame data structure for Widget that holds image as internal strucutre and paints it onto itself
     * @param parent widgets parent
     * @param size pixel dimension for underlying image
     */
    Frame(int size = 4, QColor backgroundColor = Qt::blue, DrawingTool* tool = nullptr);

    /**
     * @brief createImage creates a frame default filled in
     */
    void createImage();
    // bool saveImage(const QString &fileName, const char *fileFormat);

    // void setPenWidth(int newWidth);

    // bool isModified() const { return modified; }
//    QColor penColor() const { return myPenColor; }
    // int penWidth() const { return myPenWidth; }

    QImage getImage() const { return image; }

    QColor getBackgroundColor();

    void changeTool(DrawingTool* newTool);

public slots:

signals:

protected:
    /**
     * @brief mousePressEvent adjusts the undelrying image with new color at the location pressed and paints it
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;
    /**
     * @brief mouseMoveEvent adjusts the undelrying image with new color at the location moved over and paints it
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /**
     * @brief mouseReleaseEvent stops adjusting image and painting changes
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
    /**
     * @brief paintEvent triggger by update to scale image and display it on frame widget
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;

    void fill(const QPoint &point);

private:
    // void resizeImage(QImage *image, const QSize &newSize);
    // bool modified = false;
    bool filling = false;
    // int myPenWidth = 1;
    // QPoint lastPoint;
    int image_size;
    QColor backgroundColor;
    DrawingTool* tool;

    QPoint getPixelLocationFromMousePosition(const QPoint &Point);
};

#endif // FRAME_H
