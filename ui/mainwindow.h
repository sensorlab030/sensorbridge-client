#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QComboBox;
class QPushButton;
class QLabel;
class BridgeEngine;
class SensorOutput;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(BridgeEngine* engine, QWidget *parent = 0);

private slots:
	void initializeInterface();					//!< Initialize the interface
	void openSettings();						//!< Open output settings dialog
	void onSerialPortSelectorChanged();			//!< Handle change in serial port
	void onOutputActiveChanged(bool active);	//!< Handle change in output activity
	void onOutputChanged(SensorOutput* output);	//!< Handle change in output

	void repopulateSerialPorts();

private:
	BridgeEngine*		_engine;
	QComboBox*			_serialPortSelector;
	QLabel*				_outputDescriptionLbl;
	QPushButton*		_setupBbtn;
	QPushButton*		_startCaptureBtn;
	QPushButton*		_stopCaptureBtn;

};

#endif // MAINWINDOW_H
