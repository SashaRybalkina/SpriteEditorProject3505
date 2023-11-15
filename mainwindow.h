#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Sliders.h"
#include "FrameModel.h"
#include "framepreview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void showFramePreview();
    /**
     * @brief colorSlidersChanged - changes the model when the sliders change
     * @param value
     */
    void colorSlidersChanged(int);

    /**
     *  @brief Updates the color sliders from the model when the tool changes
     */
    void changeColorSliders(int red, int green, int blue, int alpha);
    /**
     * @brief addPenClicked - adds another pen tool to the tools list.
     */
    void addPenClicked();


public:
    MainWindow(FrameModel& frameModel, QWidget *parent = nullptr);
    ~MainWindow();


signals:
    /**
     * @brief colorChanged - signals the model that the color has changed.
     * @param color
     */
    void colorChanged(QColor color);

private:
    Ui::MainWindow *ui;
    QStackedWidget* frameStack;
    FramePreview *framePreview;

    FrameModel& frameModel;
    int currentFrame;
    int totalFrames;

    void styleSetup();
    void colorRangeSetup();
    /**
     * @brief toolsSetup Helper method to segment out connect calls for tool functionality.
     * @param frameModel
     */
    void toolsSetup(FrameModel& frameModel);
    void updateFrameCount();
};

#endif // MAINWINDOW_H
