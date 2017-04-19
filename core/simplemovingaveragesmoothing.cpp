#include "simplemovingaveragesmoothing.h"

SimpleMovingAverageSmoothing::SimpleMovingAverageSmoothing(QObject *parent) : QObject(parent) {
	_sampleCount = 10;
	_smoothedValue = 0;
}

float SimpleMovingAverageSmoothing::lastValue() const {
	return _smoothedValue;
}

void SimpleMovingAverageSmoothing::pushValue(float value) {

	// Update value buffer
	_values.push_back(value);
	if (_values.size() > _sampleCount) {
		_values.pop_front();
	}

	// Calculate new smoothed value and emit
	_smoothedValue = calculateSmoothedValue(_values);
	emit valueAdded(_smoothedValue);
}

float SimpleMovingAverageSmoothing::calculateSmoothedValue(const QVector<float>& buffer) {
	if (buffer.size() == 0) {
		return 0;
	}

	// Calculate sum
	float sum = 0;
	for (float v: buffer) {
		sum += v;
	}

	// Return simple average
	return sum / (float) buffer.size();

}
