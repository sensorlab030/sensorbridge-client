#include "sensor.h"
#include "math.h"

#include <QDebug>

Sensor::Sensor(QObject* parent) : QObject(parent) {
	_lastValue = 0;
	_isConnected = false;
	_smoothing = Smoothing::getSmoothing(Smoothing::None);
	_smoothing->setSmoothingFactor(0);
}

float Sensor::lastValue() const {
	return _smoothing->lastValue();
}

float Sensor::lastRawValue() const {
	return _lastValue;
}

void Sensor::pushValue(float value) {

	// Add raw value
	_lastValue = value;
	_smoothing->addValue(value);

	emit lastValueChanged(_smoothing->lastValue());
	emit lastRawValueChanged(_lastValue);

}

void Sensor::setIsConnected(bool isConnected) {
	if (_isConnected != isConnected) {
		_isConnected = isConnected;
		emit isConnectedChanged(_isConnected);
	}
}

bool Sensor::isConnected() const {
	return _isConnected;
}

void Sensor::setName(const QString &name) {
	this->_name =name;
}

QString Sensor::name() const {
	return _name;
}

void Sensor::setSmootingType(Smoothing::SmoothingType type) {
	if (_smoothing->type() != type) {

		// Fetch current smoothing factor
		float currentSmoothingFactor = smoothingFactor();

		// Replace smoothing
		delete _smoothing;
		_smoothing = Smoothing::getSmoothing(type);
		_smoothing->setSmoothingFactor(currentSmoothingFactor);

		// Emit change
		emit smoothingTypeChanged(type);
	}
}

Smoothing::SmoothingType Sensor::smoothingType() {
	return _smoothing->type();
}

void Sensor::setSmoothingFactor(float smoothingFactor) {
	if (_smoothing->smoothingFactor() != smoothingFactor) {
		_smoothing->setSmoothingFactor(smoothingFactor);
		emit smoothingFactorChanged(smoothingFactor);
	}
}

float Sensor::smoothingFactor() const {
	return _smoothing->smoothingFactor();
}
