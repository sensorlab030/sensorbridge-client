#ifndef CSVFILESETTINGSWIDGET_H
#define CSVFILESETTINGSWIDGET_H

#include "outputsettingswidget.h"

class QLineEdit;

class CsvFileSettingsWidget : public OutputSettingsWidget {
	Q_OBJECT

public:
	explicit CsvFileSettingsWidget(QWidget *parent = 0);

	bool			validateInput();
	QVariantList	outputConfiguration() const;
	void			storeCurrentSettings() const;

private slots:
	void			selectPath();

private:
	QLineEdit*		_pathInput;

};

#endif // CSVFILESETTINGSWIDGET_H
