#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sensor.h"
#include "serialconnection.h"
#include "websocketoutput.h"
#include "sensoroutput.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	SerialConnection* connection = new SerialConnection(&app);
	connection->openConnection("COM6");

	WebSocketOutput* server = new WebSocketOutput(&app);
	for(Sensor* s: connection->getSensors()) {
		server->addSensor(s);
	}
	server->start(1000);

	// Setup QML engine
	QQmlApplicationEngine engine;
//	qmlRegisterType<Sensor>("com.cleverfranke.sensorbridge", 1, 0, "Sensor");

//	QQmlContext* rootContext = engine.rootContext();
//	rootContext->setContextProperty("_sensor1", &s1);
//	rootContext->setContextProperty("_sensor2", &s2);

	// Load main
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	return app.exec();

}
