#include "csvfileoutput.h"

#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>
#include "sensoroutputformatter.h"

CsvFileOutput::CsvFileOutput(QObject *parent) : SensorOutput(parent) {
	_outFile = 0;
}

QString CsvFileOutput::path() const {
	return _path;
}

void CsvFileOutput::setPath(const QString& path) {
	if (path != _path) {
		_path = path;
		emit pathChanged(_path);
	}
}

QString CsvFileOutput::description() const {
	return QString("CSV files to %1 @%2ms")
			.arg(_path)
			.arg(QString::number(interval()));
}

void CsvFileOutput::startCapture() {

	QString filename = QDir(_path).filePath(QString("sensordata_%1.csv").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")));

	_outFile = new QFile(filename);
	if (_outFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
		_outFile->write(SensorOutputFormatter::csvFormatHeader().toUtf8());
	}

}

void CsvFileOutput::stopCapture() {
	if (_outFile) {
		if (_outFile->isOpen()) {
			_outFile->close();
		}
		delete _outFile;
		_outFile = 0;
	}
}

void CsvFileOutput::handleCapture(const QList<float>& data) {
	if (_outFile && _outFile->isWritable()) {
		_outFile->write(SensorOutputFormatter::formatAsCsv(data).toUtf8());
		_outFile->flush();
	}
}
