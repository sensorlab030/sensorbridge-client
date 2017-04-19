#ifndef EXPONENTIALSMOOTHING_H
#define EXPONENTIALSMOOTHING_H

#include "smoothing.h"

class ExponentialSmoothing : public Smoothing {
	Q_OBJECT

public:
	explicit ExponentialSmoothing(QObject *parent = 0);

private:
	float calculateSmoothedValue();

};

#endif // EXPONENTIALSMOOTHING_H
