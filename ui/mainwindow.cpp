#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

#include "serialconnection.h"
#include "sensoroutput.h"
#include "settingsdialog.h"
#include "sensorwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	// Setup serial connection
	_serialConnection = new SerialConnection(this);
	_sensors.append(_serialConnection->getSensors());

	QPushButton* btn = new QPushButton("Setup");
	connect(btn, &QPushButton::clicked, this, &MainWindow::openSettings);

	_startCaptureBtn = new QPushButton("Start capture");
	connect(_startCaptureBtn, SIGNAL(clicked(bool)), this, SLOT(startCapture()));

	_stopCaptureBtn = new QPushButton("Stop capture");
	_stopCaptureBtn->hide();
	connect(_stopCaptureBtn, SIGNAL(clicked(bool)), this, SLOT(stopCapture()));

	_outputDescriptionLbl = new QLabel();

	// Setup capture layout
	QHBoxLayout* captureLayout = new QHBoxLayout();
	captureLayout->addWidget(_outputDescriptionLbl);
	captureLayout->addStretch();
	captureLayout->addWidget(btn);
	captureLayout->addSpacing(40);
	captureLayout->addWidget(_startCaptureBtn);
	captureLayout->addWidget(_stopCaptureBtn);

	// Set central widget
	QVBoxLayout* centralLayout = new QVBoxLayout();
	centralLayout->addLayout(setupSensorsUI());
	centralLayout->addLayout(captureLayout, 0);
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);

	connect(this, SIGNAL(outputChanged(SensorOutput*)), this, SLOT(onOutputChanged()));
	onOutputChanged();
}

QHBoxLayout* MainWindow::setupSensorsUI() {

	QHBoxLayout* layout = new QHBoxLayout();
	layout->setMargin(0);
	layout->setContentsMargins(0, 0, 0,0);
	layout->setSpacing(0);

	for (Sensor* s: _sensors) {
		SensorWidget* widget = new SensorWidget(s);
		layout->addWidget(widget);
	}

	return layout;

}

void MainWindow::startCapture() {
	_output->start();
	_startCaptureBtn->hide();
	_stopCaptureBtn->show();
}

void MainWindow::stopCapture() {
	_output->stop();
	_startCaptureBtn->show();
	_stopCaptureBtn->hide();
}

void MainWindow::onOutputChanged() {
	_startCaptureBtn->setEnabled((_output != 0));
	_outputDescriptionLbl->setText((_output != 0) ? _output->description() : "No output configured");
}

void MainWindow::openSettings() {
	SettingsDialog dialog(this);

	if (dialog.exec() == QDialog::Accepted) {

		// Setup serial
		if (dialog.getSerialPort() != _serialConnection->portName()) {
			_serialConnection->closeConnection();
			_serialConnection->openConnection(dialog.getSerialPort());
		}

		// Setup output
		if (_output != 0) {
			delete _output;
			_output = 0;
		}

		_output = dialog.getSensorOutput();
		if (_output) {
			for(Sensor* s: _sensors) {
				_output->addSensor(s);
			}
		}
		emit outputChanged(_output);

	}

}
