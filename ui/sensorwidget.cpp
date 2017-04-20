#include "sensorwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QChart>
#include <QChartView>
#include <QDebug>

#include "../core/sensor.h"

SensorWidget::SensorWidget(Sensor* sensor, QWidget *parent) : QWidget(parent) {
	_sensor = sensor;
	connect(_sensor, &Sensor::lastValueChanged, this, &SensorWidget::onNewValue, Qt::QueuedConnection);

	// Setup data series
	_dataSeries = new QLineSeries();
	for (int  i = 0; i < 150; i++) {
		_data.append(0);
	}

	// Smoothing selector
	_smoothingSelector = new QComboBox();
	_smoothingSelector->addItem("None", Smoothing::None);
	_smoothingSelector->addItem("SMA", Smoothing::SimpleMovingAverage);
	_smoothingSelector->addItem("EXP", Smoothing::SingleExponential);
	connect(_smoothingSelector, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SensorWidget::onSmoothingSelectorChanged);
	connect(_sensor, &Sensor::smoothingTypeChanged, this, &SensorWidget::onSmoothingTypeChanged);
	onSmoothingTypeChanged(_sensor->smoothingType());

	// Smoothing slider
	_smoothingSlider = new QSlider(Qt::Horizontal);
	_smoothingSlider->setRange(0, 1000);
	onSmoothingFactorChanged(_sensor->smoothingFactor());
	connect(_sensor, &Sensor::smoothingFactorChanged, this, &SensorWidget::onSmoothingFactorChanged);

	QChart *chart = new QChart();
	chart->legend()->hide();
	chart->setBackgroundRoundness(0);
	chart->addSeries(_dataSeries);
	chart->createDefaultAxes();
	chart->axisX()->setRange(0, 151);
	chart->setTheme(QChart::ChartThemeDark);
	chart->axisX()->hide();
	chart->axisY()->setRange(0, 1);
	chart->setTitle(sensor->name());

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QHBoxLayout* smoothingLayout = new QHBoxLayout();
	smoothingLayout->addWidget(_smoothingSelector);
	smoothingLayout->addSpacing(10);
	smoothingLayout->addWidget(_smoothingSlider);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(chartView);
	layout->addLayout(smoothingLayout);
	setLayout(layout);

	startTimer(100);

}

void SensorWidget::onNewValue(float value) {
	_data.removeFirst();
	_data.append(value);
}

void SensorWidget::updateDataSeries() {
	// Update data series
	_dataSeries->clear();
	int index = 0;
	for (float v: _data) {
		_dataSeries->append(index++, v);
	}
}

void SensorWidget::timerEvent(QTimerEvent*) {
	updateDataSeries();
}

void SensorWidget::onSliderValueChanged(int value) {
	float floatVal = (float) value / (float) _smoothingSlider->maximum();
	_sensor->setSmoothingFactor(floatVal);
}

void SensorWidget::onSmoothingFactorChanged(float value) {
	int intVal = round(value * (float) _smoothingSlider->maximum());
	_smoothingSlider->setValue(intVal);
}

void SensorWidget::onSmoothingSelectorChanged(int) {
	Smoothing::SmoothingType type = (Smoothing::SmoothingType ) _smoothingSelector->currentData().toInt();
	_sensor->setSmootingType(type);
}

void SensorWidget::onSmoothingTypeChanged(Smoothing::SmoothingType type) {
	int index = _smoothingSelector->findData(type);
	if (index != -1) {
		_smoothingSelector->setCurrentIndex(index);
	}
}
