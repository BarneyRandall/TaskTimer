#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskloader.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QTimeEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    setWindowTitle(tr("Task Timer"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    //menu options
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    //buttons
    m_clearConnection = QPushButton::connect(ui->clearTaskButton, SIGNAL (released()), this, SLOT (handleClearTaskButton()));
    m_addTaskConnection = QPushButton::connect(ui->addTaskButton, SIGNAL (released()), this, SLOT (addCurrentTaskToList()));

    m_removeTaskConnection = QPushButton::connect(ui->removeTaskButton, SIGNAL (released()), this, SLOT (removeSelectedTask()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
           tr("Open Task List"), "",
           tr("Task List (*.tsk);;All Files (*)"));
    if(fileName.isEmpty())
    {
        return;
    }
    TaskLoader loader;
    taskList = loader.loadTasksFromFile(fileName);

    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        delete ui->listWidget->takeItem(i);
    }

    for(auto task : taskList)
    {
        QListWidget* listWidget = ui->listWidget;
        listWidget->addItem(task.getName() + " : " + task.getDescription() + " (" + task.getDuration().toString() + ")");
    }
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save Task List"), "",
         tr("Task List (*.tsk);;All Files (*)"));
    if(fileName.isEmpty())
    {
      return;
    }
    TaskLoader loader;
    loader.saveTasksToFile(fileName, taskList);
}

void MainWindow::handleClearTaskButton()
{
    ui->nameTextEdit->clear();
    ui->descriptionTextEdit->clear();
    ui->timeEdit->clear();
}

void MainWindow::addCurrentTaskToList()
{
    QString taskName = ui->nameTextEdit->toPlainText();
    if(taskName.length() == 0)
    {
        //TODO: error popup
        return;
    }

    QPlainTextEdit* descriptionTextEdit = ui->descriptionTextEdit;
    QString taskDescription = descriptionTextEdit->toPlainText();
    if(taskDescription.length() == 0)
    {
        //TODO:error
        return;
    }

    QTimeEdit* timeEdit = ui->timeEdit;
    QTime duration = timeEdit->time();

    QListWidget* listWidget = ui->listWidget;
    listWidget->addItem(taskName + " : " + taskDescription + " (" + duration.toString() + ")");

    int taskId = taskList.size();

    kTask newTask = kTask(taskName, taskDescription, duration, taskId);
    taskList.append(newTask);

    //clear the input boxes
    handleClearTaskButton();
}

void MainWindow::removeSelectedTask()
{
    for(auto listItem : ui->listWidget->selectedItems())
    {
        int rowId = ui->listWidget->row(listItem);
        delete ui->listWidget->takeItem(rowId);
        taskList.removeAt(rowId);
    }
}
