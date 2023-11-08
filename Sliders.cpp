#include "Sliders.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Sliders::Sliders(Ui::MainWindow *ui, QObject *parent) : QObject{parent}, ui(ui)
{

}

void Sliders::setRedText()
{
    const QString redCode = QString::number(ui -> redSlider -> value());
    ui -> redInput -> setText(redCode);
}

void Sliders::setGreenText()
{
    const QString greenCode = QString::number(ui -> greenSlider -> value());
    ui -> greenInput -> setText(greenCode);
}

void Sliders::setBlueText()
{
    const QString blueCode = QString::number(ui -> blueSlider -> value());
    ui -> blueInput -> setText(blueCode);
}

void Sliders::setOpacityText()
{
    const QString opacityCode = QString::number(ui -> opacitySlider -> value());
    ui -> opacityInput -> setText(opacityCode);
}

void Sliders::setRedSlider(const QString colorCode)
{
    ui -> redSlider -> setValue(colorCode.toInt());
}

void Sliders::setGreenSlider(const QString colorCode)
{
    ui -> greenSlider -> setValue(colorCode.toInt());
}

void Sliders::setBlueSlider(const QString colorCode)
{
    ui -> blueSlider -> setValue(colorCode.toInt());
}

void Sliders::setOpacitySlider(const QString colorCode)
{
    ui -> opacitySlider -> setValue(colorCode.toInt());
}
