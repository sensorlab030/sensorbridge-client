#ifndef SENSOROUTPUTFORMATTER_H
#define SENSOROUTPUTFORMATTER_H

#include <QString>
#include <QList>

class SensorOutputFormatter {

public:

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

};

#endif // SENSOROUTPUTFORMATTER_H
