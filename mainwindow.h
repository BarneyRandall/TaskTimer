#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QList>

#include "ktask.h"

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

protected:

private slots:
    void open();
    void save();

    void handleClearTaskButton();
    void addCurrentTaskToList();

    void removeSelectedTask();

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

    QMetaObject::Connection m_clearConnection;
    QMetaObject::Connection m_addTaskConnection;
    QMetaObject::Connection m_removeTaskConnection;

};

#endif // MAINWINDOW_H
