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
    bool _bSide;

    /*game status*/
    int _selectid;//选中的棋子标号
    bool _bRedTurn;//轮到红棋走
    void init(bool bRedSize);
    /*返回象棋棋盘行列对应的像素坐标*/
    QPoint center(int row,int col);
    QPoint center(int id);
    void drawStone(QPainter& painter,int id);

    int getStoneId(int row, int col);
    void killStone(int id);
    bool isDead(int id);
    bool sameColor(int id1, int id2);
    bool red(int id);
    bool getRowCol(QPoint pt,int &row,int &col);//获取鼠标点击点的行列值
    bool getClickRowCol(QPoint pt, int& row, int& col);
    /* move stone */
    void click(QPoint pt);
    virtual void click(int id, int row, int col);
    void trySelectStone(int id);
    void tryMoveStone(int killid, int row, int col);
    void moveStone(int moveid, int row, int col,int killid);
     void moveStone(int moveid, int row, int col);

    /* rule */
    bool canMove(int moveid,int row,int col,int killid);
    bool canMoveJiang(int moveid,int row,int col,int);
    bool canMoveShi(int moveid,int row,int col,int killid);
    bool canMoveXiang(int moveid,int row,int col,int killid);
    bool canMoveMa(int moveid, int row, int col, int);
    bool canMoveBing(int moveid, int row, int col, int);
    bool canMoveChe(int moveid, int row, int col,int killid);
     bool canMovePao(int moveid, int row, int col,int killid);
     bool canSelect(int id);

    /* draw functions */
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    /* rule helper */
    bool isBottomSide(int id);
    int getStoneCountAtLine(int row1, int col1, int row2, int col2);
    int relation(int row1, int col1, int row, int col);

signals:

public slots:
};

#endif
