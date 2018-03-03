#include "taskloader.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <assert.h>

namespace
{
    const int kNumObjectsPerLine = 6;
    const QString kSeparator = ",";
}

TaskLoader::TaskLoader()
{

}

QList<kTask> TaskLoader::loadTasksFromFile(const QString &filename)
{
    QList<kTask> tasks;

    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          kTask task;
          if(loadTask(line, task))
          {
              tasks.push_back(task);
          }
          else
          {
              assert(false && "Error reading task, check format and find a better way of loading!");
          }
       }
       inputFile.close();
    }
    else
    {
        //QMessageBox::information(this, tr("Unable to open file"),inputFile.errorString());
    }

    return tasks;
}

void TaskLoader::saveTasksToFile(const QString &filename, QList<kTask>& taskList)
{
    //TODO: handle overwriting files!
    QFile outputFile(filename);
    if(outputFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&outputFile);
        for(auto& task : taskList)
        {
            QString durationString = QString::number(task.getHours())
                    + kSeparator
                    + QString::number(task.getMinutes())
                    + kSeparator
                    + QString::number(task.getSeconds());

            QString taskIdString = QString::number(task.getId());

            QString taskData = task.getName()
                    + kSeparator
                    + task.getDescription()
                    + kSeparator
                    + durationString
                    + kSeparator
                    + taskIdString;

            out.operator <<(taskData + "\n");
        }

        outputFile.close();
    }
    else
    {
        //QMessageBox::information(this, tr("Unable to open file"),outputFile.errorString());
    }
}

bool TaskLoader::loadTask(QString &taskData, kTask& task)
{
    QStringList splitData = taskData.split(kSeparator);
    if(splitData.length() != kNumObjectsPerLine)
    {
        return false;
    }

    QString taskName = splitData[0];
    QString taskDesc = splitData[1];

    int hour = splitData[2].toInt();
    int minute = splitData[3].toInt();
    int second = splitData[4].toInt();

    QTime duration = QTime(hour, minute, second);

    int taskId = splitData[5].toInt();

    task = kTask(taskName, taskDesc, duration, taskId);

    return true;
}
