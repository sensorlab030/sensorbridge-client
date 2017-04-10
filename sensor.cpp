#include "sensor.h"
#include "math.h"

#include <QDebug>

Sensor::Sensor(QObject* parent) : QObject(parent) {}

float Sensor::getLastValue() const {
	return lastValue;
}

void Sensor::pushValue(float value) {
	lastValue = value;
	emit valuePushed(lastValue);
}

void Sensor::setName(const QString &name) {
	this->name =name;
}

QString Sensor::getName() const {
	return name;
}
