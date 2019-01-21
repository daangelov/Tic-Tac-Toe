#include <iostream>
#include "include/Game.h"

using namespace std;

int main()
{
    Game ticTacToe;

    ticTacToe.printWelcomeMessage();

    bool userStarts;
    cin >> userStarts;

    ticTacToe.play(userStarts);
    return 0;
}
