#include "outputsettingsdialog.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedLayout>
#include <QToolTip>
#include <QDebug>

#include "sensoroutput.h"
#include "websocketsettingswidget.h"
#include "csvfilesettingswidget.h"

OutputSettingsDialog::OutputSettingsDialog(QWidget* parent) : QDialog(parent) {
	setWindowTitle("Configure sensor output");
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	// Output selection
	_outputSelectionBox = new QComboBox(this);
	_outputSelectionBox->addItem("Websocket");
	_outputSelectionBox->addItem("CSV file");
//	_outputSelectionBox->addItem("JSON file");

	// Interval
	_intervalInput = new QLineEdit();
	_intervalInput->setMaximumWidth(100);
	_intervalInput->setValidator(new QIntValidator(10, 6000));
	_intervalInput->setText("100");
	_intervalInput->setToolTip("Capture interval (should be between 10 and 6,000 ms)");

	// Output widgets & interval
	_webSocketSettings = new WebSocketSettingsWidget();
	_csvFileSettings = new CsvFileSettingsWidget();

	// Accept button
	QPushButton* acceptButton = new QPushButton("Ok");
	connect(acceptButton, &QPushButton::clicked, this, &OutputSettingsDialog::onAcceptClicked);

	// Create top layout
	QHBoxLayout* topLayout = new QHBoxLayout();
	topLayout->addWidget(new QLabel("Output type"));
	topLayout->addWidget(_outputSelectionBox);
	topLayout->addStretch(40);
	topLayout->addWidget(new QLabel("Interval (ms)"));
	topLayout->addWidget(_intervalInput);

	// Center layout
	_settingsWidgetStack = new QStackedLayout();
	_settingsWidgetStack->addWidget(_webSocketSettings);
	_settingsWidgetStack->addWidget(_csvFileSettings);
	connect(_outputSelectionBox, SIGNAL(activated(int)), _settingsWidgetStack, SLOT(setCurrentIndex(int)));

	// Bottom layout
	QHBoxLayout* bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(acceptButton);

	// Create main layout
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(_settingsWidgetStack);
	mainLayout->addStretch();
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);

}

void OutputSettingsDialog::onAcceptClicked() {

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
		accept();
	}

}

OutputSettingsWidget* OutputSettingsDialog::currentOutputWidget() {
	return (OutputSettingsWidget*) _settingsWidgetStack->currentWidget();
}

SensorOutput* OutputSettingsDialog::getSensorOutput() {
	return currentOutputWidget()->getSensorOutput(_intervalInput->text().toInt());
}
