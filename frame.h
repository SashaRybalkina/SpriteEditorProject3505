#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include <QMouseEvent>
#include <QWidget>

class Frame : public QWidget
{
    Q_OBJECT
public:
    Frame(QWidget *parent = nullptr, int size = 10);
    void createImage();
    // bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    // void setPenWidth(int newWidth);

    // bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    // int penWidth() const { return myPenWidth; }

public slots:
    //void clearImage();
    //void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;

    void fill(const QPoint &point);
private:
    // void resizeImage(QImage *image, const QSize &newSize);

    // bool modified = false;
    bool filling = false;
    // int myPenWidth = 1;
    QColor myPenColor = Qt::blue;
    QImage image;
    // QPoint lastPoint;
    int image_size;
};

#endif // FRAME_H
