#ifndef NETGAME_H
#define NETGAME_H
#include "board.h"
#include <QTcpServer>
#include <QTcpSocket>

class NetGame:public Board
{
    Q_OBJECT
public:
    NetGame(bool server);
    ~NetGame();
    QTcpServer* _server;
    QTcpSocket* _socket;
public slots:
    void slotNewConnection();
};

#endif // NETGAME_H
