#include "framepreview.h"
#include "ui_framepreview.h"

FramePreview::FramePreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramePreview)
{
    ui->setupUi(this);
}

FramePreview::~FramePreview()
{
    delete ui;
}
