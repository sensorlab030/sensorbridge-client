#include <QApplication>

#include "ui/mainwindow.h"
#include "sensor.h"
#include "serialconnection.h"
#include "websocketoutput.h"
#include "sensoroutput.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	app.setApplicationName("SensorBridge");
	app.setApplicationDisplayName("Sensor Bridge");
	app.setApplicationVersion(APP_VERSION);

//	SerialConnection* connection = new SerialConnection(&app);
//	connection->openConnection("COM6");

//	WebSocketOutput* server = new WebSocketOutput(&app);
//	for(Sensor* s: connection->getSensors()) {
//		server->addSensor(s);
//	}
//	server->start(1000);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();

}
