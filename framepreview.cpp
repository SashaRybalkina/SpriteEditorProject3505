#include "framemodel.h"
#include "framepreview.h"
#include "ui_framepreview.h"
#include <QPixmap>

FramePreview::FramePreview(QStackedWidget* frameStack, FrameModel* frameModel, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FramePreview),
    frameModel(frameModel),
    frameStack(frameStack),
    currentFrameIndex(0)
{
    ui->setupUi(this);

    playPauseButton = ui->playPause;
    fpsSlider = ui->fpsSlider;
    fpsBox = ui->fpsBox;
    actualSizeBox = ui->actualSize;

    fpsSlider->setMinimum(1);
    fpsSlider->setMaximum(60);
    fpsSlider->setValue(currentFPS);
    fpsBox->setMinimum(1);
    fpsBox->setMaximum(60);
    fpsBox->setValue(currentFPS);

    connect(ui->playPause, &QPushButton::clicked, this, &FramePreview::togglePlayPause);
    connect(fpsSlider, &QSlider::valueChanged, fpsBox, &QSpinBox::setValue);
    connect(fpsBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &FramePreview::changeFPS);
    connect(actualSizeBox, &QCheckBox::stateChanged, this, &FramePreview::toggleActualSize);

    connect(&timer, &QTimer::timeout, this, &FramePreview::updateAnimation);
    timer.setInterval(1000 / currentFPS);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    updateCurrentFrame();
}

FramePreview::~FramePreview()
{
    delete ui;
    if (timer.isActive()) {
        timer.stop();
    }
}

void FramePreview::populateFrameStackModel(QStackedWidget* frameStack, FrameModel* frameModel){
    this -> frameStack = frameStack;
    this -> frameModel = frameModel;
}

void FramePreview::togglePlayPause() {
    isPlaying = !isPlaying;

    if (isPlaying) {
        playPauseButton->setText("Pause");
        if (!timer.isActive()) {
            timer.start(1000 / currentFPS);
            qDebug() << "played";
        }
    } else {
        playPauseButton->setText("Play");
        timer.stop();
        qDebug() << "paused";
    }
}

void FramePreview::changeFPS(int fps)
{
    currentFPS = fps;
    timer.setInterval(1000 / currentFPS);
    fpsBox->setValue(fps);
    qDebug() << "fps changed to" << fps;
}

void FramePreview::toggleActualSize()
{
    atActualSize = actualSizeBox->isChecked();
    updateCurrentFrame();
    qDebug() << "actualsize clicked";
}

void FramePreview::updateAnimation()
{
    qDebug() << "updateAnimation called";
    qDebug() << "currentFrameIndex: " << currentFrameIndex;

    if (frameStack) {
        qDebug() << "frameStack count: " << frameStack->count();
        currentFrameIndex = (currentFrameIndex + 1) % frameStack->count();
        updateCurrentFrame();
        qDebug() << "animation updated";

    } else {
        qDebug() << "framestack null";
    }
}

void FramePreview::updateCurrentFrame()
{
    QImage frame = frameModel->getImageAt(currentFrameIndex);

    if (!frame.isNull()) {
        qDebug() << "frame not null";

        QPixmap framePixmap;

        if (atActualSize) {
            qDebug() << "actual size true";
            framePixmap = QPixmap::fromImage(frame);
        }else {
            qDebug() << "actual size false";
            framePixmap = QPixmap::fromImage(frame.scaled(
                ui->graphicsView->width(),
                ui->graphicsView->height(),
                Qt::KeepAspectRatio
                ));
        }
        scene->clear();
        scene->addPixmap(framePixmap);
    }
//    qDebug() << "frame null";
    //qDebug() << "frame updated";
}

