#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QObject>
#include <QList>

#include "tasktimer.h"

class TaskManager : public QObject
{
    Q_OBJECT
public:
    TaskManager(QList<kTask> taskList);

    void startTasks();
    void stopTasks();
    void pauseTasks();

signals:
    void onTaskStarted(QString name, QString description);
    void onTaskTimeChanged(QString timeString);

private slots:
    void onCurrentTimerUpdates(qint64 secondsRemaining);
    void onCurrentTimerEnds();

private:
    void startTask(int id);

private:
    kTask* currentTask;
    int currentTaskId;

    QList<kTask> taskList;
    QList<TaskTimer*> timerList;
};

#endif // TIMERMANAGER_H
