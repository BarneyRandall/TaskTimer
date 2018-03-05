#ifndef TASKTIMER_H
#define TASKTIMER_H

#include <QTimer>
#include <QObject>

#include <ktask.h>

class TaskTimer : public QObject
{
    Q_OBJECT
public:
    TaskTimer(kTask task);

    void startTimer();
    void stopTimer();
    void pauseTimer();

signals:
    void onTimerUpdates(qint64 secondsRemaining);
    void onTimerEnds();

private:
    void setupTimer(QTime& time);

private slots:
    void onTimerTick();

private:
    kTask task;

    QTimer* timer;
    QTime startTime;
    QTime endTime;

    QMetaObject::Connection timerConnection;
};

#endif // TASKTIMER_H
