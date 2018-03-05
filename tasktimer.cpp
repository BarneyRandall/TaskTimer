#include "tasktimer.h"

#include <QDateTime>

TaskTimer::TaskTimer(kTask task)
    : task(task)
{
    timer = new QTimer(this);

    //connections
    timerConnection = connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTick()));
}

void TaskTimer::startTimer()
{
    startTime = QTime::currentTime();

    QTime duration = task.getDuration();
    endTime = QTime(startTime.hour() + duration.hour(), startTime.minute() + duration.minute(),startTime.second() + duration.second());
    timer->start(10);
}

void TaskTimer::stopTimer()
{
    timer->stop();
}

void TaskTimer::pauseTimer()
{
    //TODO:
}

void TaskTimer::onTimerTick()
{
    QTime now = QTime::currentTime();
    qint64 secondsRemaining = now.secsTo(endTime);
    if(secondsRemaining <= 0)
    {
        emit onTimerEnds();
    }
    else
    {
        emit onTimerUpdates(secondsRemaining);
        timer->start(10);
    }
}
