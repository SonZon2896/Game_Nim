#include <iostream>
#include <vector>

enum{
    GameStart = 1,
    OpenSettings,
    Quit,
    PlayerOne,
    PlayerTwo
};

void ClearConsole()
{
    system("cls");
}

/// @brief Input function
/// @tparam T 
/// @param input variable to input
template <typename T>
void Input(T& input)
{
    std::cin >> input;
}

/// @brief Input to PlayersMove()
/// @param row row in field
/// @param chips number of chips in row
void InputMove(int& row, int& chips)
{
    Input(row);
    Input(chips);
}

void PrintField(const std::vector<int> field)
{
    ClearConsole();
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

/// @brief make field by rows
/// @param rows variable in Menu()
/// @return 
std::vector<int> MakeField(int rows)
{
    std::vector<int> field(rows);
    for (int i = 0; i < rows; i++)
    {
        field[i] = 3 + i;
    }
    return field;
}

/// @brief 
/// @param field gaming field
/// @param allchips all chips in field
/// @param player which player is moving
/// @return return error(if player input error) - true, if not error - false
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
    ClearConsole();
    if (Winner == PlayerOne)
        std::cout << "First Player WINS!!!\n";
    else if (Winner == PlayerTwo)
        std::cout << "Second Player WINS!!!\n";
    else
        std::cout << "No Winner\n\n";
}

/// @brief main game colculation
/// @param field 
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

/// @brief game settings
/// @param rows rows in field
void Settings(int& rows)
{
    ClearConsole();
    std::cout << "Input rows in game: ";
    Input(rows);
    ClearConsole();
}

/// @brief main function
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
        ClearConsole();
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