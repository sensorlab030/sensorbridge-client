#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

/*!
 * Sensor
 * The representation of one single sensor value in the application. This is where
 * the collected data is pushed and from here distributed to the relevant listeners
 */
class Sensor : public QObject {
	Q_OBJECT

public:
	Sensor( QObject* parent = 0);

	void pushValue(float value);				//!< Push new value to the sensor
	float lastValue() const;					//!< Get the latest value

	void setName (const QString& name);			//!< Set the sensor name
	QString name() const;						//!< Get the sensor name

signals:
	void	valueAdded(float value);

private:
	float				_lastValue;				//!< The last value
	QString				_name;					//!< The sensor name

};

#endif // SENSOR_H
