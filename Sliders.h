#ifndef SLIDERS_H
#define SLIDERS_H

#include <QObject>
#include <iostream>
#include "ui_mainwindow.h"

/**
 * @brief The Sliders class - Handles updating UI sliders and input fields
 */
class Sliders : public QObject
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    /**
     * @brief Sliders - Constructor for the Sliders class
     * @param ui - Pointer to the MainWindow UI
     * @param parent - Parent QObject
     */
    explicit Sliders(Ui::MainWindow *ui, QObject *parent = nullptr);

public slots:
    /**
     * @brief setRedText - Slot to set the text for the red slider
     */
    void setRedText();

    /**
     * @brief setGreenText - Slot to set the text for the green slider
     */
    void setGreenText();

    /**
     * @brief setBlueText - Slot to set the text for the blue slider
     */
    void setBlueText();

    /**
     * @brief setOpacityText - Slot to set the text for the opacity slider
     */
    void setOpacityText();

    /**
     * @brief setRedSlider - Slot to set the value of the red slider
     * @param colorCode - The new value for the red slider
     */
    void setRedSlider(const QString colorCode);

    /**
     * @brief setGreenSlider - Slot to set the value of the green slider
     * @param colorCode - The new value for the green slider
     */
    void setGreenSlider(const QString colorCode);

    /**
     * @brief setBlueSlider - Slot to set the value of the blue slider
     * @param colorCode - The new value for the blue slider
     */
    void setBlueSlider(const QString colorCode);

    /**
     * @brief setOpacitySlider - Slot to set the value of the opacity slider
     * @param colorCode - The new value for the opacity slider
     */
    void setOpacitySlider(const QString colorCode);
};
#endif // SLIDERS_H
