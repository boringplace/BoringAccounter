#ifndef _TASK_H_
#define _TASK_H_

#include <QObject>

class Task: public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run();

signals:
    void finished();
};

#endif
