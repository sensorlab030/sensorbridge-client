#ifndef SENSOROUTPUTFORMATTER_H
#define SENSOROUTPUTFORMATTER_H

#include <QString>
#include <QList>

/*!
 * SensorOutputFormatter
 * Collection of formatting methods for the data series
 */
class SensorOutputFormatter {

public:
	static QString formatAsJson(const QList<float>& data);  //!< Format given data list as a JSON object in a QString
	static QString csvFormatHeader();						//!< Get CSV line header corresponding to the formatAsCsv output
	static QString formatAsCsv(const QList<float>& data);	//!< Format given data list as a CSV line in a QString

private:
	static const char csvFieldSeparator = ',';
	static const char csvLineSeparator = '\n';

};

#endif // SENSOROUTPUTFORMATTER_H
