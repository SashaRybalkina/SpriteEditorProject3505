#include "framemodel.h"
#include "framepreview.h"
#include "ui_framepreview.h"
#include <QPixmap>

FramePreview::FramePreview(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::FramePreview),
      currentFrameIndex(0)
{
    ui->setupUi(this);

    playPauseButton = ui->playPause;
    fpsSlider = ui->fpsSlider;
    fpsBox = ui->fpsBox;
    actualSizeBox = ui->actualSize;

    // sets min, max, and default of slider and spin box
    fpsSlider->setMinimum(1);
    fpsSlider->setMaximum(60);
    fpsSlider->setValue(currentFPS);
    fpsBox->setMinimum(1);
    fpsBox->setMaximum(60);
    fpsBox->setValue(currentFPS);

    // connects buttons for frame playback functionality
    connect(ui->playPause, &QPushButton::clicked, this, &FramePreview::togglePlayPause);
    connect(fpsSlider, &QSlider::valueChanged, fpsBox, &QSpinBox::setValue);
    connect(fpsBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &FramePreview::changeFPS);
    connect(actualSizeBox, &QCheckBox::stateChanged, this, &FramePreview::toggleActualSize);

    connect(ui->hideButton, &QPushButton::clicked, this, &FramePreview::hideFramePreview);

    // manages speed of animation
    connect(&timer, &QTimer::timeout, this, &FramePreview::updateAnimation);
    timer.setInterval(1000 / currentFPS);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

FramePreview::~FramePreview()
{
    delete ui;
    if (timer.isActive())
    {
        timer.stop();
    }
}

void FramePreview::populateFrameStackModel(QStackedWidget *frameStack, FrameModel *frameModel)
{
    this->frameStack = frameStack;
    this->frameModel = frameModel;
}

void FramePreview::togglePlayPause()
{
    this->isPlaying = !isPlaying;

    if (isPlaying)
    {
        playPauseButton->setText("Pause");
        if (!timer.isActive())
        {
            timer.start(1000 / currentFPS);
        }
    }
    else
    {
        playPauseButton->setText("Play");
        timer.stop();
    }
}

void FramePreview::changeFPS(int fps)
{
    this->currentFPS = fps;
    timer.setInterval(1000 / currentFPS);
    fpsBox->setValue(fps);
}

void FramePreview::toggleActualSize()
{
    this->atActualSize = actualSizeBox->isChecked();
    updateCurrentFrame();
}

void FramePreview::updateAnimation()
{
    this->currentFrameIndex = (currentFrameIndex + 1) % frameStack->count();
    updateCurrentFrame();
}

void FramePreview::updateCurrentFrame()
{
    QImage frame = frameModel->getImageAt(currentFrameIndex);

    if (!frame.isNull())
    {
        QPixmap framePixmap;

        if (atActualSize)
        {
            framePixmap = QPixmap::fromImage(frame);
        }
        else
        {
            framePixmap = QPixmap::fromImage(frame.scaled(
                ui->graphicsView->width(),
                ui->graphicsView->height(),
                Qt::KeepAspectRatio));
        }
        scene->clear();
        scene->addPixmap(framePixmap);
    }
}

void FramePreview::hideFramePreview()
{
    hide();
}
