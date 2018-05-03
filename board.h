#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    Stone _s[32];
    int _r;//棋子的半径
    int _selectid;//选中的棋子标号
    bool bRedTurn = true;//轮到红棋走
    /*返回象棋棋盘行列对应的像素坐标*/
    QPoint center(int row,int col);
    QPoint center(int id);
    void drawStone(QPainter& painter,int id);
    int relation(int row1, int col1, int row, int col);
    int getStoneId(int row, int col);
    bool isDead(int id);
    //获取鼠标点击点的行列值
    bool getRowCol(QPoint pt,int &row,int &col);
    bool canMove(int moveid,int row,int col,int killid);
    bool canMoveJiang(int moveid,int row,int col,int killid);
    bool canMoveShi(int moveid,int row,int col,int killid);
    bool canMoveXiang(int moveid,int row,int col,int killid);
    bool canMoveMa(int moveid, int row, int col, int);
    bool canMoveBing(int moveid, int row, int col, int);

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
};

#endif
