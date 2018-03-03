#include "taskmanager.h"

#include <QtWidgets>

namespace kTaskTimer
{
    TaskManager::TaskManager()
    {

    }

    void TaskManager::loadTaskList()
    {
//        QString fileName = QFileDialog::getOpenFileName(this,
//               tr("Open Task List"), "",
//               tr("Task List (*.tsk);;All Files (*)"));

//           if (fileName.isEmpty())
//           {
//               return;
//           }
//           else {

//               QFile file(fileName);

//               if (!file.open(QIODevice::ReadOnly)) {
//                   QMessageBox::information(this, tr("Unable to open file"),
//                       file.errorString());
//                   return;
//               }

//               QDataStream in(&file);
//               in.setVersion(QDataStream::Qt_4_5);
//               taskList.clear();   // clear existing tasks
//               in >> taskList;

//               if (taskList.isEmpty())
//               {
//                   QMessageBox::information(this, tr("No tasks in file"),
//                       tr("The file you are attempting to open contains no tasks."));
//               }
//               else
//               {

//               }
//           }
    }
}
