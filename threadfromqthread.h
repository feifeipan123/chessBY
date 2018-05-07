﻿#ifndef THREADFROMQTHREAD_H
#define THREADFROMQTHREAD_H
#include <QThread>

class ThreadFromQThread:public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    ThreadFromQThread(QObject* par);
    ~ThreadFromQThread();
    virtual void run();
};

#endif // THREADFROMQTHREAD_H
