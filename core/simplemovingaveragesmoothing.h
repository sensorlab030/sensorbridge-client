#ifndef SIMPLEMOVINGAVERAGESMOOTHING_H
#define SIMPLEMOVINGAVERAGESMOOTHING_H

#include <QObject>
#include <QVector>

class SimpleMovingAverageSmoothing : public QObject {
	Q_OBJECT

public:
	explicit SimpleMovingAverageSmoothing(QObject* parent = 0);

	float lastValue() const;

signals:
	void valueAdded(float value);

public slots:
	void pushValue(float value);

private:
	static float calculateSmoothedValue(const QVector<float>& buffer);

	int					_sampleCount;
	QVector<float>		_values;
	float				_smoothedValue;

};

#endif // SIMPLEMOVINGAVERAGESMOOTHING_H
