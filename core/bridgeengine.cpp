#include "bridgeengine.h"

#include <QThread>
#include <QCoreApplication>
#include <QDebug>

#include "sensoroutput.h"
#include "serialconnection.h"

BridgeEngine::BridgeEngine(QObject *parent) : QObject(parent) {

	// Move to separate thread
	QThread* newThread = new QThread();
	newThread->start();
	newThread->setPriority(QThread::TimeCriticalPriority);
	moveToThread(newThread);

	// Make sure this object is correctly destructed on application close
	connect(qApp, &QCoreApplication::aboutToQuit, this, &BridgeEngine::terminate);

}

QList<Sensor*> BridgeEngine::sensors() {
	QList<Sensor*> sensors;

	// Add sensors from sensor board
	if (_serialConnection) {
		sensors.append(_serialConnection->getSensors());
	}

	return sensors;
}

void BridgeEngine::initialize() {

	// Setup serial connection
	_serialConnection = new SerialConnection(this);

	// Emit signal
	emit initialized();

}

void BridgeEngine::startSerialConnection(const QString& port) {
	_serialConnection->openConnection(port);
}

void BridgeEngine::stopSerialConnection() {
	_serialConnection->closeConnection();
}

void BridgeEngine::startOutput() {
	if (_output) {
		_output->start();
		emit outputActiveChanged(true);
	}
}

void BridgeEngine::stopOutput() {
	if (_output) {
		_output->stop();
		emit outputActiveChanged(false);
	}
}

void BridgeEngine::configureOutput(const QVariantList& configuration) {

	// Clear current output
	if (_output) {
		delete _output;
		_output = 0;
	}

	// Setup new output
	_output = SensorOutput::createOutput(configuration);
	if (_output) {
		_output->setParent(this);
		for (Sensor* s: _serialConnection->getSensors()) {
			_output->addSensor(s);
		}
	}

	// Signal change
	emit outputChanged(_output);
}

void BridgeEngine::terminate() {

	// Stop processes
	stopSerialConnection();
	stopOutput();

	// Cleanup
	if (_serialConnection) {
		delete _serialConnection;
	}
	if (_output) {
		delete _output;
	}
}

