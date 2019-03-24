#include <QCoreApplication>
#include <QTimer>
#include "Task.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Task *task = new Task(&app);

    QObject::connect(task, SIGNAL(finished()), &app, SLOT(quit()));

    QTimer::singleShot(500, task, SLOT(run()));

    return app.exec();
}
