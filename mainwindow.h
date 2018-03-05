#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QList>
#include <QThread>

#include "taskmanager.h"

namespace Ui {
class MainWindow;
}

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //File menu actions
    void open();
    void save();

    //Task list setup
    void handleClearTaskButton();
    void addCurrentTaskToList();
    void removeSelectedTask();

    //Timer tab
    void handleTimerButton();

    void onNewTaskStarts(QString name, QString desc);
    void onCurrentTimerUpdates(QString timeString);
    void onCurrentTimerEnds();

private:
    void createActions();
    void createMenus();

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;

    QLabel *infoLabel;

    QList<kTask> taskList;

    //task setup button connections
    QMetaObject::Connection clearConnection;
    QMetaObject::Connection addTaskConnection;
    QMetaObject::Connection removeTaskConnection;

    //Timer buton connection
    QMetaObject::Connection timerButtonConnection;
    QMetaObject::Connection timerUpdateConnection;
    QMetaObject::Connection timerDetailsConnection;

    //Timer
    TaskManager* taskManager;
    bool timerRunning;

};

#endif // MAINWINDOW_H
