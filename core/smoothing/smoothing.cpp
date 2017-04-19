#include "smoothing.h"

Smoothing::Smoothing(QObject *parent) : QObject(parent) {
	_maxSampleCount = 10;
	_smoothedValue = 0;
	_smoothingFactor = 1;
}

float Smoothing::lastValue() const {
	return _smoothedValue;
}

void Smoothing::pushValue(float value) {

	// Update value buffer
	_samples.push_back(value);
	if (_samples.size() > _maxSampleCount) {
		_samples.pop_front();
	}

	// Calculate new smoothed value and emit
	_smoothedValue = calculateSmoothedValue();
	emit valueAdded(_smoothedValue);

}

float Smoothing::smoothingFactor() const {
	return _smoothingFactor;
}

void Smoothing::setSmoothingFactor(float smoothingFactor) {
	if (_smoothingFactor != smoothingFactor) {
		_smoothingFactor = smoothingFactor;
		emit smoothingFactorChanged(_smoothingFactor);
	}
}
