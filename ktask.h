#ifndef KTASK_H
#define KTASK_H

#include <QString>
#include <QTime>

class kTask
{
public:
    kTask();
    kTask(QString name, QString desc, QTime duration, int taskId);

    QString getName() const { return taskName; }
    QString getDescription() const { return taskDescription; }
    QTime getDuration() const { return taskDuration; }
    int getHours() const { return taskDuration.hour(); }
    int getMinutes() const { return taskDuration.minute(); }
    int getSeconds() const { return taskDuration.second(); }
    int getId() const { return taskId; }
private:
    QString taskName;
    QString taskDescription;

    QTime taskDuration;

    int taskId;
};

#endif // KTASK_H
