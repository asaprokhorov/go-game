#include "gamefield.h"

GameField::GameField()
{
    field_ = new int*[FIELD_SIZE];
    for(int i = 0; i < FIELD_SIZE; ++i)
    {
        field_[i] = new int[FIELD_SIZE];
        for(int j = 0; j < FIELD_SIZE; ++j)
        {
            field_[i][j] = FREE;
        }
    }
}

int GameField::Dame(int row, int col, int type)
{
    int result = 0;
    if(row > 0)
    {
        result += field_[row - 1][col] == type ? 1 : 0;
    }
    if(col > 0)
    {
        result += field_[row][col - 1] == type ? 1 : 0;
    }
    if(row < FIELD_SIZE - 1)
    {
        result += field_[row + 1][col] == type ? 1 : 0;
    }
    if(col < FIELD_SIZE - 1)
    {
        result += field_[row][col + 1] == type ? 1 : 0;
    }
    return result;
}

int GameField::DiagonalDame(int row, int col, int type)
{
    int result = 0;
    if(row > 0 && col > 0)
    {
        result += field_[row - 1][col - 1] == type ? 1 : 0;
    }
    if(row > 0 && col < FIELD_SIZE - 1)
    {
        result += field_[row - 1][col + 1] == type ? 1 : 0;
    }
    if(row < FIELD_SIZE - 1 && col > 0)
    {
        result += field_[row + 1][col - 1] == type ? 1 : 0;
    }
    if(row < FIELD_SIZE - 1 && col < FIELD_SIZE - 1)
    {
        result += field_[row + 1][col + 1] == type ? 1 : 0;
    }
    return result;
}

bool GameField::Atari(int row, int col)
{
    bool result = false;
    int type = field_[row][col];
    if(Dame(row, col, FREE) == 0)
    {
        if(Dame(row, col, type) > 0)
        {
            field_[row][col] = type == WHITE ? BLACK : WHITE;
            if(row > 0)
            {
                if(field_[row - 1][col] == type && (result || Atari(row - 1, col))) result = true;
            }
            if(col > 0)
            {
                if(field_[row][col - 1] == type && (result || Atari(row, col - 1))) result = true;
            }
            if(row < FIELD_SIZE - 1)
            {
                if(field_[row + 1][col] == type && (result || Atari(row + 1, col))) result = true;
            }
            if(col < FIELD_SIZE - 1)
            {
                if(field_[row][col + 1] == type && (result || Atari(row, col + 1))) result = true;
            }
            field_[row][col] = type;
        }
        else
        {
            result = true;
        }
    }
    return result;
}

void GameField::KillGroup(int row, int col)
{
    int type = field_[row][col];
    field_[row][col] = FREE;
    if(row > 0)
    {
        if(field_[row - 1][col] == type)
        {
            KillGroup(row - 1, col);
        }
    }
    if(col > 0)
    {
        if(field_[row][col - 1] == type)
        {
            KillGroup(row, col - 1);
        }
    }
    if(row < FIELD_SIZE - 1)
    {
        if(field_[row + 1][col] == type)
        {
            KillGroup(row + 1, col);
        }
    }
    if(col < FIELD_SIZE - 1)
    {
        if(field_[row][col + 1] == type)
        {
            KillGroup(row, col + 1);
        }
    }
}

bool GameField::Move(int row, int col, int type)
{
    bool result = false;
    if (type != BLACK && type != WHITE) return false;
    if(row == 0) return true;
    row--;
    col--;

    if(row < FIELD_SIZE && row >= 0 && col < FIELD_SIZE && col >= 0)
    {
        if(field_[row][col] == FREE)
        {
            field_[row][col] = type;
            if(!Atari(row, col))
            {
                result = true;
                int opponent = type == WHITE ? BLACK : WHITE;
                if(row > 0)
                {
                    if(field_[row - 1][col] == opponent)
                    {
                        if(Atari(row - 1, col))
                        KillGroup(row - 1, col);
                    }
                }
                if(col > 0)
                {
                    if(field_[row][col - 1] == opponent)
                    {
                        if(Atari(row, col - 1))
                        KillGroup(row, col - 1);
                    }
                }
                if(row < FIELD_SIZE - 1)
                {
                    if(field_[row + 1][col] == opponent)
                    {
                        if(Atari(row + 1, col))
                        KillGroup(row + 1, col);
                    }
                }
                if(col < FIELD_SIZE - 1)
                {
                    if(field_[row][col + 1] == opponent)
                    {
                        if(Atari(row, col + 1))
                        KillGroup(row, col + 1);
                    }
                }
            }
            else if (DiagonalDame(row, col, type))
            {
                bool kill = false;
                int opponent = type == WHITE ? BLACK : WHITE;
                if(row > 0)
                {
                    if(field_[row - 1][col] == opponent)
                    {
                        if(Atari(row - 1, col))
                        {
                            kill = true;
                            KillGroup(row - 1, col);
                        }
                    }
                }
                if(col > 0)
                {
                    if(field_[row][col - 1] == opponent)
                    {
                        if(Atari(row, col - 1))
                        {
                            kill = true;
                            KillGroup(row, col - 1);
                        }
                    }
                }
                if(row < FIELD_SIZE - 1)
                {
                    if(field_[row + 1][col] == opponent)
                    {
                        if(Atari(row + 1, col))
                        {
                            kill = true;
                            KillGroup(row + 1, col);
                        }
                    }
                }
                if(col < FIELD_SIZE - 1)
                {
                    if(field_[row][col + 1] == opponent)
                    {
                        if(Atari(row, col + 1))
                        {
                            kill = true;
                            KillGroup(row, col + 1);
                        }
                    }
                }
                if(!kill)
                {
                    field_[row][col] = FREE;
                }
                else
                {
                    result = true;
                }
            }
            else
            {
                field_[row][col] = FREE;
            }
        }
    }
    return result;
}

char GameField::GetSymbol(int row, int col)
{
    char result;
    if (field_[row][col] == BLACK)
    {
        result = BLACK_CHAR;
    }
    else if (field_[row][col] == WHITE)
    {
        result = WHITE_CHAR;
    }
    else
    {
        result = FREE_CHAR;
    }
    return result;
}

void GameField::Draw(int player_type)
{
    char player_char = player_type == WHITE ? WHITE_CHAR : BLACK_CHAR;
#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("------------------------------GO GAME-------------------------------\nPlayer: %c\n\n", player_char);
    char type;
    printf("\t");
    for(int i = 0; i < FIELD_SIZE - 1; ++i)
    {
        printf("%d   ", i + 1);
    }
    printf("%d\n\n", FIELD_SIZE);
    for(int i = 0; i < FIELD_SIZE - 1; ++i)
    {
        printf("%d\t", i + 1);
        for(int j = 0; j < FIELD_SIZE - 1; ++j)
        {
            type = GetSymbol(i, j);
            printf("%c - ", type);
        }
        type = GetSymbol(i, FIELD_SIZE - 1);
        printf("%c\n\t", type);
        for(int j = 0; j < FIELD_SIZE - 1; ++j)
        {
            printf("|   ");
        }
        printf("|\n");
    }
    printf("%d\t", FIELD_SIZE);
    for(int j = 0; j < FIELD_SIZE - 1; ++j)
    {
        type = GetSymbol(FIELD_SIZE - 1, j);
        printf("%c - ", type);
    }
    type = GetSymbol(FIELD_SIZE - 1, FIELD_SIZE - 1);
    printf("%c\n", type);
}

GameField::~GameField()
{
    for(int i = 0; i < FIELD_SIZE; ++i)
    {
        delete[] field_[i];
    }
    delete[] field_;
}

void SplitBuffer(char buffer[], int result[])
{
    char tock[2048];
    int count = 0;
    int k = 0;
    int len = strlen(buffer);
    for(int i = 0; i < len; ++i)
    {
        if(buffer[i] != '|')
        {
            tock[k] = buffer[i];
            k++;
        }
        else
        {
            tock[k] = '\0';
            result[count] = atoi(tock);
            k = 0;
            count++;
        }
    }
    tock[k] = '\0';
    result[count] = atoi(tock);
}

void CreateBuffer(int row, int col, char buffer[])
{
    char numb[10];
    strcpy(buffer, "");
    sprintf(numb, "%d", row);
    strcat(buffer, numb);
    strcat(buffer, "|");
    sprintf(numb, "%d", col);
    strcat(buffer, numb);
    strcat(buffer, "|");
}
