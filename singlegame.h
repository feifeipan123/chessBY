﻿#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "Board.h"

class SingleGame:public Board
{
    Q_OBJECT
public:
    SingleGame();
    virtual void click(int id, int row, int col);
    void getAllPossibleMove(QVector<Step *> &steps);
    Step* getBestMove();
    void fakeMove(Step *step);
    void unfakeMove(Step* step);
    int calcScore();
    int getMinScore(int level,int curMaxScore);
    int getMaxScore(int level,int curMinScore);
    int _level;

public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
