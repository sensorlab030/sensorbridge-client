#ifndef SIMPLEMOVINGAVERAGESMOOTHING_H
#define SIMPLEMOVINGAVERAGESMOOTHING_H

#include "smoothing.h"

class SimpleMovingAverageSmoothing : public Smoothing {
	Q_OBJECT

public:
	explicit SimpleMovingAverageSmoothing(QObject* parent = 0);

private:
	float calculateSmoothedValue();

};

#endif // SIMPLEMOVINGAVERAGESMOOTHING_H
