#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>

class QWebSocket;
class QWebSocketServer;

class WebSocketServer : public QObject {
	Q_OBJECT

public:
	explicit WebSocketServer(QObject *parent = 0);

public slots:
	bool startServer(quint16 port);
	void stopServer();
	void broadcastMessage(const QString& message);		//!< Broadcast a message to all connected clients

private slots:
	void onNewConnection();
	void onSocketDisconnected();
	void onIncomingTextMessage(QString message);

private:
	void timerEvent(QTimerEvent*);

	QWebSocketServer*	_socketServer;
	QList<QWebSocket*>	_clients;
};

#endif // WEBSOCKETSERVER_H
