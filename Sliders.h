#ifndef SLIDERS_H
#define SLIDERS_H

#include <QObject>
#include <iostream>
#include "ui_mainwindow.h"

class Sliders : public QObject
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    explicit Sliders(Ui::MainWindow *ui, QObject *parent = nullptr);

public slots:
    /**
     * @brief setRedText sets the text of the label near the red slider to the value of the red slider
     */
    void setRedText();
    /**
     * @brief setGreenText sets the text of the label near the green slider to the value of the green slider
     */
    void setGreenText();
    /**
     * @brief setBlueText sets the text of the label near the blue slider to the value of the blue slider
     */
    void setBlueText();
    /**
     * @brief setRedText sets the text of the label near the opacity slider to the value of the opacity slider
     */
    void setOpacityText();

    /**
     * @brief setRedSlider sets the value of the red slider to the text in the label near the red slider
     */
    void setRedSlider(const QString colorCode);
    /**
     * @brief setGreenSlider sets the value of the green slider to the text in the label near the green slider
     */
    void setGreenSlider(const QString colorCode);
    /**
     * @brief setBlueSlider sets the value of the blue slider to the text in the label near the blue slider
     */
    void setBlueSlider(const QString colorCode);
    /**
     * @brief setOpacitySlider sets the value of the opacity slider to the text in the label near the opacity slider
     */
    void setOpacitySlider(const QString colorCode);
};

#endif // SLIDERS_H
