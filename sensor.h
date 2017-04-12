#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor : public QObject {
	Q_OBJECT

public:
	Sensor( QObject* parent = 0);

	void pushValue(float value);
	float lastValue() const;

	void setName (const QString& name);
	QString name() const;

private:
	float				_lastValue;
	QString				_name;

};

#endif // SENSOR_H
