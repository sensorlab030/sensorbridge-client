#ifndef EXPONENTIALSMOOTHING_H
#define EXPONENTIALSMOOTHING_H

#include "smoothing.h"

class ExponentialSmoothing : public Smoothing {

public:
	explicit ExponentialSmoothing();

	SmoothingType type() const;

private:
	float calculateSmoothedValue();

};

#endif // EXPONENTIALSMOOTHING_H
