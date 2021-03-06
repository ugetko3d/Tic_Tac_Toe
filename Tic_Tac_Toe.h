#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_Tic_Tac_Toe.h"

#include <vector>
#include <iostream>
#include <algorithm>

class Tic_Tac_Toe : public QMainWindow
{
    Q_OBJECT

public:
    Tic_Tac_Toe(QWidget *parent = Q_NULLPTR);
    ~Tic_Tac_Toe();

private:
    bool isMovesLeft();
    int evaluate();
    int miniMax(int depth, bool isMax);
    bool isGameEnd();
    void computerTurn();

    struct Move
    {
        int row, col;
    };

    Ui::Tic_Tac_ToeClass ui;
    QMessageBox* messageBox;

    char board[3][3];
    char player = 'o';
    char computer = 'x';


private slots:
    void onCellClicked(int row, int col);
    void onButtonResetClicked();
};
