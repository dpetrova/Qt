#ifndef TASK_H
#define TASK_H

#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
    explicit Task(const QString &name, QWidget *parent = 0);
    ~Task();    
    void setName(const QString &name);
    QString getName() const;
    bool isCompleted() const;

public slots:
    void rename();

private slots:
    void checked(bool checked);

//signal is simply a notification sent to the receiver (the connected slot); it implies that there is no function body
signals:
    void removed(Task* task);
    void statusChanged(Task* task);

private:
    Ui::Task *ui;
};

#endif // TASK_H
