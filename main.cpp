#include <QApplication>

#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	app.setApplicationName("SensorBridge");
	app.setApplicationDisplayName("Sensor Bridge");
	app.setApplicationVersion(APP_VERSION);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();

}
