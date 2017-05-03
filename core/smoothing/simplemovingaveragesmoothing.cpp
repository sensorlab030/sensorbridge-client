#include "simplemovingaveragesmoothing.h"

SimpleMovingAverageSmoothing::SimpleMovingAverageSmoothing() : Smoothing() {}

Smoothing::SmoothingType SimpleMovingAverageSmoothing::type() const {
	return SimpleMovingAverage;
}

float SimpleMovingAverageSmoothing::calculateSmoothedValue() {

	// Get starting index of value buffer (higher smoothing value
	// results in a bigger used buffer, e.g. more history being
	// used)
	int startIndex = (1 - smoothingFactor()) * _samples.count();
	if (startIndex >= _samples.count() -2) {
		startIndex = _samples.count() -2;
	}

	// Get sum of selected set
	float sum = 0;
	for (int i = startIndex; i < _samples.count(); i++) {
		sum += _samples.at(i);
	}

	// Return simple average
	if (sum == 0) {
		return 0;
	} else {
		return sum / (float) (_samples.size() - startIndex);
	}

}
