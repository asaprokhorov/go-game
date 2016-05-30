#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#define FIELD_SIZE 9

#define BLACK 1
#define WHITE 2
#define FREE 0

#define BLACK_CHAR 'B'
#define WHITE_CHAR 'W'
#define FREE_CHAR '+'

void SplitBuffer(char buffer[], int result[]);
void CreateBuffer(int row, int col, char buffer[]);

class GameField
{
    int** field_;
    char GetSymbol(int row, int col);
    int Dame(int row, int col, int type);
    int DiagonalDame(int row, int col, int type);
    bool Atari(int row, int col);
    void KillGroup(int row, int col);
public:
    GameField();
    bool Move(int row, int col, int type);
    void Draw(int player_type);
    ~GameField();
};

#endif // GAMEFIELD_H
