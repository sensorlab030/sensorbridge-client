#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QDebug>
#include <QSettings>
#include <QSerialPortInfo>

#include "../core/bridgeengine.h"
#include "../core/sensoroutput.h"
#include "settingsdialog.h"
#include "sensorwidget.h"

MainWindow::MainWindow(BridgeEngine* engine, QWidget *parent) : QMainWindow(parent) {

	// Connect engine to interface
	_engine = engine;
	connect(_engine, &BridgeEngine::initialized, this, &MainWindow::initializeInterface, Qt::QueuedConnection);
	connect(_engine, &BridgeEngine::outputChanged, this, &MainWindow::onOutputChanged, Qt::QueuedConnection);
	connect(_engine, &BridgeEngine::outputActiveChanged, this, &MainWindow::onOutputActiveChanged, Qt::QueuedConnection);

	// Call for engine initialization
	QMetaObject::invokeMethod(engine, "initialize", Qt::QueuedConnection);

}

void MainWindow::initializeInterface() {

	// Setup serial port selector
	_serialPortSelector = new QComboBox();
	_serialPortSelector->setMaximumWidth(150);
	_serialPortSelector->addItem("None", "None");
	for (QSerialPortInfo portInfo: QSerialPortInfo::availablePorts()) {
		QString displayName = QString("%1 (%2)").arg(portInfo.portName()).arg(portInfo.description());
		_serialPortSelector->addItem(displayName, portInfo.portName());
	}
	connect(_serialPortSelector, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::onSerialPortSelectorChanged);

	// Select previously used serial port (if it is available)
	int previousSerialIndex = _serialPortSelector->findData(QSettings().value("serial", "None"));
	if (previousSerialIndex != -1) {
		_serialPortSelector->setCurrentIndex(previousSerialIndex);
	}

	// Setup capture elements
	_outputDescriptionLbl = new QLabel("No output configured");

	_setupBbtn = new QPushButton("Setup");
	connect(_setupBbtn, &QPushButton::clicked, this, &MainWindow::openSettings);

	_startCaptureBtn = new QPushButton("Start capture");
	_startCaptureBtn->setEnabled(false);
	connect(_startCaptureBtn, &QPushButton::clicked, _engine, &BridgeEngine::startOutput);

	_stopCaptureBtn = new QPushButton("Stop capture");
	_stopCaptureBtn->hide();
	connect(_stopCaptureBtn, &QPushButton::clicked, _engine, &BridgeEngine::stopOutput);

	// Setup sensor layout
	QGridLayout* sensorLayout = new QGridLayout();
	sensorLayout->setMargin(0);
	sensorLayout->setContentsMargins(0, 0, 0,0);
	sensorLayout->setSpacing(0);

	int index = 0;
	for (Sensor* s: _engine->sensors()) {
		SensorWidget* widget = new SensorWidget(s);
		sensorLayout->addWidget(widget, index / 3, index % 3);
		index++;
	}

	// Setup bottom layout
	QHBoxLayout* captureLayout = new QHBoxLayout();
	captureLayout->addWidget(new QLabel("Serial Port"));
	captureLayout->addWidget(_serialPortSelector);
	captureLayout->addStretch();
	captureLayout->addSpacing(40);
	captureLayout->addWidget(new QLabel("Output:"));
	captureLayout->addWidget(_outputDescriptionLbl);
	captureLayout->addWidget(_setupBbtn);
	captureLayout->addSpacing(10);
	captureLayout->addWidget(_startCaptureBtn);
	captureLayout->addWidget(_stopCaptureBtn);

	// Set central widget
	QVBoxLayout* centralLayout = new QVBoxLayout();
	centralLayout->addLayout(sensorLayout);
	centralLayout->addLayout(captureLayout, 0);
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);

	// Show window when UI is initialized
	show();

}

void MainWindow::onSerialPortSelectorChanged() {
	QString selectedData = _serialPortSelector->currentData().toString();
	if (selectedData == "None") {
		QMetaObject::invokeMethod(_engine, "stopSerialConnection", Qt::QueuedConnection);
	} else {
		QMetaObject::invokeMethod(_engine, "startSerialConnection", Qt::QueuedConnection, Q_ARG(QString, selectedData));
	}
	QSettings().setValue("serial", selectedData);

}

void MainWindow::onOutputActiveChanged(bool active) {
	_startCaptureBtn->setVisible(!active);
	_stopCaptureBtn->setVisible(active);
	_setupBbtn->setEnabled(!active);
}

void MainWindow::onOutputChanged(SensorOutput* output) {
	_startCaptureBtn->setEnabled(output != 0);

	QString outputDescription = (output != 0) ? output->description() : "No output configured";
	_outputDescriptionLbl->setText(outputDescription);
}

void MainWindow::openSettings() {
	SettingsDialog dialog(this);

	if (dialog.exec() == QDialog::Accepted) {

		// Send output configuration to engine
		QVariantList outputConfiguration (dialog.outputConfiguration());
		QMetaObject::invokeMethod(_engine, "configureOutput", Qt::QueuedConnection, Q_ARG(QVariantList, outputConfiguration));

	}

}
