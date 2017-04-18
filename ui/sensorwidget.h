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

private slots:
	void onNewValue(float value);
	void updateDataSeries();


private:
	void timerEvent(QTimerEvent*);

	QLineSeries*	_dataSeries;
	QVector<float>	_data;

};

#endif // SENSORWIDGET_H
