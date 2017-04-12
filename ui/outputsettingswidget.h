#ifndef OUTPUTSETTINGSWIDGET_H
#define OUTPUTSETTINGSWIDGET_H

#include <QWidget>

class SensorOutput;

class OutputSettingsWidget : public QWidget {
	Q_OBJECT

public:
	explicit OutputSettingsWidget(QWidget *parent = 0);

	virtual bool validateInput() = 0;								//!< Validate input
	virtual SensorOutput* getSensorOutput(int interval) = 0;		//!<

};

#endif // OUTPUTSETTINGSWIDGET_H
