#include "websocketoutput.h"
#include <QWebSocketServer>
#include <QWebSocket>
#include <QtNetwork>
#include "sensoroutputformatter.h"

WebSocketOutput::WebSocketOutput(QObject *parent) : SensorOutput(parent) {
	_port = 9001;

	// Setup socket server
	_socketServer = new QWebSocketServer("SensorBridge", QWebSocketServer::NonSecureMode, this);
	connect(_socketServer, &QWebSocketServer::newConnection, this, &WebSocketOutput::onNewConnection);

}

int WebSocketOutput::port() const {
	return _port;
}

void WebSocketOutput::setPort(quint16 port) {
	if (port != _port) {
		_port = port;
		emit portChanged(_port);
	}
}

void WebSocketOutput::startCapture() {
	_socketServer->listen(QHostAddress::Any, _port);
}

void WebSocketOutput::stopCapture() {
	if (_socketServer->isListening()) {

		// Close socket
		_socketServer->close();

		// Destroy clients
		qDeleteAll(_clients);

	}
}

void WebSocketOutput::handleCapture(const QList<float>& data) {
	QString formattedData = SensorOutputFormatter::formatAsJson(data);
	for (QWebSocket* clientSocket: _clients) {
		clientSocket->sendTextMessage(formattedData);
	}
}

void WebSocketOutput::onNewConnection() {
	QWebSocket* clientSocket = _socketServer->nextPendingConnection();
	connect(clientSocket, &QWebSocket::textMessageReceived, this, &WebSocketOutput::onIncomingTextMessage);
	connect(clientSocket, &QWebSocket::disconnected, this, &WebSocketOutput::onSocketDisconnected);
	_clients.append(clientSocket);
}

void WebSocketOutput::onIncomingTextMessage(QString message) {
	QWebSocket* clientSocket = qobject_cast<QWebSocket*>(sender());
	if (clientSocket) {
		clientSocket->sendTextMessage(message);
	}
}

void WebSocketOutput::onSocketDisconnected() {
	QWebSocket* clientSocket = qobject_cast<QWebSocket*>(sender());
	if (clientSocket) {
		_clients.removeAll(clientSocket);
		clientSocket->deleteLater();
	}
}
