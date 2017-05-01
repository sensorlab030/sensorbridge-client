#include "nonesmoothing.h"

NoneSmoothing::NoneSmoothing(): Smoothing() {}

Smoothing::SmoothingType NoneSmoothing::type() const {
	return None;
}

float NoneSmoothing::calculateSmoothedValue() {
	return _samples.last();
}
