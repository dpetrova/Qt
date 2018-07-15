#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "task.h"
#include <QMainWindow>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT //This macro allows the class to define its own signals/slots and more globally Qt's meta-object system

public:
    explicit MainWindow(QWidget *parent = 0); //constructor that takes a parameter parent, which is a QWidget (UI component) pointer that is null by default.
    ~MainWindow(); //destructor
    void updateStatus();

//custom slot
public slots:
    void addTask();
    void removeTask(Task* task);

private:
    Ui::MainWindow *ui; //declare a pointer, ui member variable will allow you to interact with your UI components (QLabel, QPushButton, and so on)
    QVector<Task*> tasks; //QVector is the Qt container class providing a dynamic array (equivalent of std::vector)
};

#endif // MAINWINDOW_H
