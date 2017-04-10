#include "sensor.h"
#include "math.h"

#include <QDebug>

Sensor::Sensor(QObject* parent) : QObject(parent) {
	startTimer(1000);
}

float Sensor::getLastValue() const {
	return lastValue;
}

void Sensor::pushValue(float value) {
	lastValue = value;
	emit valuePushed(lastValue);
}

void Sensor::timerEvent(QTimerEvent*) {
	float val = ((float) rand() / (RAND_MAX));
	qDebug() << "C++" << val;
	pushValue(val);
}

void Sensor::setName(const QString &name) {
	this->name =name;
}

QString Sensor::getName() const {
	return name;
}
