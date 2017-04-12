#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "sensoroutput.h"
#include "outputsettingsdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

	QPushButton* btn = new QPushButton("Setup");
	connect(btn, &QPushButton::clicked, this, &MainWindow::setupOutput);

	_startCaptureBtn = new QPushButton("Start capture");
	connect(_startCaptureBtn, SIGNAL(clicked(bool)), this, SLOT(startCapture()));

	_stopCaptureBtn = new QPushButton("Stop capture");
	_stopCaptureBtn->hide();
	connect(_stopCaptureBtn, SIGNAL(clicked(bool)), this, SLOT(stopCapture()));

	// Setup capture layout
	QHBoxLayout* captureLayout = new QHBoxLayout();
	captureLayout->addWidget(new QLabel("Output setup: websocket@9001 @100ms"));
	captureLayout->addStretch();
	captureLayout->addWidget(btn);
	captureLayout->addSpacing(40);
	captureLayout->addWidget(_startCaptureBtn);
	captureLayout->addWidget(_stopCaptureBtn);

	// Set central widget
	QVBoxLayout* centralLayout = new QVBoxLayout();
	centralLayout->addStretch();
	centralLayout->addLayout(captureLayout);
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);

	connect(this, SIGNAL(outputChanged(SensorOutput*)), this, SLOT(onOutputChanged()));
	onOutputChanged();
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
}

void MainWindow::setupOutput() {
	OutputSettingsDialog dialog(this);

	if (dialog.exec() == QDialog::Accepted) {

		if (_output != 0) {
			delete _output;
			_output = 0;
		}

		_output = dialog.getSensorOutput();
		emit outputChanged(_output);

	}
}
