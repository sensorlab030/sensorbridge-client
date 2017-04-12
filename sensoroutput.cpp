#include "sensoroutput.h"
#include "sensor.h"

#include <QDebug>

SensorOutput::SensorOutput(QObject* parent) : QObject(parent) {
	_timerId = 0;
	_interval = 100;	// Set default interval to 100ms
}

void SensorOutput::addSensor(Sensor* sensor) {
	if (!_sensors.contains(sensor)) {
		_sensors.append(sensor);
	}
}

void SensorOutput::removeSensor(Sensor* sensor) {
	_sensors.removeAll(sensor);
}

void SensorOutput::start() {
	stop();								// Stop capturing
	startCapture();						// Start capture on client (initialization)
	_timerId = startTimer(_interval);	// Start capture timer
}

void SensorOutput::start(int interval) {
	stop();					// Stop capturing
	setInterval(interval);	// Set interval
	start();				// Start capture
}

void SensorOutput::stop() {
	if (_timerId == 0) {
		return;
	}

	// Stop capture timer
	killTimer(_timerId);
	_timerId = 0;

	// Stop capture on implementation class (cleanup)
	stopCapture();

}

void SensorOutput::timerEvent(QTimerEvent*) {

	// Capture data from sensors
	QList<float> data;
	for (int i = 0; i < _sensors.count(); i++) {
		data.append(_sensors.at(i)->lastValue());
	}

	// Let implementation class handle the data
	handleCapture(data);

}

void SensorOutput::setInterval(int interval) {
	if (interval != _interval) {
		_interval = interval;
		emit intervalChanged(_interval);
	}
}

int SensorOutput::interval() const {
	return _interval;
}

