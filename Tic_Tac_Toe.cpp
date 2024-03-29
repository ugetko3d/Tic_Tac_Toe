#include "Tic_Tac_Toe.h"

Tic_Tac_Toe::Tic_Tac_Toe(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    messageBox = new QMessageBox;
    
    // Initialize the board
    resetBoard();

    // Connect signals to functions (clicking on the reset button, and clicking in a cell)
    connect(ui.tbl_grid, &QTableWidget::cellClicked, this, &Tic_Tac_Toe::onCellClicked);
    connect(ui.btn_reset, &QPushButton::released, this, &Tic_Tac_Toe::onButtonResetClicked);
}

Tic_Tac_Toe::~Tic_Tac_Toe()
{
    delete messageBox;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Delete cells
            QTableWidgetItem* cell = ui.tbl_grid->item(i, j);
            if (cell)
                delete cell;
        }
    }
}

bool Tic_Tac_Toe::isMovesLeft()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int Tic_Tac_Toe::evaluate()
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2])
        {
            if (board[row][0] == player)
                return -10;
            else if (board[row][0] == computer)
                return +10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col])
        {
            if (board[0][col] == player)
                return -10;

            else if (board[0][col] == computer)
                return +10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == player)
            return -10;
        else if (board[0][0] == computer)
            return +10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == player)
            return -10;
        else if (board[0][2] == computer)
            return +10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int Tic_Tac_Toe::miniMax(int depth, bool isMax)
{
    int score = evaluate();

    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 10)
        return score;

    // If Minimizer has won the game return his/her
    // evaluated score
    if (score == -10)
        return score;

    // If there are no more moves and no winner then
    // it is a tie
    if (!isMovesLeft())
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        // Start with an awful score, any cell will have a better score than this.
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == '_')
                {
                    // Make the move
                    board[i][j] = computer;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = std::max(best,
                        miniMax(depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        // Start with a great score, any cell will have a worse score than this.
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == '_')
                {
                    // Make the move
                    board[i][j] = player;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = std::min(best,
                        miniMax(depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

void Tic_Tac_Toe::computerTurn()
{
    // Computer will now make its turn
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (board[i][j] == '_')
            {
                // Make the move
                board[i][j] = computer;

                // compute evaluation function for this
                // move.
                int moveVal = miniMax(0, false);

                // Undo the move
                board[i][j] = '_';

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestMove.row][bestMove.col] = computer;
    ui.tbl_grid->item(bestMove.row, bestMove.col)->setBackground(Qt::red);
}

bool Tic_Tac_Toe::isGameEnd()
{
    int score = evaluate();
    if (score == 10)
    {
        messageBox->setText("The computer won... again.");
        messageBox->show();
        return true;
    }
    else if (score == -10)
    {
        messageBox->setText("You won! How did you manage to win!?!?!?");
        messageBox->show();
        return true;
    }
    else if (!isMovesLeft())
    {
        messageBox->setText("Draw...");
        messageBox->show();
        return true;
    }
    return false;
}

void Tic_Tac_Toe::onCellClicked(int row, int col)
{
    if (isGameEnd())
        return;

    // User picked a cell
    if (board[row][col] != '_')
    {
        messageBox->setText("This cell is already taken!");
        messageBox->show();
        return;
    }
        
    board[row][col] = player;
    ui.tbl_grid->item(row, col)->setBackground(Qt::blue);
    ui.tbl_grid->item(row, col)->setSelected(false);

    if (isGameEnd())
        return;

    computerTurn();


    if (isGameEnd())
        return;

}

void Tic_Tac_Toe::onButtonResetClicked()
{
    // Initialise the board
    resetBoard();

    // Computer (X) shall move first if not user has specified that player shall move first
    m_isFirst = ui.cb_goFirst->isChecked();

    if (!m_isFirst)
        computerTurn();
}

void Tic_Tac_Toe::resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '_';

            // If cell is null (first time start program), create it
            if (!ui.tbl_grid->item(i, j))
                ui.tbl_grid->setItem(i, j, new QTableWidgetItem);

            ui.tbl_grid->item(i, j)->setBackground(Qt::white);
        }
    }
}


