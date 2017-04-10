#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor : public QObject {
	Q_OBJECT
	Q_PROPERTY(float lastValue READ getLastValue NOTIFY valuePushed)
	Q_PROPERTY(QString name READ getName)

public:
	Sensor( QObject* parent = 0);

	void pushValue(float value);
	float getLastValue() const;

	void setName (const QString& name);
	QString getName() const;

signals:
	void valuePushed(float newValue);

private:
	float lastValue;
	QString name;

};

#endif // SENSOR_H
