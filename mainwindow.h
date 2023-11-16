#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FrameModel.h"
#include "framepreview.h"
#include "sliders.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class - The main screen that everything is on
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QStackedWidget *frameStack;
    FramePreview *framePreview;
    FrameModel &frameModel;
    Sliders *sliders;

    int currentFrame;
    int totalFrames;

    /**
     * @brief styleSetup - Initializes the style components and stylesheets in the MainWindow
     */
    void styleSetup();

    /**
     * @brief colorSetup - Initializes color components and connections in the MainWindow
     */
    void colorSetup();

    /**
     * @brief toolsSetup - Helper method to segment out connect calls for tool functionality
     * @param frameModel - An object with frames
     */
    void toolsSetup(FrameModel &frameModel);

    /**
     * @brief updateFrameCount - Changes the frameCount label
     */
    void updateFrameCount();

private slots:
    /**
     * @brief showFramePreview - Shows the frame preview widget
     */
    void showFramePreview();

    /**
     * @brief colorSlidersChanged - Changes the model when the sliders change
     * @param value
     */
    void colorSlidersChanged(int);

    /**
     * @brief updateColorSliders - Updates the color sliders from the model when the tool changes
     * @param red - Red value
     * @param green - Green value
     * @param blue - Blue value
     * @param alpha - Opacity value
     */
    void updateColorSliders(int red, int green, int blue, int alpha);

    /**
     * @brief addPenClicked - Adds another pen tool to the tools list
     */
    void addPenClicked();

    /**
     * @brief handleOpen - Updates ui when a new document is opened
     */
    void handleOpen();

public:
    /**
     * @brief MainWindow - Initializes the main window
     * @param frameModel - Object with frames
     * @param parent - Parent widget
     */
    MainWindow(FrameModel &frameModel, QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~MainWindow();

public slots:
    /**
     * @brief updateBrushSpinBox - Updates the brush spin box value
     * @param value - New value for the brush spin box
     */
    void updateBrushSpinBox(int value);

signals:
    /**
     * @brief colorChanged - Signals the model that the color has changed
     * @param color - The new color value
     */
    void colorChanged(QColor color);
};
#endif // MAINWINDOW_H
