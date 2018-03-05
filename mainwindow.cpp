#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskloader.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QTimeEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    taskManager(nullptr),
    timerRunning(false)
{
    ui->setupUi(this);

    createActions();
    createMenus();

    setWindowTitle(tr("Task Timer"));

    //TODo: make thi load the last used task list instead
    TaskLoader loader;
    taskList = loader.loadTasksFromFile("morning_tasks.tsk");
    for(auto task : taskList)
    {
        QListWidget* listWidget = ui->listWidget;
        listWidget->addItem(task.getName() + " : " + task.getDescription() + " (" + task.getDuration().toString() + ")");
    }
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

    //Task setup butons
    clearConnection = QPushButton::connect(ui->clearTaskButton, SIGNAL (released()), this, SLOT (handleClearTaskButton()));
    addTaskConnection = QPushButton::connect(ui->addTaskButton, SIGNAL (released()), this, SLOT (addCurrentTaskToList()));
    removeTaskConnection = QPushButton::connect(ui->removeTaskButton, SIGNAL (released()), this, SLOT (removeSelectedTask()));

    //Timer button
    timerButtonConnection = QPushButton::connect(ui->startTasksButton, SIGNAL (released()), this, SLOT (handleTimerButton()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
}

#pragma mark - menu actions

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

#pragma mark - button actions

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

void MainWindow::handleTimerButton()
{
    if(taskManager == nullptr)
    {
        taskManager = new TaskManager(taskList);

        timerUpdateConnection = connect(taskManager, &TaskManager::onTaskStarted, this, &MainWindow::onNewTaskStarts);
        timerDetailsConnection = connect(taskManager, &TaskManager::onTaskTimeChanged, this, &MainWindow::onCurrentTimerUpdates);
    }

    if(timerRunning)
    {
        taskManager->startTasks();
        delete taskManager;
        taskManager = nullptr;
        ui->startTasksButton->setText("Start");
    }
    else
    {
       taskManager->startTasks();
       ui->startTasksButton->setText("Stop");
    }

    timerRunning = !timerRunning;
}

void MainWindow::onCurrentTimerUpdates(QString timeString)
{
    ui->timerLabel->setText(timeString);
}

void MainWindow::onCurrentTimerEnds()
{

}

void MainWindow::onNewTaskStarts(QString name, QString desc)
{
    ui->taskNameLabel->setText(name);
    ui->taskDescLabel->setText(desc);
}
