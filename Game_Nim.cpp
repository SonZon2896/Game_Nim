#include <iostream>

enum{
    GameStart = 1,
    Settings,
    PlayerOne,
    PlayerTwo
};

bool PlayersMove(int* field, int&allchips, const int rows, const int player)
{
    int row, chips;
    if (player == PlayerOne)
        std::cout << "First Player Move (row, chips): ";
    else if (player == PlayerTwo)
        std::cout << "Second Player Move (row, chips):  ";

    std::cin >> row >> chips;
    if (row > rows || row <= 0)
        return true;
    if (chips > field[--row] || chips <= 0)
        return true;

    field[row] -= chips;
    allchips -= chips;
    return false;
}

void PrintField(const int* field, const int rows)
{
    std::cout << '\n';
    for (int i = 0; i < rows; i++)
    {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < field[i]; j++)
        {
            std::cout << '*';
        }
        std::cout << '\n';
    }
}

int main()
{
    int input = 100;
    int rows = 3;
    while (true)
    {
        std::cout << "1 - Start Game\n2 - Change Settings\n";
        std::cin >> input;

        bool isQuit = false;
        switch (input)
        {
        case GameStart:
            isQuit = true;
            break;
        case Settings:
            std::cout << "Print rows: ";
            std::cin >> rows;
            isQuit = true;
            break;
        default:
            break;
        }
        if (isQuit)
            break;
    }
    
    

    int allchips = 0;
    int* field = new int[rows];
    for (int i = 0; i < rows; i++)
    {
        field[i] = 3 + i;
        allchips += field[i];
    }

    // Game is started
    int Winner;
    while (true)
    {
        bool isError = false;
        PrintField(field, rows);

        do{
            isError = PlayersMove(field, allchips, rows, PlayerOne);
        } while (isError);

        if (allchips <= 0)
        {
            Winner = PlayerOne;
            break;
        }
        PrintField(field, rows);

        do{
            isError = PlayersMove(field, allchips, rows, PlayerTwo);
        } while (isError);

        if (allchips <= 0)
        {
            Winner = PlayerTwo;
            break;
        }
    }

    if (Winner == PlayerOne)
        std::cout << "First Player WINS!!!\n";
    else if (Winner == PlayerTwo)
        std::cout << "Second Player WINS!!!\n";

    std::cout << "Enter someting to quit: ";
    int a;
    std::cin >> a;

    delete[] field;
    return 0;
}