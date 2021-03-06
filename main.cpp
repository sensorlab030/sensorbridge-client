#include <QApplication>

#include "core/bridgeengine.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {

	// Setup application
	QApplication app(argc, argv);
	app.setApplicationName("SensorBridge");
	app.setApplicationDisplayName("Sensor Bridge");
	app.setOrganizationName("CLEVER°FRANKE");
	app.setOrganizationDomain("com.cleverfranke");
	app.setApplicationVersion("1.1.1");

	// Construct engine (initialization is done by mainwindow)
	BridgeEngine engine;

	// Construct and show mainwindow
	MainWindow mainWindow(&engine);

	return app.exec();

}
