#include "mainwindow.h"
#include "framemodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Sliders sliders;
    FrameModel frameModel;
    MainWindow w(frameModel);
    w.show();
    return a.exec();
}
