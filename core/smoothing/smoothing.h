#ifndef SMOOTHING_H
#define SMOOTHING_H

#include <QObject>
#include <QVector>

class Smoothing : public QObject {
	Q_OBJECT

public:
	explicit Smoothing(QObject *parent = 0);

	float lastValue() const;			//!< Get last calculated value
	float smoothingFactor() const;		//!< Get smoothing factor [0.0, 1.0]

signals:
	void valueAdded(float value);
	void smoothingFactorChanged(float smoothingFacor);

public slots:
	void pushValue(float value);					//!< Add new value
	void setSmoothingFactor(float smoothingFactor);	//!< Set smoothing factor [0.0, 1.0]

protected:
	virtual float calculateSmoothedValue() = 0;

	QVector<float>		_samples;					//!< Value buffer

private:
	int					_maxSampleCount;			//!< Max allowed number of values in _values
	float				_smoothingFactor;			//!< How much should be smoothed [0.0, 1.0]
	float				_smoothedValue;				//!< Last calculated smoothed value

};

#endif // SMOOTHING_H
