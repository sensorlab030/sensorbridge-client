#include "websocketsettingswidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QToolTip>
#include "websocketoutput.h"

WebSocketSettingsWidget::WebSocketSettingsWidget(QWidget *parent) : OutputSettingsWidget(parent) {

	_portInput = new QLineEdit();
	_portInput->setValidator(new QIntValidator(1024, 32768));
	_portInput->setText("9001");
	_portInput->setMaximumWidth(100);
	_portInput->setToolTip("Websocket port (should be between 1024 and 32768)");

	QFormLayout* layout = new QFormLayout();
	layout->addRow("Port", _portInput);
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

SensorOutput* WebSocketSettingsWidget::getSensorOutput(int interval) {
	WebSocketOutput* output = new WebSocketOutput();
	output->setInterval(interval);
	output->setPort(_portInput->text().toInt());
	return output;
}
