#include "../include/Game.h"
#include <iostream>
#include <math.h>
#include <array>
#include <vector>

using namespace std;

Game::Game()
{
    for (auto &element : this->board)
        element = '*';
    this->depth = 0;
}

void Game::printWelcomeMessage() const
{
    cout << "Tic Tac Toe Game" << endl;
    cout << "----------------" << endl;
    cout << "User  : (X)" << endl;
    cout << "CPU   : (O)" << endl;
    cout << "Select: 0 -> CPU first" << endl;
    cout << "        1 -> User first" << endl;
}

void Game::printBoard() const
{
    system("cls");
    int rowSize = sqrt(boardSize);
    int separatorSize = rowSize * 3 + rowSize - 1;
    string separator(separatorSize, '-');

    for (int i = 0; i < boardSize; i = i + rowSize)
    {
        for (int j = 0; j < rowSize; ++j)
        {
            cout << " " << this->board[i + j] << " ";
            if (j != rowSize - 1)
                cout << "|";
        }
        if (i != boardSize - rowSize)
            cout << endl << separator << endl;
    }
    cout << endl;
}

char Game::winner(array<char, boardSize> board) const
{
    int rowSize = sqrt(boardSize);
    // Check rows
    for (int i = 0; i < boardSize; i = i + rowSize)
    {
        char firstOnRow = board[i];
        for (int j = 1; j < rowSize; ++j)
        {
            if (firstOnRow == '*' || board[i + j] == '*' || firstOnRow != board[i + j])
                break;

            if (j == rowSize - 1)
                return firstOnRow;
        }
    }

    // Check cols
    for (int i = 0; i < rowSize; ++i)
    {
        char firstOnCol = board[i];
        for (int j = 1; j < rowSize; ++j)
        {
            if (firstOnCol == '*' || board[i + rowSize * j] == '*' || firstOnCol != board[i + rowSize * j])
                break;

            if (j == rowSize - 1)
                return firstOnCol;
        }
    }

    // Check main diag
    char firstOnDiag = board[0];
    for (int i = 0; i < boardSize; i = i + rowSize + 1)
    {
        if (firstOnDiag == '*' || board[i] == '*' || firstOnDiag != board[i])
            break;
        if (i == boardSize - 1)
            return firstOnDiag;
    }

    // Check second diag
    firstOnDiag = board[rowSize - 1];
    for (int i = rowSize - 1; i < boardSize; i = i + rowSize - 1)
    {
        if (firstOnDiag == '*' || board[i] == '*' || firstOnDiag != board[i])
            break;
        if (i == boardSize - rowSize)
            return firstOnDiag;
    }

    // Check for empty spaces
    for (int i = 0; i < boardSize; ++i)
    {
        if (board[i] == '*')
            return 'N';
    }

    return 'D';
}

void Game::moveUser()
{
    int x, y;
    cout << "Enter x and y: ";
    cin >> x >> y;

    int boardIndex = 3 * (x - 1) + (y - 1);
    while (this->board[boardIndex] != '*')
    {
        cout << "Invalid Move." << endl;
        cin >> x >> y;
        boardIndex = 3 * (x - 1) + (y - 1);
    }
    this->board[boardIndex] = 'X';
}

vector<int> Game::getEmptySpots(array<char, boardSize> board) const
{
    vector<int> emptySpots;
    for (int i = 0; i < boardSize; ++i)
    {
        if (board[i] == '*')
            emptySpots.push_back(i);
    }

    return emptySpots;
}

void Game::moveCpu()
{
    vector<int> emptySpots = this->getEmptySpots(this->board);

    int bestIndex = emptySpots[0];
    int bestValue = MIN;

    for (unsigned int i = 0; i < emptySpots.size(); ++i)
    {
        array<char, boardSize> nextBoard = this->board;

        int spot = emptySpots[i];
        nextBoard[spot] = 'O';
        int value = this->minimax(nextBoard, 'X', this->depth, false, MIN, MAX);

        if (value > bestValue)
        {
            bestValue = value;
            bestIndex = spot;
        }
    }
    if (this->board[bestIndex] != '*')
        cout << "SHIT" << endl;

    this->board[bestIndex] = 'O';
}

int Game::minimax(array<char, boardSize> board, char player, int depth, bool maximiser, int alpha, int beta)
{
    char win = this->winner(board);

    // Terminal states
    if (win == 'D')
        return DRAW - depth;
    if (win == 'X')
        return MIN - depth;
    if (win == 'O')
        return MAX - depth;

    // Else
    char otherPlayer = (player == 'X') ? 'O' : 'X';

    if (maximiser)
    {
        int best = MIN;
        vector<int> emptySpots = this->getEmptySpots(board);
        for (auto &spot : emptySpots)
        {
            array<char, boardSize> nextBoard = board;
            nextBoard[spot] = player;
            int value = minimax(nextBoard, otherPlayer, depth + 1, false, alpha, beta);

            best = max(best, value);
            alpha = max(alpha, best);

            if (beta <= alpha)
                break;
        }
        return best;
    }
    else
    {
        int best = MAX;
        vector<int> emptySpots = this->getEmptySpots(board);
        for (auto &spot : emptySpots)
        {
            array<char, boardSize> nextBoard = board;
            nextBoard[spot] = player;
            int value = minimax(nextBoard, otherPlayer, depth + 1, true, alpha, beta);

            best = min(best, value);
            beta = min(beta, best);

            if (beta <= alpha)
                break;
        }
        return best;
    }
}

void Game::displayWinner(char winner) const
{
    cout << "Game ended" << endl;
    if (winner != 'D')
        cout << "Winner: " << winner << endl;
    else
        cout << "Draw";
}

void Game::play(bool userTurn)
{
    this->printBoard();

    char winner = this->winner(this->board);
    if (winner != 'N')
        this->displayWinner(winner);
    else
    {
        if (userTurn)
            this->moveUser();
        else
            this->moveCpu();

        this->play(!userTurn);
    }
}
