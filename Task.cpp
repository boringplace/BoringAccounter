#include <iostream>
#include "Task.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using namespace std;

void Task::run()
{
    if (db.open()) {
        qDebug() << "Database opened!\n";
        qDebug() << db.tables();
        QSqlQuery query = db.exec("SELECT * FROM accounting.label");

        if (query.lastError().isValid())
            qDebug() << query.lastError().databaseText();
        while (query.next()) {
                QString id = query.value(0).toString();
                qDebug() << id;
        }
    } else {
        qDebug() << "Database not opened!\n";
    }

    emit finished();
}
