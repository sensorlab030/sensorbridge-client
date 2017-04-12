#include "csvfilesettingswidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QToolTip>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

CsvFileSettingsWidget::CsvFileSettingsWidget(QWidget *parent) : OutputSettingsWidget(parent) {

	_pathInput = new QLineEdit();
	_pathInput->setText(QDir::homePath());
	_pathInput->setToolTip("Directory where the files will be saved");

	QPushButton* browseButton = new QPushButton("Select");
	browseButton->setMaximumWidth(100);
	connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(selectPath()));

	QHBoxLayout* fileLayout = new QHBoxLayout();
	fileLayout->addWidget(_pathInput);
	fileLayout->addSpacing(20);
	fileLayout->addWidget(browseButton);

	QFormLayout* layout = new QFormLayout();
	layout->addRow("Capture directory", fileLayout);
	setLayout(layout);

}

void CsvFileSettingsWidget::selectPath() {
	QString newPath = QFileDialog::getExistingDirectory(this, "Select capture directory", _pathInput->text());
	if (!newPath.isEmpty()) {
		_pathInput->setText(newPath);
	}
}

bool CsvFileSettingsWidget::validateInput() {

	if (_pathInput->text().isEmpty() || !QDir(_pathInput->text()).exists()) {
		QToolTip::showText(_pathInput->mapToGlobal(QPoint()), _pathInput->toolTip());
		return false;
	}

	return true;

}

SensorOutput* CsvFileSettingsWidget::getSensorOutput(int interval) {
	return 0;
}
