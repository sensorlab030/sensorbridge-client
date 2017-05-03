#include "serialconnection.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include "sensor.h"

SerialConnection::SerialConnection(QObject *parent) : QObject(parent) {

	for (int  i = 0; i < SERIAL_ANALOG_SENSORS; i++) {
		sensors[i] = new Sensor(this);
		sensors[i]->setName(QString("SERIAL_%1").arg(i));
	}

	buffer = new QByteArray();

	// Setup port
	port = new QSerialPort(this);
	connect(port, SIGNAL(readyRead()), this, SLOT(readData()));
//	connect(port, SIGNAL(error()), this, SLOT(handleError()));

}

int SerialConnection::getSensorCount() {
	return SERIAL_ANALOG_SENSORS;
}

Sensor* SerialConnection::getSensor(int index) {
	if (index >= SERIAL_ANALOG_SENSORS) {
		return 0;
	}
	return sensors[index];
}

QList<Sensor*> SerialConnection::getSensors() {
	QList<Sensor*> list;
	for (int i = 0; i < SERIAL_ANALOG_SENSORS; i++) {
		list.append(sensors[i]);
	}
	return list;
}

void SerialConnection::openConnection(const QString& portName) {

	// Disconnect port if open
	if (port->isOpen()) {
		closeConnection();
	}

	// Configure and open port
	port->setPortName(portName);
	port->setBaudRate(QSerialPort::Baud9600);
	if (!port->open(QSerialPort::ReadWrite)) {
		qDebug() << "Serial connection error:" << port->errorString();
	}

}

void SerialConnection::closeConnection() {
	if (port->isOpen()) {
		port->close();
	}
}

void SerialConnection::readData() {

	// Add to buffer
	buffer->append(port->readAll());

	// Read data collections
	int index = -1;
	while ((index = buffer->indexOf(0x0A)) != -1) {

		// Take data collection from buffer
		QByteArray segment = buffer->left(index -1);
		buffer->remove(0, index + 1);
		if (segment.size() != SERIAL_ANALOG_SENSORS * 2) {
			continue;
		}

		// Parse sensor readings
		QDataStream dataStream(segment);
		for (int i = 0; i < SERIAL_ANALOG_SENSORS; i++) {
			quint16 value;
			dataStream >> value;

			if (value <= 1023) {
				sensors[i]->setIsConnected(true);
				sensors[i]->pushValue((float) value / 1023.0);
			} else {
				sensors[i]->setIsConnected(false);
			}

		}

	}

}

QString SerialConnection::portName() const {
	return port->portName();
}

