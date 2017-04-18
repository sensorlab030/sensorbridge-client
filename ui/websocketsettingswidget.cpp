#include "websocketsettingswidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QToolTip>
#include <QSettings>

WebSocketSettingsWidget::WebSocketSettingsWidget(QWidget *parent) : OutputSettingsWidget() {

	_portInput = new QLineEdit();
	_portInput->setValidator(new QIntValidator(1024, 32768));
	_portInput->setText(QSettings().value("websocket/port", 9001).toString());
	_portInput->setMaximumWidth(100);
	_portInput->setToolTip("Websocket port (should be between 1024 and 32768)");

	QGridLayout* layout = new QGridLayout();
	layout->setMargin(0);
	layout->setColumnMinimumWidth(0, 130);
	layout->setColumnStretch(0, 0);
	layout->addWidget(new QLabel("Port"), 0, 0);
	layout->addWidget(_portInput, 0, 1, 1, Qt::AlignLeft);
	setLayout(layout);

}

bool WebSocketSettingsWidget::validateInput() {

	if (!_portInput->hasAcceptableInput()) {
		QToolTip::showText(_portInput->mapToGlobal(QPoint()), _portInput->toolTip());
		_portInput->setStyleSheet("QLineEdit {background-color: red; color: white;}");
		return false;
	}

	return true;

}

QVariantList WebSocketSettingsWidget::outputConfiguration() {
	QVariantList config;
	config << _portInput->text().toInt();
	return config;
}

void WebSocketSettingsWidget::storeCurrentSettings() const {
	QSettings settings;
	settings.setValue("websocket/port", _portInput->text().toInt());
}
