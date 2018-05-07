#include "netgame.h"
#include <QDebug>

NetGame::NetGame(bool server)
{
    _server = NULL;
    _socket = NULL;
    if(server){
        _server=new QTcpServer(this);
        _server->listen(QHostAddress::Any,9999);
        connect(_server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    }else{
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"),9999);
    }

}

NetGame::~NetGame()
{

}

void NetGame::slotNewConnection(){
    if(_socket) return;
    _socket = _server->nextPendingConnection();
    qDebug()<<"connect";

}
