#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <QVector>

class Smoothing {

public:
	explicit Smoothing();

	enum SmoothingType {
		None,
		SimpleMovingAverage,
		SingleExponential
	};

	virtual SmoothingType type() const = 0;
	float lastValue() const;						//!< Get last calculated value
	float smoothingFactor() const;					//!< Get smoothing factor [0.0, 1.0]
	void addValue(float value);						//!< Add new value
	void setSmoothingFactor(float smoothingFactor);	//!< Set smoothing factor [0.0, 1.0]

	static Smoothing* getSmoothing(SmoothingType type);

protected:
	virtual float calculateSmoothedValue() = 0;

	QVector<float>		_samples;					//!< Value buffer

private:
	int					_maxSampleCount;			//!< Max allowed number of values in _values
	float				_smoothingFactor;			//!< How much should be smoothed [0.0, 1.0]
	float				_smoothedValue;				//!< Last calculated smoothed value

};

#endif // SMOOTHING_H
