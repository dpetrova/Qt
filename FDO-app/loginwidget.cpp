#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    dbManager(DbManager::instance())
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
