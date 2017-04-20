#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include <QLineSeries>
#include "../core/smoothing/smoothing.h"

class Sensor;
class QComboBox;
class QSlider;

using namespace QtCharts;

class SensorWidget : public QWidget {
	Q_OBJECT

public:
	explicit SensorWidget(Sensor* sensor, QWidget *parent = 0);

private slots:
	void onNewValue(float value);
	void updateDataSeries();

	void onSliderValueChanged(int value);
	void onSmoothingFactorChanged(float value);
	void onSmoothingSelectorChanged(int);
	void onSmoothingTypeChanged(Smoothing::SmoothingType type);

private:
	void timerEvent(QTimerEvent*);

	QComboBox*		_smoothingSelector;
	QSlider*		_smoothingSlider;
	QLineSeries*	_dataSeries;
	QVector<float>	_data;
	Sensor*			_sensor;

};

#endif // SENSORWIDGET_H
