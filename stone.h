#ifndef STONE_H
#define STONE_H
#include <QString>


class Stone
{
public:
    Stone();
    ~Stone();
    enum TYPE{
        JIANG,
        CHE,
        PAO,
        MA,
        BING,
        SHI,
        XIANG
    };
    int _row;
    int _col;
    int _id;
    bool _dead;
    bool _red;
    TYPE _type;
    void init(int id);
    QString getText();
    void rotate();
};

#endif // STONE_H
