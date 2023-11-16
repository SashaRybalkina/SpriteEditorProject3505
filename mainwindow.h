#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FrameModel.h"
#include "framepreview.h"
#include "Sliders.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    /**
     * @brief showFramePreview
     */
    void showFramePreview();

    /**
     * @brief colorSlidersChanged - changes the model when the sliders change
     * @param value
     */
    void colorSlidersChanged(int);

    /**
     *  @brief Updates the color sliders from the model when the tool changes
     */
    void updateColorSliders(int red, int green, int blue, int alpha);

    /**
     * @brief addPenClicked - adds another pen tool to the tools list.
     */
    void addPenClicked();

    /**
     * @brief handleOpen - updates ui when a new document is opened.
     */
    void handleOpen();

private:
    Ui::MainWindow* ui;
    QStackedWidget* frameStack;
    FramePreview* framePreview;

    FrameModel& frameModel;
    Sliders* sliders;
    int currentFrame;
    int totalFrames;

    void styleSetup();
    void colorSetup();
    /**
     * @brief toolsSetup Helper method to segment out connect calls for tool functionality.
     * @param frameModel
     */
    void toolsSetup(FrameModel& frameModel);
    void updateFrameCount();

public:
    MainWindow(FrameModel& frameModel, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateBrushSpinBox(int value);

signals:
    /**
     * @brief colorChanged - signals the model that the color has changed.
     * @param color
     */
    void colorChanged(QColor color);
};

#endif // MAINWINDOW_H
