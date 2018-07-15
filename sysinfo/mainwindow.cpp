#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "sysinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCpuWidget(this) //initialize mCpuWidget
{
    ui->setupUi(this);
    SysInfo::instance().init();
    ui->centralWidget->layout()->addWidget(&mCpuWidget); //add mCpuWidget to centralWidget layout
}

MainWindow::~MainWindow()
{
    delete ui;
}
