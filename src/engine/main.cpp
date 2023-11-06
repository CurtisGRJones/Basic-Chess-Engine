#include <iostream>
#include <string>
#include "../shared/position/position.h"

int main()
{
    try
    {
        std::array<std::array<char, 8>, 8> board = {};
        Position *position = new Position();
        while (true)
        {
            std::cout << position->getTurnString() << "'s turn\n";
            for (int i = 7; i >= 0; i--)
            {
                std::cout << i + 1 << ' ';
                for (int j = 0; j < 8; j++)
                {
                    std::cout << position->getPeiceCharAt(i, j) << ' ';
                }
                std::cout << '\n';
            }
            std::cout << "  A B C D E F G H\n\nWhat is your move?\n";

            position->showMovesFromPawn(48);

            std::string move;

            std::cin >> move;

            position->makeMove((std::string)move);
        }

        delete position;
    }
    catch (...)
    {
        std::cout << "\nAn unexpected error occured";
    }

    std::cout << std::endl;
    return 0;
}