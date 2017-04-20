#include "smoothing.h"
#include "nonesmoothing.h"
#include "simplemovingaveragesmoothing.h"
#include "exponentialsmoothing.h"

Smoothing::Smoothing() {
	_maxSampleCount = 10;
	_smoothedValue = 0;
	_smoothingFactor = 1;
}

float Smoothing::lastValue() const {
	return _smoothedValue;
}

void Smoothing::addValue(float value) {

	// Update value buffer
	_samples.push_back(value);
	if (_samples.size() > _maxSampleCount) {
		_samples.pop_front();
	}

	// Calculate new smoothed value and emit
	_smoothedValue = calculateSmoothedValue();

}

float Smoothing::smoothingFactor() const {
	return _smoothingFactor;
}

void Smoothing::setSmoothingFactor(float smoothingFactor) {
	if (_smoothingFactor != smoothingFactor) {
		_smoothingFactor = smoothingFactor;
	}
}

Smoothing* Smoothing::getSmoothing(SmoothingType type) {
	switch (type) {
		case None:
			return new NoneSmoothing();
		case SimpleMovingAverage:
			return new SimpleMovingAverageSmoothing();
		case SingleExponential:
			return new ExponentialSmoothing();
		default:
			return 0;
	}
}
