#ifndef JSONFILESETTINGSWIDGET_H
#define JSONFILESETTINGSWIDGET_H

#include "outputsettingswidget.h"

class QLineEdit;
class SensorOutput;

class JsonFileSettingsWidget : public OutputSettingsWidget {
	Q_OBJECT

public:
	explicit JsonFileSettingsWidget(QWidget *parent = 0);

	bool			validateInput();
	QVariantList	outputConfiguration() const;
	void			storeCurrentSettings() const;

private slots:
	void			selectPath();

private:
	QLineEdit*		_pathInput;

};

#endif // JSONFILESETTINGSWIDGET_H
