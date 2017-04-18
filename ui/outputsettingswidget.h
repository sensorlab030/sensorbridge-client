#ifndef OUTPUTSETTINGSWIDGET_H
#define OUTPUTSETTINGSWIDGET_H

#include <QWidget>

class SensorOutput;

class OutputSettingsWidget : public QWidget {
	Q_OBJECT

public:
	explicit OutputSettingsWidget(QWidget *parent = 0) : QWidget(parent) {}

	virtual bool validateInput() = 0;								//!< Validate input
	virtual QVariantList outputConfiguration() = 0;					//!< Get the output configuration with the current selected settings
	virtual void storeCurrentSettings() const = 0;					//!< Store the current settings

};

#endif // OUTPUTSETTINGSWIDGET_H
