#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tic_Tac_Toe.h"

class Tic_Tac_Toe : public QMainWindow
{
    Q_OBJECT

public:
    Tic_Tac_Toe(QWidget *parent = Q_NULLPTR);

private:
    Ui::Tic_Tac_ToeClass ui;
};
