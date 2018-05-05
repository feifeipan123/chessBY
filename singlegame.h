#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"

class SingleGame:public Board
{
public:
    virtual void click(int id, int row, int col);
    void getAllPossibleMove(QVector<Step *> &steps);
    Step* getBestMove();
    void fakeMove(Step *step);
    void unfakeMove(Step* step);
    int calcScore();
    int getMinScore();
};

#endif // SINGLEGAME_H
