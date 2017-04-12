#ifndef JSONFILESETTINGSWIDGET_H
#define JSONFILESETTINGSWIDGET_H

#include "outputsettingswidget.h"

class QLineEdit;
class SensorOutput;

class JsonFileSettingsWidget : public OutputSettingsWidget {

public:
	explicit JsonFileSettingsWidget(QWidget *parent = 0);

	bool			validateInput();
	SensorOutput*	getSensorOutput(int interval);

private slots:
	void			selectPath();

private:
	QLineEdit*		_pathInput;

};

#endif // JSONFILESETTINGSWIDGET_H
