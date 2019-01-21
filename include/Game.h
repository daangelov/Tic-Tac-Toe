#ifndef GAME_H
#define GAME_H

#include <array>
#include <vector>

#define boardSize 9
#define MAX 100
#define MIN -100
#define DRAW 0


class Game
{

private:
    std::array<char, boardSize> board;
    int depth;

public:
    Game();
    void printWelcomeMessage() const;
    void play(bool);

private:
    void printBoard() const;
    char winner(std::array<char, boardSize>) const;
    void displayWinner(char) const;
    void moveUser();
    void moveCpu();
    std::vector<int> getEmptySpots(std::array<char, boardSize>) const;
    int minimax(std::array<char, boardSize>, char, int, bool, int, int);
};

#endif // GAME_H
