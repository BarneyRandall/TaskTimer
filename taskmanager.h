#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>

#include <QMap>

namespace kTaskTimer
{
    struct Task
    {
        std::string name;
        std::string description;

        time_t duraction;//in seconds
    };

    class TaskManager
    {
    public:
        TaskManager();

        void loadTaskList();

    private:
        QMap<std::string, Task> taskList;
    };
}
#endif // TASKMANAGER_H
