#include "mainwindow.h"
#include "framemodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Sliders sliders;
    FrameModel frameModel;
    Frame frame;
    MainWindow w(frameModel, frame);
    w.show();

    return a.exec();
}
