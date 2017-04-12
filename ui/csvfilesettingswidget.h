#ifndef CSVFILESETTINGSWIDGET_H
#define CSVFILESETTINGSWIDGET_H

#include "outputsettingswidget.h"

class QLineEdit;

class CsvFileSettingsWidget : public OutputSettingsWidget {
	Q_OBJECT

public:
	CsvFileSettingsWidget(QWidget *parent = 0);

	bool			validateInput();
	SensorOutput*	getSensorOutput(int interval);

private slots:
	void			selectPath();

private:
	QLineEdit*		_pathInput;
};

#endif // CSVFILESETTINGSWIDGET_H
