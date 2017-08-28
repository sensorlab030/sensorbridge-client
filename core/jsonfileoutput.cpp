#include "jsonfileoutput.h"

#include <QDir>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include "sensoroutputformatter.h"
#include "sensor.h"

JsonFileOutput::JsonFileOutput(QObject *parent) : SensorOutput(parent) {
	_rootArray = 0;
}

QString JsonFileOutput::path() const {
	return _path;
}

void JsonFileOutput::setPath(const QString& path) {
	if (path != _path) {
		_path = path;
		emit pathChanged(_path);
	}
}

QString JsonFileOutput::description() const {
	return QString("JSON files to %1 @%2ms")
			.arg(_path)
			.arg(QString::number(interval()));
}

void JsonFileOutput::startCapture() {
	_rootArray = new QJsonArray();
}

void JsonFileOutput::stopCapture() {
	if (_rootArray) {

		// Open file
		QString filename = QDir(_path).filePath(QString("sensordata_%1.json").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")));
		QFile file(filename);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

			// Convert to JSON document
			QJsonDocument outputDocument(*_rootArray);
			file.write(outputDocument.toJson());
			file.close();

		}

		// Clean up data in memory
		delete _rootArray;
		_rootArray = 0;

	}
}

void JsonFileOutput::handleCapture(const QList<float>& data) {
	if (_rootArray) {

		QJsonObject obj;
		obj.insert("timestamp", QJsonValue(QDateTime::currentMSecsSinceEpoch()));
		for (int i = 0; i < data.count(); i++) {
			obj.insert(Sensor::variableName(i + 1), QJsonValue(data.at(i)));
		}

		_rootArray->append(obj);
	}
}
