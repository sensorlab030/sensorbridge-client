#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class SensorOutput;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);

signals:
	void outputChanged(SensorOutput* output);

public slots:

private slots:
	void setupOutput();
	void startCapture();
	void stopCapture();
	void onOutputChanged();

private:
	SensorOutput*		_output = 0;

	QPushButton*		_startCaptureBtn;
	QPushButton*		_stopCaptureBtn;

};

#endif // MAINWINDOW_H
