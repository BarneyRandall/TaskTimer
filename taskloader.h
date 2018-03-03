#ifndef TASKLOADER_H
#define TASKLOADER_H

#include "ktask.h"

class TaskLoader
{
public:
    TaskLoader();

    QList<kTask> loadTasksFromFile(const QString& filename);
    void saveTasksToFile(const QString& filename, QList<kTask>& taskList);

private:
    bool loadTask(QString& taskData, kTask& task);
};

#endif // TASKLOADER_H
