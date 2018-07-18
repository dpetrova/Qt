#include "stdafx.h"
#include "qtaddressbook.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtAddressBook w;
	w.show();
	return a.exec();
}
