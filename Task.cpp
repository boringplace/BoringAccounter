#include <iostream>
#include "Task.h"

using namespace std;

void Task::run()
{
    if (db.open()) {
        cout << "Database opened!\n";
    } else {
        cout << "Database not opened!\n";
    }

    emit finished();
}
