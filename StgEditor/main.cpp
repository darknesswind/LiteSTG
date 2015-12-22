#include "mainwindow.h"
#include <QApplication>
#include "editordata.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	EditorData::instance()->load();

	MainWindow w;
	w.show();

	int res = a.exec();

	EditorData::instance()->save();
	return res;
}
