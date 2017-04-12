#ifndef CSVFILEOUTPUT_H
#define CSVFILEOUTPUT_H

#include "sensoroutput.h"

class QFile;

/*!
 * WebSocketOutput
 * Implementation of SensorOutput as a CSV file writer. The data captured
 * via SensorOutput will be formatted as CSV and written to file
 */
class CsvFileOutput : public SensorOutput {
	Q_OBJECT

public:
	explicit CsvFileOutput(QObject *parent = 0);		//!< Class constructor
	QString path() const;								//!< Returns the output path
	QString description() const;						//!< Returns a description of output and its settings

public slots:
	void setPath(const QString& path);					//!< Set the output path

signals:
	void pathChanged(const QString& path);				//!< Signal that is emitted when the output path changed

protected:
	void startCapture();								//!< Start the websocket server
	void stopCapture();									//!< Stop the websocket server
	void handleCapture(const QList<float>& data);		//!< Write captured data to file

private:
	QString					_path;			//!< Output path
	QFile*					_outFile;		//!< Output file for the captured data

};

#endif // CSVFILEOUTPUT_H
