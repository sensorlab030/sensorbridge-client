#ifndef OUTPUTSETTINGSDIALOG_H
#define OUTPUTSETTINGSDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;
class QStackedLayout;
class SensorOutput;
class OutputSettingsWidget;
class WebSocketSettingsWidget;
class CsvFileSettingsWidget;

class OutputSettingsDialog : public QDialog {
	Q_OBJECT

public:
	OutputSettingsDialog(QWidget* parent = 0);

	SensorOutput*					getSensorOutput();

private slots:
	void onAcceptClicked();

private:
	OutputSettingsWidget*			currentOutputWidget();

	QComboBox*						_outputSelectionBox;
	QLineEdit*						_intervalInput;
	QStackedLayout*					_settingsWidgetStack;

	WebSocketSettingsWidget*		_webSocketSettings;
	CsvFileSettingsWidget*			_csvFileSettings;

};

#endif // OUTPUTSETTINGSDIALOG_H
