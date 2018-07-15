#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QInputDialog>

//As a best practice, try to always initialize member variables in the constructor (initialization lists)
// and respect the order of variable declarations.
//Your code will run faster and you will avoid unnecessary variable copies

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), //parent argument is used to call the superclass constructor QMainWindow
    ui(new Ui::MainWindow), //initialize the private member variable ui
    tasks() //initialize the private member variable tasks
{
    ui->setupUi(this); //call the setupUi() function to initialize all widgets used by the MainWindow.ui design file

    //message exchange mechanism through three concepts: signals, slots, and connections
    //signal is a message sent by an object
    //slot is a function that will be called when this signal is triggered
    //connect function specifies which signal is linked to which slot
    //connect(sender, &Sender::signalName, receiver, &Receiver::slotName);

    //first way:
    //connect(ui->addTaskButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
    //connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);

    //second way:
    connect(ui->addTaskButton, SIGNAL(clicked()), this, SLOT(addTask()));

    updateStatus();
}

void MainWindow::addTask()
{
    //if you want your application to have multiple language support,
    //wrap every user-visible string in your code inside a tr() function

    //QinputDialog::getText function is a static blocking function that displays the dialog
    bool ok;
    QString name = QInputDialog::getText(this, tr("Add Task"), tr("Task Name"), QLineEdit::Normal, tr("Untitled Task"), &ok);

    if(ok && !name.isEmpty())
    {
        Task* task = new Task(name);
        connect(task, &Task::removed, this, &MainWindow::removeTask);
        connect(task, &Task::statusChanged, this, &MainWindow::updateStatus);
        tasks.append(task);
        ui->taskLayout->addWidget(task);
        updateStatus();
    }
}

void MainWindow::removeTask(Task *task)
{
    tasks.removeOne(task); //task is first removed from the tasks vector
    ui->taskLayout->removeWidget(task); //then removed from tasksLayout; tasksLayout releases its ownership of task (task class's parent becomes centralWidget)
    task->setParent(0); //we want Qt to forget everything about task
    delete task; //then safely delete it
    updateStatus();
}

void MainWindow::updateStatus()
{
    int completed = 0;
    for(auto t : tasks) //lets us loop over a range-based container; auto->compiler deduces the variable type automatically based on the initializer
    {
        if(t->isCompleted())
        {
            completed++;
        }
    }

    int todo = tasks.size() - completed;
    ui->statusLabel->setText(QString("%1 todo / %2 completed").arg(todo).arg(completed)); //arguments are position-based only, no need to specify the type
}

MainWindow::~MainWindow()
{
    delete ui; //as we initialize a pointer in the constructor, it must be cleaned in the destructor
}
