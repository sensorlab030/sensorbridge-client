#include "sensorwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QDebug>
#include "sensor.h"
#include "math.h"

SensorWidget::SensorWidget(Sensor* sensor, QWidget *parent) : QWidget(parent) {
	_sensor = sensor;

	// Setup data series
	_dataSeries = new QLineSeries();

	for (int  i = 0; i < 100; i++) {
		_data.append(0);
	}

	QChart *chart = new QChart();
	chart->legend()->hide();
	chart->setBackgroundRoundness(0);
	chart->addSeries(_dataSeries);
	chart->createDefaultAxes();
	chart->axisX()->setRange(0, 100);
	chart->axisX()->hide();
	chart->axisY()->setRange(0, 1);
	chart->setTitle(sensor->name());

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(chartView);
	setLayout(layout);

	startTimer(100);
}


void SensorWidget::timerEvent(QTimerEvent*) {

//	float value = (float) rand() / (float) RAND_MAX;
	float value = _sensor->lastValue();

	// Update data
	_data.removeFirst();
	_data.append(value);

	// Update data series
	_dataSeries->clear();
	int index = 0;
	for (float v: _data) {
		_dataSeries->append(index++, v);
	}

}
