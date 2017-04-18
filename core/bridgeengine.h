#ifndef BRIDGEENGINE_H
#define BRIDGEENGINE_H

#include <QObject>

class SerialConnection;
class Sensor;
class SensorOutput;

/*!
 * BridgeEngine
 * Class that owns and manages the sensor connections and
 * and the data outputs and provides the interface to
 * configure and start/stop them. A BridgeEngine instance
 * will run in a separate thread, so communication is
 * suggested to go via (queued) signals and slots.
 */
class BridgeEngine : public QObject {
	Q_OBJECT

public:
	explicit BridgeEngine(QObject *parent = 0);					//!< Class constructor
	QList<Sensor*> sensors();									//!< Get all available sensors

signals:
	void initialized();											//!< Signal that indicates that the engine is ready to be used]
	void outputActiveChanged(bool outputActive);				//!< Signal that indicates that the output has become active/inactive
	void outputChanged(SensorOutput* output);					//!< Signal that indicates that the output has changed

public slots:
	void initialize();											//!< Initialize engine, intialized signal will be emitted once done
	void startSerialConnection(const QString& port);			//!< Start serial communication on given port (if serial port is already connected, it will be disconnected first)
	void stopSerialConnection();								//!< Stop serial communication
	void startOutput();											//!< Start the output recording/serving
	void stopOutput();											//!< Stop the output recording/serving

	void configureOutput(const QVariantList& configuration);	//!< Configure the output with the given list

private slots:
	void terminate();											//!< Slot is called when application is about to quit

private:
	SerialConnection*			_serialConnection;				//!< Connection to the serial port
	SensorOutput*				_output;						//!< Sensor output

};

#endif // BRIDGEENGINE_H
