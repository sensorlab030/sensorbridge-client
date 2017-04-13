#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;
class QStackedLayout;
class SensorOutput;
class OutputSettingsWidget;
class WebSocketSettingsWidget;
class CsvFileSettingsWidget;
class JsonFileSettingsWidget;

/**
 * @brief The SettingsDialog class
 */
class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	SettingsDialog(QWidget* parent = 0);

	QString							getSerialPort();
	SensorOutput*					getSensorOutput();

private slots:
	void onAcceptClicked();

private:
	OutputSettingsWidget*			currentOutputWidget();

	QComboBox*						_serialPortSelectionBox;
	QComboBox*						_outputSelectionBox;
	QLineEdit*						_intervalInput;
	QStackedLayout*					_settingsWidgetStack;

	WebSocketSettingsWidget*		_webSocketSettings;
	CsvFileSettingsWidget*			_csvFileSettings;
	JsonFileSettingsWidget*			_jsonFileSettings;

};

#endif // SETTINGSDIALOG_H
