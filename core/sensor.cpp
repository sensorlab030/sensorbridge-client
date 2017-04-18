#include "sensor.h"
#include "math.h"

#include <QDebug>

Sensor::Sensor(QObject* parent) : QObject(parent) {
	_lastValue = 0;
}

float Sensor::lastValue() const {
	return _lastValue;
}

void Sensor::pushValue(float value) {
	_lastValue = value;
	emit valueAdded(_lastValue);
}

void Sensor::setName(const QString &name) {
	this->_name =name;
}

QString Sensor::name() const {
	return _name;
}
