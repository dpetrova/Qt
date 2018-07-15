#include "task.h"
#include "ui_task.h"

#include <QInputDialog>

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);

    setName(name);

    //connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(rename()));

    //connect the clicked signal to an anonymous inline function, a lambda
    //lambda avoids the declaration of a verbose slot
    //Qt5 accept lambda instead of a slot in a connect (both syntaxes can be used)
    connect(ui->removeButton, &QPushButton::clicked, [this](){
        emit removed(this);
    } );

    //lambda syntax:
    //[ capture-list ] ( params ) -> ret { body }
    //capture-list: This defines what variables will be visible inside the lambda scope
    //params: This is the function parameters type list that can be passed to the lambda scope
    //ret: the return type of the lambda function. Just like params, it can be omitted if the return type is void
    //body: code body where you have access to capture-list, and params, and which must return a variable with a type ret

    connect(ui->checkBox, &QCheckBox::toggled, this, &Task::checked);
}

void Task::setName(const QString &name)
{
    this->ui->checkBox->setText(name); //here in ui-> are all widgets that are made in task.ui
}

QString Task::getName() const
{
    return this->ui->checkBox->text();
}

bool Task::isCompleted() const
{
    return this->ui->checkBox->isChecked();
}

void Task::rename()
{
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Edit Task"), tr("Task Name"), QLineEdit::Normal, this->getName(), &ok);

    if(ok && !newName.isEmpty())
    {
        this->setName(newName);
    }
}

void Task::checked(bool checked)
{
    QFont font(ui->checkBox->font()); //create a copy font
    font.setStrikeOut(checked); //modify it (strike out the checkbox text according to the bool checked value)
    ui->checkBox->setFont(font); //assign it back
    emit statusChanged(this); //notifies MainWindow that the Task status has changed
}

Task::~Task()
{
    delete ui;
}
