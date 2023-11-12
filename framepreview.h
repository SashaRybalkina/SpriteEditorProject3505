#ifndef FRAMEPREVIEW_H
#define FRAMEPREVIEW_H

#include <QWidget>

namespace Ui {
class FramePreview;
}

class FramePreview : public QWidget
{
    Q_OBJECT

public:
    explicit FramePreview(QWidget *parent = nullptr);
    ~FramePreview();

private:
    Ui::FramePreview *ui;
};

#endif // FRAMEPREVIEW_H
