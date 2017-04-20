#ifndef SIMPLEMOVINGAVERAGESMOOTHING_H
#define SIMPLEMOVINGAVERAGESMOOTHING_H

#include "smoothing.h"

class SimpleMovingAverageSmoothing : public Smoothing {

public:
	explicit SimpleMovingAverageSmoothing();

	SmoothingType type() const;

private:
	float calculateSmoothedValue();

};

#endif // SIMPLEMOVINGAVERAGESMOOTHING_H
