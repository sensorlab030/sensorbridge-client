#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include <QLineSeries>

class Sensor;

using namespace QtCharts;

class SensorWidget : public QWidget {
	Q_OBJECT

public:
	explicit SensorWidget(Sensor* sensor, QWidget *parent = 0);

private:
	void timerEvent(QTimerEvent*);

	Sensor*			_sensor;
	QLineSeries*	_dataSeries;
	QVector<float>	_data;

};

#endif // SENSORWIDGET_H
