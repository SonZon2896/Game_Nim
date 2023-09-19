#include <iostream>
#include <vector>

enum{
    GameStart = 1,
    OpenSettings,
    Quit,
    PlayerOne,
    PlayerTwo
};

static std::vector<int> prevfield;
static std::vector<int> field;
static bool GameWithBot;

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

int SumChipsInField()
{
    int sum = 0;
    for (int i: field)
        sum += i;
    return sum;
}

void PrintField()
{
    ClearConsole();
    for (int i = 0; i < field.size(); i++)
    {
        std::cout << i + 1 << ' ';
        if (GameWithBot)
            for (int j = 0; j < prevfield[i]; j++)
            {
                if (j < field[i])
                    std::cout << '*';
                else
                    std::cout << '$';
            }
        else
            for (int j = 0; j < field[i]; j++)
            {
                std::cout << '*';
            }
        std::cout << std::endl;
    }
    //std::cout << SumChipsInField() << std::endl;
}

/// @brief make field by rows
/// @param rows variable in Menu()
/// @return 
std::vector<int> MakeField(int rows)
{
    std::vector<int> tempfield(rows);
    for (int i = 0; i < rows; i++)
    {
        tempfield[i] = 3 + i;
    }
    prevfield = tempfield;
    return tempfield;
}

int NimSum(std::vector<int> Field = field)
{
    int nimSum = 0;
    for (auto i: Field)
        nimSum ^= i;
    return nimSum;
}

/// @brief bot
/// @param field 
/// @return row, chips
std::vector<int> botMove()
{
    if (NimSum() == 0)
    {
        for (int i = 0; i < field.size(); i++)
        {
            if (field[i] > 2)
                return {i + 1, field[i] - 2};
            else if (field[i] != 0)
                return {i + 1, 1};
        }
    }
    std::vector<int> Move(2);
    std::vector<int> tempField = field;
    for (int i = 0; i < field.size(); i++)
    {
        for (int j = 0; j < field[i] + 1; j++)
        {
            tempField[i] -= j;
            if (NimSum(tempField) == 0)
                return {i + 1, j};
            tempField[i] += j;
        }
    }
    return {-1, -1};
}

/// @brief 
/// @param field gaming field
/// @param allchips all chips in field
/// @param player which player is moving
/// @return return error(if player input error) - true, if not error - false
bool PlayersMove(int& allchips, const int player)
{
    PrintField();
    if (player == PlayerOne)
        std::cout << "First Player Move (row, chips): ";
    else if (player == PlayerTwo)
        std::cout << "Second Player Move (row, chips):  ";
    else
        std::cout << "No Player???";
    
    int row, chips;
    if (GameWithBot && player == PlayerTwo)
    {
        std::vector<int> BotMove = botMove();
        row = BotMove[0];
        chips = BotMove[1];
        std::cout << row << ' ' << chips << std::endl;
    }
    else
        InputMove(row, chips);
    
    if (row > field.size() || row <= 0)
        return true;
    if (chips > field[--row] || chips <= 0)
        return true;

    prevfield = field;
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
void GameManager()
{
    int allchips = SumChipsInField();
    int Winner = -1;
    int player = PlayerTwo;
    while (true)
    {
        bool isError = false;
        player == PlayerOne ? player = PlayerTwo : player = PlayerOne;
        do{
            isError = PlayersMove(allchips, player);
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
    std::cout << "Do you want play with bot? (y/n): ";
    char input;
    Input(input);
    if (input == 'y')
        GameWithBot = true;
    else if (input == 'n')
        GameWithBot = false;
    ClearConsole();
}

/// @brief main function
void Menu()
{
    int rows = 3;
    GameWithBot = true;
    while (true)
    {
        int input = -1;
        int Winner = -1;
        field = MakeField(rows);
        std::cout << "1 - Start Game\n" <<
            "2 - Change Settings\n" <<
            "3 - Quit\n";
        Input(input);
        ClearConsole();
        switch (input)
        {
        case GameStart:
            GameManager();
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