#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;
class QStackedLayout;
class OutputSettingsWidget;

/**
 * @brief The SettingsDialog class
 */
class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	SettingsDialog(QWidget* parent = 0);

	QVariantList					outputConfiguration() const;

private slots:
	void onAcceptClicked();

private:
	OutputSettingsWidget*			currentOutputWidget();
	const OutputSettingsWidget*		currentOutputWidget() const;

	QComboBox*						_outputSelectionBox;
	QLineEdit*						_intervalInput;
	QStackedLayout*					_settingsWidgetStack;

};

#endif // SETTINGSDIALOG_H
