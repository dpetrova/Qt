#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "dbmanager.h"

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
    DbManager& dbManager; //the widget(view) will communicate with the data(model) through it
};

#endif // LOGINWIDGET_H
