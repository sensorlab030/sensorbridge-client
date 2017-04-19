#include "simplemovingaveragesmoothing.h"

SimpleMovingAverageSmoothing::SimpleMovingAverageSmoothing(QObject *parent) : Smoothing(parent) {}

float SimpleMovingAverageSmoothing::calculateSmoothedValue() {

	// Get starting index of value buffer (higher smoothing value
	// results in a bigger used buffer, e.g. more history being
	// used)
	int startIndex = (1 - smoothingFactor()) * _samples.count();

	// Get sum of selected set
	float sum = 0;
	for (int i = startIndex; i < _samples.count(); i++) {
		sum += _samples.at(i);
	}

	// Return simple average
	return sum / (float) (_samples.size() - startIndex);

}
