#ifndef NONESMOOTHING_H
#define NONESMOOTHING_H

#include "smoothing.h"

class NoneSmoothing : public Smoothing {

public:
	NoneSmoothing();

	SmoothingType type() const;

private:
	float calculateSmoothedValue();

};

#endif // NONESMOOTHING_H
