#include "framemodel.h"
#include "framepreview.h"
#include "ui_framepreview.h"
#include <QPixmap>

FramePreview::FramePreview(QStackedWidget* frameStack, FrameModel* frameModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramePreview),
    frameModel(frameModel),
    currentFrameIndex(0)
{
    ui->setupUi(this);

    playPauseButton = ui->playPause;
    fpsSlider = ui->fpsSlider;
    fpsBox = ui->fpsBox;
    actualSizeBox = ui->actualSize;

    connect(ui->playPause, &QPushButton::clicked, this, &FramePreview::togglePlayPause);
    connect(fpsSlider, &QSlider::valueChanged, this, &FramePreview::changeFPS);
    connect(fpsBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &FramePreview::changeFPS);
    connect(actualSizeBox, &QCheckBox::stateChanged, this, &FramePreview::toggleActualSize);

    connect(&timer, &QTimer::timeout, this, &FramePreview::updateAnimation);
    timer.setInterval(1000 / currentFPS);
    updateCurrentFrame();
}

FramePreview::~FramePreview()
{
    delete ui;

    if (timer.isActive()) {
        timer.stop();
    }
}

void FramePreview::togglePlayPause()
{
    isPlaying = !isPlaying;
    if (isPlaying) {
        playPauseButton->setText("Pause");
        timer.start();
    } else {
        playPauseButton->setText("Play");
        timer.stop();
    }
}

void FramePreview::changeFPS(int fps)
{
    currentFPS = fps;
    timer.setInterval(1000 / currentFPS);
    fpsBox->setValue(fps);
}

void FramePreview::toggleActualSize()
{
    atActualSize = actualSizeBox->isChecked();
    updateCurrentFrame();
}

void FramePreview::updateAnimation()
{
    currentFrameIndex = (currentFrameIndex + 1) % frameStack->count();
    updateCurrentFrame();
}

void FramePreview::updateCurrentFrame()
{
    QPixmap pixmap;
    if (atActualSize) {
        pixmap = QPixmap::fromImage(frameModel->getImageAt(currentFrameIndex));
    } else {
        pixmap = QPixmap::fromImage(frameModel->getImageAt(currentFrameIndex).scaled(
            ui->graphicsView->width(),
            ui->graphicsView->height(),
            Qt::KeepAspectRatio
            ));
    }
    scene->clear();
    scene->addPixmap(pixmap);
}
