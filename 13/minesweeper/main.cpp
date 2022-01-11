#include "square.hh"
#include "gameboard.hh"
#include <iostream>

// Reads values for x and y that are passed by reference for the caller.
bool readCoordinates(int& x, int& y)
{
    std::cout << "x y> ";
    return std::cin >> x and std::cin >> y;
}

// Reads seed value given by the user and returns it for the caller.
int readSeedValue()
{
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);

    if(seed == "")
    {
        // If the user did not give a seed value,
        // use computer time as the seed value.
        return time(NULL);
    }
    else
    {
        // If the user gave a seed value, use it.
        return stoi(seed);
    }
}

// Prints the question given as a parameter and interpretes the given string.
bool flagQuestion(std::string question)
{
    std::string answer = "";
    do
    {
        std::cout << question;
        std::cin >> answer;
    } while(answer != "Y" and answer != "y" and
            answer != "N" and answer != "n");

    return (answer == "Y" or answer == "y");
}

int main()
{
    GameBoard board;
    int seed = readSeedValue();
    board.init(seed);
    board.print(std::cout);

    int x = 0;
    int y = 0;

    while(not board.isGameOver() and readCoordinates(x, y))
    {
        Square square = board.getSquare(x - 1, y - 1);
        if(square.hasFlag())
        {
            if(flagQuestion("Do you want to remove the flag? (Y/N) "))
            {
                square.removeFlag();
            }
        }
        else if(not flagQuestion("Do you want to add a flag? (Y/N) "))
        {
            if(not square.open())
            {
                std::cout << "BOOOM! Game over!" << std::endl;
                board.print(std::cout);
                std::cout << "You lost ..." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            square.addFlag();
        }
        // Until now modifications have been targeted to a local object square,
        // and thus, the modifications must be copied into the game board.
        board.setSquare(square, x - 1, y - 1);
        board.print(std::cout);
    }
    std::cout << "You won, yay!" << std::endl;
    return EXIT_SUCCESS;
}
