#include <QApplication>

#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	app.setApplicationName("SensorBridge");
	app.setApplicationDisplayName("Sensor Bridge");
	app.setOrganizationName("CLEVER°FRANKE");
	app.setOrganizationDomain("com.cleverfranke");
	app.setApplicationVersion("0.1.0");

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();

}
