#ifndef JSONFILEOUTPUT_H
#define JSONFILEOUTPUT_H

#include "sensoroutput.h"

class QJsonArray;

/*!
 * JsonFileOutput
 * Implementation of SensorOutput as a JSON file writer. The data captured
 * via SensorOutput will be formatted as JSON and written to file
 */
class JsonFileOutput : public SensorOutput {
	Q_OBJECT

	public:
		explicit JsonFileOutput(QObject *parent = 0);		//!< Class constructor
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
		QString					_path;				//!< Output path
		QJsonArray*				_rootArray;			//!< Output document

};

#endif // JSONFILEOUTPUT_H
