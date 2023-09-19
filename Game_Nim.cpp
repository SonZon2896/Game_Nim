#include <iostream>
#include <vector>

enum{
    GameStart = 1,
    OpenSettings,
    Quit,
    PlayerOne,
    PlayerTwo
};

template <typename T>
void Input(T& input)
{
    std::cin >> input;
}

void InputMove(int& row, int& chips)
{
    Input(row);
    Input(chips);
}

void PrintField(const std::vector<int> field)
{
    system("cls");
    for (int i = 0; i < field.size(); i++)
    {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < field[i]; j++)
        {
            std::cout << '*';
        }
        std::cout << std::endl;
    }
}

int SumChipsInField(const std::vector<int> field)
{
    int sum = 0;
    for (int i: field)
        sum += i;
    return sum;
}

std::vector<int> MakeField(int rows)
{
    std::vector<int> field(rows);
    for (int i = 0; i < rows; i++)
    {
        field[i] = 3 + i;
    }
    return field;
}

bool PlayersMove(std::vector<int>& field, int& allchips, const int player)
{
    int row, chips;
    PrintField(field);
    if (player == PlayerOne)
        std::cout << "First Player Move (row, chips): ";
    else if (player == PlayerTwo)
        std::cout << "Second Player Move (row, chips):  ";
    else
        std::cout << "No Player???";

    InputMove(row, chips);
    if (row > field.size() || row <= 0)
        return true;
    if (chips > field[--row] || chips <= 0)
        return true;

    field[row] -= chips;
    allchips -= chips;
    return false;
}

void PrintWinner(const int Winner)
{
    system("cls");
    if (Winner == PlayerOne)
        std::cout << "First Player WINS!!!\n";
    else if (Winner == PlayerTwo)
        std::cout << "Second Player WINS!!!\n";
    else
        std::cout << "No Winner\n\n";
}

void GameManager(std::vector<int> field)
{
    int allchips = SumChipsInField(field);
    int Winner = -1;
    int player = PlayerTwo;
    while (true)
    {
        bool isError = false;
        player == PlayerOne ? player = PlayerTwo : player = PlayerOne;
        do{
            isError = PlayersMove(field, allchips, player);
        } while (isError);

        if (allchips <= 0)
        {
            Winner = player;
            break;
        }
    }
    PrintWinner(Winner);
    return;
}

void Settings(int& rows)
{
    system("cls");
    std::cout << "Input rows in game: ";
    Input(rows);
    system("cls");
}

void Menu()
{
    int rows = 3;
    while (true)
    {
        int input = -1;
        int Winner = -1;
        std::vector<int> field = MakeField(rows);
        std::cout << "1 - Start Game\n" <<
            "2 - Change Settings\n" <<
            "3 - Quit\n";
        Input(input);
        system("cls");
        switch (input)
        {
        case GameStart:
            GameManager(field);
            break;
        case OpenSettings:
            Settings(rows);
            break;
        case Quit:
            return;
        default:
            break;
        }
    }
    return;
}

int main()
{
    Menu();

    return 0;
}