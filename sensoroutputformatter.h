#ifndef SENSOROUTPUTFORMATTER_H
#define SENSOROUTPUTFORMATTER_H

#include <QString>
#include <QStringBuilder>
#include <QList>

class SensorOutputFormatter {

public:
	static const char csvFieldSeparator = ',';
	static const char csvLineSeparator = '\n';

	/*!
	 * Format given data list as a JSON object in a QString
	 */
	static QString formatAsJson(const QList<float>& data) {

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
	static QString csvFormatHeader() {

		QString line;
		line = line % "timestamp" % csvFieldSeparator;
		for (int i = 0; i < SERIAL_ANALOG_SENSORS; i++) {
			if (i < SERIAL_ANALOG_SENSORS-1) {
				line = line % "SERIAL_" % QString::number(i) % csvFieldSeparator;
			} else {
				line = line % "SERIAL_" % QString::number(i) % csvLineSeparator;
			}
		}

		return line;
	}

	/*!
	 * Format given data list as a CSV line in a QString
	 */
	static QString formatAsCsv(const QList<float>& data) {

		QString line;
		line = line % QString::number(QDateTime::currentMSecsSinceEpoch()) % csvFieldSeparator;
		for (int i = 0; i < data.count(); i++) {
			if (i < data.count() - 1) {
				line = line % QString::number(data.at(i)) % csvFieldSeparator;
			} else {
				line = line % QString::number(data.at(i)) % csvLineSeparator;
			}
		}

		return line;
	}



};

#endif // SENSOROUTPUTFORMATTER_H
