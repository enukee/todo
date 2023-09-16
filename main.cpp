#include <QApplication>
#include "mainwindow.h"

#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif

//опа

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWindow mainwindow;
	mainwindow.show();
	return app.exec();
}
