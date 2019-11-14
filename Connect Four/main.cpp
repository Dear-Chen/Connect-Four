#include "UI.h"
#include <QtWidgets/QApplication>
#include "log.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	initLog();
	UI w;
	w.show();
	return a.exec();
}
