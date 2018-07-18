#include "stdafx.h"
#include "qtaddressbook.h"
#include "adddialog.h"

QtAddressBook::QtAddressBook(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void QtAddressBook::on_addButton_clicked()
{
	AddDialog dialog(this);

	if (dialog.exec()) {
		QString name = dialog.nameEdit->text();
		QString email = dialog.emailEdit->text();

		if (!name.isEmpty() && !email.isEmpty()) {
			QListWidgetItem *item = new QListWidgetItem(name, ui.addressList);
			item->setData(Qt::UserRole, email);
			ui.addressList->setCurrentItem(item);
		}
	}
}

void QtAddressBook::on_addressList_currentItemChanged()
{
	QListWidgetItem *curItem = ui.addressList->currentItem();

	if (curItem) {
		ui.nameLabel->setText("Name: " + curItem->text());
		ui.emailLabel->setText("Email: " + curItem->data(Qt::UserRole).toString());
	}
	else {
		ui.nameLabel->setText("<No item selected>");
		ui.emailLabel->clear();
	}
}

void QtAddressBook::on_deleteButton_clicked()
{
	QListWidgetItem *curItem = ui.addressList->currentItem();

	if (curItem) {
		int row = ui.addressList->row(curItem);
		ui.addressList->takeItem(row);
		delete curItem;

		if (ui.addressList->count() > 0)
			ui.addressList->setCurrentRow(0);
		else
			on_addressList_currentItemChanged();
	}
}
