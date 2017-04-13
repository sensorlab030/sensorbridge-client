#include "settingsdialog.h"
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedLayout>
#include <QToolTip>
#include <QDebug>
#include <QSerialPortInfo>
#include <QSettings>

#include "sensoroutput.h"
#include "websocketsettingswidget.h"
#include "csvfilesettingswidget.h"
#include "jsonfilesettingswidget.h"

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
	setWindowTitle("Configure sensor output");
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	setFixedWidth(600);

	QSettings settings;

	// Serial port selection
	_serialPortSelectionBox = new QComboBox(this);
	for (QSerialPortInfo portInfo: QSerialPortInfo::availablePorts()) {
		QString displayName = QString("%1 (%2)").arg(portInfo.portName()).arg(portInfo.description());
		_serialPortSelectionBox->addItem(displayName, portInfo.portName());
	}
	if (int previousSerialIndex = _serialPortSelectionBox->findData(settings.value("serial", "")) != -1) {
		_serialPortSelectionBox->setCurrentIndex(previousSerialIndex);
	}

	// Output type selection
	_outputSelectionBox = new QComboBox(this);
	_outputSelectionBox->addItem("Websocket");
	_outputSelectionBox->addItem("CSV file");
	_outputSelectionBox->addItem("JSON file");
	_outputSelectionBox->setCurrentIndex(settings.value("output-method", 0).toInt());

	// Interval
	_intervalInput = new QLineEdit();
	_intervalInput->setMaximumWidth(100);
	_intervalInput->setValidator(new QIntValidator(10, 6000));
	_intervalInput->setText(settings.value("interval", 100).toString());
	_intervalInput->setToolTip("Capture interval (should be between 10 and 6,000 ms)");

	if (int previousSerialIndex = _serialPortSelectionBox->findData(settings.value("serial", "")) != -1) {
		_serialPortSelectionBox->setCurrentIndex(previousSerialIndex);
	}

	// Output widgets & interval
	_webSocketSettings = new WebSocketSettingsWidget();
	_csvFileSettings = new CsvFileSettingsWidget();
	_jsonFileSettings = new JsonFileSettingsWidget();

	// Accept button
	QPushButton* acceptButton = new QPushButton("Ok");
	connect(acceptButton, &QPushButton::clicked, this, &SettingsDialog::onAcceptClicked);

	// Create form layout
	QGridLayout* formLayout = new QGridLayout();
	formLayout->setColumnMinimumWidth(0, 130);
	formLayout->setColumnStretch(0, 0);
	formLayout->addWidget(new QLabel("Serial port"), 0, 0);
	formLayout->addWidget(_serialPortSelectionBox, 0, 1, 1, 1, Qt::AlignLeft);
	formLayout->addWidget(new QLabel("Output"), 1, 0);
	formLayout->addWidget(_outputSelectionBox, 1, 1, 1, 1, Qt::AlignLeft);
	formLayout->addWidget(new QLabel("Capture inverval (ms)"), 2, 0);
	formLayout->addWidget(_intervalInput, 2, 1, 1, 1, Qt::AlignLeft);

	// Center layout
	_settingsWidgetStack = new QStackedLayout();
	_settingsWidgetStack->addWidget(_webSocketSettings);
	_settingsWidgetStack->addWidget(_csvFileSettings);
	_settingsWidgetStack->addWidget(_jsonFileSettings);
	connect(_outputSelectionBox, SIGNAL(activated(int)), _settingsWidgetStack, SLOT(setCurrentIndex(int)));
	_settingsWidgetStack->setCurrentIndex(_outputSelectionBox->currentIndex());

	// Bottom layout
	QHBoxLayout* bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(acceptButton);

	// Create main layout
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addLayout(formLayout, 0);
	mainLayout->addLayout(_settingsWidgetStack, 0);
	mainLayout->addStretch();
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);

}

void SettingsDialog::onAcceptClicked() {

	// Validation flags
	bool inputOk = true;

	// Validate interval
	if (!_intervalInput->hasAcceptableInput()) {
		QToolTip::showText(_intervalInput->mapToGlobal(QPoint()), _intervalInput->toolTip());
		inputOk = false;
	}

	// Validate output specific settings
	if (!currentOutputWidget()->validateInput()) {
		inputOk = false;
	}

	// Accept dialog on valid input
	if (inputOk) {

		// Save current settings
		QSettings settings;
		settings.setValue("serial", _serialPortSelectionBox->currentData().toString());
		settings.setValue("interval", _intervalInput->text().toInt());
		settings.setValue("output-method", _outputSelectionBox->currentIndex());

		// Save settings out current output
		currentOutputWidget()->storeCurrentSettings();

		// Accept dialog
		accept();
	}

}

OutputSettingsWidget* SettingsDialog::currentOutputWidget() {
	return (OutputSettingsWidget*) _settingsWidgetStack->currentWidget();
}

QString SettingsDialog::getSerialPort() {
	return _serialPortSelectionBox->currentData().toString();
}

SensorOutput* SettingsDialog::getSensorOutput() {
	return currentOutputWidget()->getSensorOutput(_intervalInput->text().toInt());
}
