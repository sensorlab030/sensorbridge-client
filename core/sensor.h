#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "smoothing/smoothing.h"

/*!
 * Sensor
 * The representation of one single sensor value in the application. This is where
 * the collected data is pushed and from here distributed to the relevant listeners
 */
class Sensor : public QObject {
	Q_OBJECT

public:
	Sensor(QObject* parent = 0);

	void pushValue(float value);				//!< Push new value to the sensor
	float lastValue() const;					//!< Get the latest (smoothed) value
	float lastRawValue() const;					//!< Get the latest raw value

	void setName (const QString& name);			//!< Set the sensor name
	QString name() const;						//!< Get the sensor name

	void						setSmootingType(Smoothing::SmoothingType type);
	Smoothing::SmoothingType	smoothingType();

	void setSmoothingFactor(float smoothingFactor);
	float smoothingFactor() const;

signals:
	void lastValueChanged(float value);
	void lastRawValueChanged(float value);
//	void valueAdded(float value);
	void smoothingTypeChanged(Smoothing::SmoothingType type);
	void smoothingFactorChanged(float smoothingFactor);

private:
	float				_lastValue;				//!< The last value
	QString				_name;					//!< The sensor name
	Smoothing*			_smoothing;				//!< Smoother

};

#endif // SENSOR_H
