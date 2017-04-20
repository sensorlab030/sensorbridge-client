#ifndef WEBSOCKETSETTINGSWIDGET_H
#define WEBSOCKETSETTINGSWIDGET_H

#include "outputsettingswidget.h"

class QLineEdit;

class WebSocketSettingsWidget : public OutputSettingsWidget {
	Q_OBJECT

public:
	explicit WebSocketSettingsWidget(QWidget *parent = 0);

	bool			validateInput();
	QVariantList	outputConfiguration() const;
	void			storeCurrentSettings() const;

private:
	QLineEdit*	_portInput;

};

#endif // WEBSOCKETSETTINGSWIDGET_H
