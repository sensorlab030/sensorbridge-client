#include "sensoroutputformatter.h"
#include <QDateTime>

/*!
 * Format given data list as a JSON object in a QString
 */
QString SensorOutputFormatter::formatAsJson(const QList<float>& data) {

	QString json = "{";
	for (int i = 0; i < data.count(); i++) {
		json.append(QString("\"sensor_%1\": %2").arg(QString::number(i), QString::number(data.at(i))));
		if (i < data.count() -1) {
			json.append(",");
		}
	}
	json.append("}");

	return json;
}

/*!
 * Get CSV line header corresponding to the formatAsCsv output
 */
QString SensorOutputFormatter::csvFormatHeader() {

	QString line;
	line.append("timestamp");
	line.append(csvFieldSeparator);
	for (int i = 0; i < SERIAL_ANALOG_SENSORS; i++) {
		line.append(QString("SERIAL_%1").arg(QString::number(i)));
		line.append((i < SERIAL_ANALOG_SENSORS-1) ? csvFieldSeparator : csvLineSeparator);
	}
	return line;
}

/*!
 * Format given data list as a CSV line in a QString
 */
QString SensorOutputFormatter::formatAsCsv(const QList<float>& data) {

	QString line;
	line.append(QString::number(QDateTime::currentMSecsSinceEpoch()));
	line.append(csvFieldSeparator);
	for (int i = 0; i < data.count(); i++) {
		line.append(QString::number(data.at(i)));
		line.append((i < data.count()-1) ? csvFieldSeparator : csvLineSeparator);
	}
	return line;
}
