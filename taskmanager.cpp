#include "taskmanager.h"

TaskManager::TaskManager(QList<kTask> taskList)
    : taskList(taskList),
      currentTask(nullptr),
      currentTaskId(0)
{

}

void TaskManager::startTasks()
{
    currentTaskId = 0;
    timerList.clear();
    startTask(currentTaskId);
}

void TaskManager::stopTasks()
{
    int numTimers = timerList.size();
    if(numTimers > 0)
    {
        timerList[numTimers - 1]->stopTimer();
    }
    timerList.clear();
    currentTaskId = 0;
}

void TaskManager::pauseTasks()
{

}

void TaskManager::onCurrentTimerUpdates(qint64 secondsRemaining)
{
    int seconds, minutes, hours;
    seconds = secondsRemaining % 60;
    minutes = secondsRemaining / 60;
    hours = minutes / 60;

    QString hoursString = QString::number(hours).rightJustified(2, '0');
    QString minutesString = QString::number(minutes).rightJustified(2, '0');
    QString secondsString = QString::number(seconds).rightJustified(2, '0');
    QString timerText = hoursString + ":" + minutesString + ":" + secondsString;

    emit onTaskTimeChanged(timerText);
}

void TaskManager::onCurrentTimerEnds()
{
    if(++currentTaskId < taskList.size())
    {
        TaskTimer* timer = timerList[timerList.size() -1];
        disconnect(timer, &TaskTimer::onTimerUpdates, this, &TaskManager::onCurrentTimerUpdates);
        disconnect(timer, &TaskTimer::onTimerEnds, this, &TaskManager::onCurrentTimerEnds);

        startTask(currentTaskId);

        int numTimers = timerList.size();
        if(numTimers > 1)
        {
            timerList.pop_front();
        }
    }
    else
    {
        //END
    }
}

void TaskManager::startTask(int id)
{
    currentTask = &taskList[currentTaskId];
    emit onTaskStarted(currentTask->getName(), currentTask->getDescription());

    TaskTimer* timer = new TaskTimer(taskList[id]);
    timerList.push_back(timer);

    //make the connection
    connect(timer, &TaskTimer::onTimerUpdates, this, &TaskManager::onCurrentTimerUpdates);
    connect(timer, &TaskTimer::onTimerEnds, this, &TaskManager::onCurrentTimerEnds);
    timer->startTimer();
}
