#ifndef SLIDERS_H
#define SLIDERS_H

#include <QObject>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class Sliders : public QObject
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    explicit Sliders(Ui::MainWindow *ui, QObject *parent = nullptr);

public slots:
    void setRedText();
    void setGreenText();
    void setBlueText();
    void setOpacityText();

    void setRedSlider(const QString colorCode);
    void setGreenSlider(const QString colorCode);
    void setBlueSlider(const QString colorCode);
    void setOpacitySlider(const QString colorCode);
};

#endif // SLIDERS_H
