#ifndef _TASK_H_
#define _TASK_H_

#include <QObject>
#include <QSqlDatabase>

class Task: public QObject
{
    Q_OBJECT
    QSqlDatabase db;

public:
    Task(QObject *parent = 0) : QObject(parent)
    {
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setDatabaseName("boringdb");
        db.setHostName("hp.boringplace.net");

        QString user = qgetenv("USER");
        if (user.isEmpty())
            user = qgetenv("USERNAME");
        db.setUserName(user);
    }

public slots:
    void run();

signals:
    void finished();
};

#endif
