#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sensor.h"
#include "serialconnection.h"
#include "websocketserver.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	WebSocketServer* server = new WebSocketServer(&app);
	server->startServer(9001);

//	SerialConnection* connection = new SerialConnection(&app);
//	connection->openConnection("COM6");

//	// Prep models
//	Sensor s1 = new Sensor(&app);
//	s1.setName("Sensor Foo");

//	Sensor s2 = new Sensor(&app);
//	s2.setName("Sensor Bar");

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
