#include "ktask.h"

kTask::kTask()
{

}

kTask::kTask(QString name, QString desc, QTime duration, int taskId)
    : taskName(name)
    , taskDescription(desc)
    , taskDuration(duration)
    , taskId(taskId)
{

}
