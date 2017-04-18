#ifndef UISENSOR_H
#define UISENSOR_H

#include <QObject>

class UiSensor : public QObject {
	Q_OBJECT

public:
	UiSensor(QObject* parent = 0);

};

#endif // UISENSOR_H
