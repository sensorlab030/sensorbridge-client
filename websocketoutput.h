#ifndef WEBSOCKETOUTPUT_H
#define WEBSOCKETOUTPUT_H

#include "sensoroutput.h"

class QWebSocket;
class QWebSocketServer;

/*!
 * WebSocketOutput
 * Implementation of SensorOutput as a WebSocket. The data captured
 * via SensorOutput will be JSON formatted and sent over a websocket
 * to any connected client
 */
class WebSocketOutput : public SensorOutput {
	Q_OBJECT

public:
	explicit WebSocketOutput(QObject *parent = 0);		//!< Class constructor
	int port() const;									//!< Returns the websocket port number
	QString description() const;						//!< Returns a description of output and its settings

public slots:
	void setPort(quint16 port);							//!< Set the websocket port number

signals:
	void portChanged(quint16 port);						//!< Signal that is emitted when the port changed

private slots:
	void onNewConnection();								//!< Handle client connect
	void onSocketDisconnected();						//!< Handle client disconnect
	void onIncomingTextMessage(QString message);		//!< Echo incoming message from client

protected:
	void startCapture();								//!< Start the websocket server
	void stopCapture();									//!< Stop the websocket server
	void handleCapture(const QList<float>& data);					//!< Send capture data to all connected clients

private:
	quint16				_port;							//!< The websocket port number
	QWebSocketServer*	_socketServer;					//!< The socket server
	QList<QWebSocket*>	_clients;						//!< All connected clients

};

#endif // WEBSOCKETOUTPUT_H
