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

public:
    MainWindow(FrameModel& frameModel, Frame& frame, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget* frameStack;
    FramePreview *framePreview;

    void styleSetup();
    void colorRangeSetup();
};

#endif // MAINWINDOW_H
