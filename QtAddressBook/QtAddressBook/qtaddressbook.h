#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtaddressbook.h"

class QtAddressBook : public QWidget
{
	Q_OBJECT

public:
	QtAddressBook(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtAddressBookClass ui;

private slots:
	void on_addButton_clicked();
	void on_addressList_currentItemChanged();
	void on_deleteButton_clicked();
};
