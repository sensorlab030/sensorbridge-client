#ifndef CSVFILESETTINGSWIDGET_H
#define CSVFILESETTINGSWIDGET_H

#include "outputsettingswidget.h"

class QLineEdit;
class SensorOutput;

class CsvFileSettingsWidget : public OutputSettingsWidget {
	Q_OBJECT

public:
	explicit CsvFileSettingsWidget(QWidget *parent = 0);

	bool			validateInput();
	SensorOutput*	getSensorOutput(int interval);
	void			storeCurrentSettings() const;

private slots:
	void			selectPath();

private:
	QLineEdit*		_pathInput;

};

#endif // CSVFILESETTINGSWIDGET_H
