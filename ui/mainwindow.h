#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QLabel;
class QHBoxLayout;
class Sensor;
class SerialConnection;
class SensorOutput;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);

signals:
	void outputChanged(SensorOutput* output);

private slots:
	void openSettings();
	void startCapture();
	void stopCapture();
	void onOutputChanged();

private:
	QHBoxLayout *setupSensorsUI();

	QList<Sensor*>		_sensors;
	SerialConnection*	_serialConnection;
	SensorOutput*		_output = 0;

	QLabel*				_outputDescriptionLbl;
	QPushButton*		_startCaptureBtn;
	QPushButton*		_stopCaptureBtn;

};

#endif // MAINWINDOW_H
