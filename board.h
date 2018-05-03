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
    /*返回象棋棋盘行列对应的像素坐标*/
    QPoint center(int row,int col);
    QPoint center(int id);
    void drawStone(QPainter& painter,int id);
    //获取鼠标点击点的行列值
    bool getRowCol(QPoint pt,int &row,int &col);
    bool canMove(int moveid,int row,int col,int killid);

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

public slots:
};

#endif
