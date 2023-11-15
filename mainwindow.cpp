#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sliders.h"
#include "FrameModel.h"
#include "ui_framepreview.h"
#include <QHBoxLayout>

MainWindow::MainWindow(FrameModel& frameModel, QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), frameModel(frameModel), currentFrame(0), totalFrames(0)
{
    ui->setupUi(this);
    Sliders* sliders = new Sliders(ui);

    frameModel.attachStackWidget(ui -> FrameStack);
    ui -> widget -> populateFrameStackModel(ui->FrameStack, &frameModel);
    //    ui -> widget -> hide();
    connect(ui -> showButton, &QPushButton::clicked, this, &MainWindow::showFramePreview);

    styleSetup();
    colorRangeSetup();

    connect(ui -> redSlider, &QSlider::valueChanged, sliders, &Sliders::setRedText);
    connect(ui -> greenSlider, &QSlider::valueChanged, sliders, &Sliders::setGreenText);
    connect(ui -> blueSlider, &QSlider::valueChanged, sliders, &Sliders::setBlueText);
    connect(ui -> opacitySlider, &QSlider::valueChanged, sliders, &Sliders::setOpacityText);

    connect(ui -> redInput, &QLineEdit::textEdited, sliders, &Sliders::setRedSlider);
    connect(ui -> greenInput, &QLineEdit::textEdited, sliders, &Sliders::setGreenSlider);
    connect(ui -> blueInput, &QLineEdit::textEdited, sliders, &Sliders::setBlueSlider);
    connect(ui -> opacityInput, &QLineEdit::textEdited, sliders, &Sliders::setOpacitySlider);

    // connects UI to model for adding Sprite Frames
    connect(ui -> AddButton, &QPushButton::clicked, &frameModel, &FrameModel::addFrame);
    // Connects UI to model for deleting Sprite Frames
    connect(ui -> DeleteButton, &QPushButton::clicked, &frameModel, &FrameModel::deleteFrame);
    // Connects UI to model for moving forward through Sprite Frames
    connect(ui -> forwardButton, &QPushButton::clicked, &frameModel, &FrameModel::nextFrame);
    // Connects UI to model for moving backward through Sprite Frames
    connect(ui -> backwardButton, &QPushButton::clicked, &frameModel, &FrameModel::priorFrame);


    connect(ui->AddButton, &QPushButton::clicked, this, &MainWindow::updateFrameCount);
    connect(ui->DeleteButton, &QPushButton::clicked, this, &MainWindow::updateFrameCount);
    connect(ui->forwardButton, &QPushButton::clicked, this, &MainWindow::updateFrameCount);
    connect(ui->backwardButton, &QPushButton::clicked, this, &MainWindow::updateFrameCount);

    // Connects UI to model for updating frame size
    connect(ui -> sizeComboBox, &QComboBox::currentTextChanged, &frameModel, &FrameModel::sizeChanged);
    // Connect model to UI for changing back frame size if user picks no during warning
    connect(&frameModel, &FrameModel::changeSizeComboBox, ui -> sizeComboBox, &QComboBox::setCurrentText);

    connect(ui -> actionSave, &QAction::triggered, &frameModel, &FrameModel::saveFile);
    connect(ui -> actionOpen, &QAction::triggered, &frameModel, &FrameModel::openFile);

    connect(&frameModel, &FrameModel::setSize, ui -> sizeComboBox, &QComboBox::setCurrentText);

    // Connects UI to model for updating background color for additonal frames
    connect(ui -> backgroundComboBox, &QComboBox::currentTextChanged, &frameModel, &FrameModel::backgroundColorChanged);

    connect(ui -> actionOpen, &QAction::triggered, this, &MainWindow::handleOpen);


    toolsSetup(frameModel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete framePreview;
}

void MainWindow::styleSetup()
{
    QString universalStyle1 = "QSlider::groove:horizontal {border: 2px solid ";
    QString universalStyle2 = "; background: white; height: 10px;} QSlider::sub-page:horizontal {border: 2px solid ";
    QString universalStyle3 = "; background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 1, stop: 0 #ffffff, stop: 1 ";
    QString universalStyle4 = ");} QSlider::handle:horizontal {";
    QString universalStyle5 = "; width: 12px; margin-top: -4.25px; margin-bottom: -4.25px; margin-left: -2.25px; margin-right: -2.25px;}";

    ui -> redSlider -> setStyleSheet(QString(universalStyle1 + "#AA0000" + universalStyle2 + "#AA0000" + universalStyle3 + "#FF0000" + universalStyle4 + "background: #FF0000; border: 2.5px solid #AA0000" + universalStyle5));
    ui -> greenSlider -> setStyleSheet(QString(universalStyle1 + "#00AA00" + universalStyle2 + "#00AA00" + universalStyle3 + "#00FF00" + universalStyle4 + "background: #00FF00; border: 2.5px solid #00AA00" + universalStyle5));
    ui -> blueSlider -> setStyleSheet(QString(universalStyle1 + "#0000AA" + universalStyle2 + "#0000AA" + universalStyle3 + "#0000FF" + universalStyle4 + "background: #0000FF; border: 2.5px solid #0000AA" + universalStyle5));
    ui -> opacitySlider -> setStyleSheet(QString(universalStyle1 + "#000000" + universalStyle2 + "#000000" + universalStyle3 + "#000000" + universalStyle4 + "background: #555555; border: 2.5px solid #000000" + universalStyle5));

    ui -> redInput-> setStyleSheet(QString("border: 2.5px solid #AA0000"));
    ui -> greenInput-> setStyleSheet(QString("border: 2.5px solid #00AA00"));
    ui -> blueInput-> setStyleSheet(QString("border: 2.5px solid #0000AA"));
    ui -> opacityInput-> setStyleSheet(QString("border: 2.5px solid #555555"));
}

void MainWindow::colorRangeSetup()
{
    ui -> redInput-> setValidator(new QIntValidator(this));
    ui -> greenInput-> setValidator(new QIntValidator(this));
    ui -> blueInput-> setValidator(new QIntValidator(this));
    ui -> opacityInput-> setValidator(new QIntValidator(this));

    ui -> redSlider -> setRange(0, 255);
    ui -> greenSlider -> setRange(0, 255);
    ui -> blueSlider -> setRange(0, 255);
    ui -> opacitySlider -> setRange(0, 255);
}

void MainWindow::showFramePreview()
{
    qDebug() << "show called";
    ui -> widget -> show();
}

void MainWindow::toolsSetup(FrameModel& frameModel)
{
    // Connect color sliders to tools for drawing
    connect(ui -> redSlider, &QSlider::valueChanged, this, &MainWindow::colorSlidersChanged);
    connect(ui -> greenSlider, &QSlider::valueChanged, this, &MainWindow::colorSlidersChanged);
    connect(ui -> blueSlider, &QSlider::valueChanged, this, &MainWindow::colorSlidersChanged);
    connect(ui -> opacitySlider, &QSlider::valueChanged, this, &MainWindow::colorSlidersChanged);
    connect(this, &MainWindow::colorChanged, &frameModel, &FrameModel::colorChanged);

    connect(&frameModel, &FrameModel::changeColorSliders, this, &MainWindow::changeColorSliders);

    // Coonnects UI to model for updating when the selected tool is changed
    connect(ui -> toolListWidget, &QListWidget::currentRowChanged, &frameModel, &FrameModel::toolChanged);
    connect(ui -> addPenButton, &QPushButton::clicked, this, &MainWindow::addPenClicked);
    connect(ui -> addPenButton, &QPushButton::clicked, &frameModel, &FrameModel::addPen);
    // Brush Size Connection
    connect(ui -> brushSizeSpinBox, &QSpinBox::valueChanged, &frameModel, &FrameModel::brushSizeChanged);
    connect(&frameModel, &FrameModel::updateBrushSize, this, &MainWindow::updateBrushSpinBox);
    addPenClicked();
}

void MainWindow::colorSlidersChanged(int)
{
    int red, green, blue, alpha;
    red = ui -> redSlider -> value();
    green = ui -> greenSlider -> value();
    blue = ui -> blueSlider -> value();
    alpha = ui -> opacitySlider -> value();

    emit colorChanged(QColor(red, green, blue, alpha));
}

void MainWindow::changeColorSliders(int red, int green, int blue, int alpha)
{
    ui -> redSlider -> setValue(red);
    ui -> greenSlider -> setValue(green);
    ui -> blueSlider -> setValue(blue);
    ui -> opacitySlider -> setValue(alpha);
}

void MainWindow::addPenClicked()
{
    QListWidgetItem* item = new QListWidgetItem("Custom Pen");
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui -> toolListWidget -> addItem(item);
    item->isSelected();
}

void MainWindow::updateFrameCount()
{
    totalFrames = frameModel.getTotalFrames();
    currentFrame = frameModel.getCurrentFrame();
    ui->frameCount->setText(QString::number(currentFrame) + "/" + QString::number(totalFrames));
}

void MainWindow::handleOpen(){
    updateFrameCount();

}

void MainWindow::updateBrushSpinBox(int value)
{
    ui -> brushSizeSpinBox -> setValue(value);
}
