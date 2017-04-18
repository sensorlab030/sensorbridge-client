#include "jsonfilesettingswidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolTip>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QSettings>

JsonFileSettingsWidget::JsonFileSettingsWidget(QWidget* parent) : OutputSettingsWidget(parent) {

	_pathInput = new QLineEdit();
	_pathInput->setText(QSettings().value("jsonfile/path", QDir::homePath()).toString());
	_pathInput->setToolTip("Directory where the files will be saved");

	QPushButton* browseButton = new QPushButton("Select");
	browseButton->setMaximumWidth(100);
	connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(selectPath()));

	QHBoxLayout* fileLayout = new QHBoxLayout();
	fileLayout->addWidget(_pathInput);
	fileLayout->addWidget(browseButton);

	QGridLayout* layout = new QGridLayout();
	layout->setMargin(0);
	layout->setColumnMinimumWidth(0, 130);
	layout->setColumnStretch(0, 0);
	layout->addWidget(new QLabel("Capture directory"), 0, 0);
	layout->addLayout(fileLayout, 0, 1, 1, Qt::AlignLeft);
	setLayout(layout);

}

void JsonFileSettingsWidget::selectPath() {
	QString newPath = QFileDialog::getExistingDirectory(this, "Select capture directory", _pathInput->text());
	if (!newPath.isEmpty()) {
		_pathInput->setText(newPath);
	}
}

bool JsonFileSettingsWidget::validateInput() {

	if (_pathInput->text().isEmpty() || !QDir(_pathInput->text()).exists()) {
		QToolTip::showText(_pathInput->mapToGlobal(QPoint()), _pathInput->toolTip());
		return false;
	}

	return true;

}

QVariantList JsonFileSettingsWidget::outputConfiguration() {
	QVariantList config;
	config << _pathInput->text();
	return config;
}

void JsonFileSettingsWidget::storeCurrentSettings() const {
	QSettings settings;
	settings.setValue("jsonfile/path", _pathInput->text());
}
