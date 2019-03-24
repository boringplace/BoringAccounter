#include <iostream>
#include "Task.h"

using namespace std;

void Task::run()
{
    cout << "Hello, World!\n";

    emit finished();
}
