#include "websocketserver.h"

#include <QWebSocketServer>
#include <QWebSocket>
#include <QtNetwork>

#include "time.h"

WebSocketServer::WebSocketServer(QObject *parent) : QObject(parent) {
	_socketServer = new QWebSocketServer("SensorBridge", QWebSocketServer::NonSecureMode, this);
	connect(_socketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
	startTimer(1000);
}

bool WebSocketServer::startServer(quint16 port) {
	return _socketServer->listen(QHostAddress::Any, port);
}

void WebSocketServer::stopServer() {
	if (_socketServer->isListening()) {

		// Close socket
		_socketServer->close();

		// Destroy clients
		qDeleteAll(_clients);

	}
}

void WebSocketServer::broadcastMessage(const QString& message) {
	for (QWebSocket* clientSocket: _clients) {
		clientSocket->sendTextMessage(message);
	}
}

void WebSocketServer::onNewConnection() {
	QWebSocket* clientSocket = _socketServer->nextPendingConnection();
	connect(clientSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onIncomingTextMessage);
	connect(clientSocket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);
	_clients.append(clientSocket);
}

void WebSocketServer::onIncomingTextMessage(QString message) {
	QWebSocket* clientSocket = qobject_cast<QWebSocket*>(sender());
	if (clientSocket) {
		clientSocket->sendTextMessage(message);
	}
}

void WebSocketServer::onSocketDisconnected() {
	QWebSocket* clientSocket = qobject_cast<QWebSocket*>(sender());
	if (clientSocket) {
		_clients.removeAll(clientSocket);
		clientSocket->deleteLater();
	}
}

void WebSocketServer::timerEvent(QTimerEvent*) {
	QString msg = QString("Runtime: %1").arg(time(NULL));
	broadcastMessage(msg);
}
