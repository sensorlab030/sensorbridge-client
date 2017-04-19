#include "exponentialsmoothing.h"

ExponentialSmoothing::ExponentialSmoothing(QObject *parent) : Smoothing(parent) {}

float ExponentialSmoothing::calculateSmoothedValue() {
	float alpha = 1.0 - smoothingFactor();

	// Calculate result using single exponential smooting
	// @see https://grisha.org/blog/2016/01/29/triple-exponential-smoothing-forecasting/
	float result = _samples.first();
	for (int i = 1; i < _samples.length(); i++) {
		result = alpha * _samples[i] + (1-alpha) * result;
	}

	return result;
}

