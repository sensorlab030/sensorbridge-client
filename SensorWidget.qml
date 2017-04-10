import QtQuick 2.0

import QtCharts 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import com.cleverfranke.sensorbridge 1.0

ColumnLayout {
	readonly property int xResolution: 100;
	property Sensor sensor

	ChartView {
		id: chart
		Layout.fillHeight: true
		Layout.fillWidth: true
//		theme: ChartView.ChartThemeHighContrast
		antialiasing: true
		title: ""
		legend.visible: false
		dropShadowEnabled: false
		backgroundRoundness: 0


		ValueAxis {
			id: axisX
			min: 0
			max: xResolution
			tickCount: 0
			visible: false
		}

		ValueAxis {
			id: axisY
			min: 0
			max: 1
			tickCount: 11
			visible: false
		}

		LineSeries {
			id: sensor1Series
			axisX: axisX
			axisY: axisY
		}
	}

	Item {
		Layout.alignment: Qt.AlignLeft
		Layout.preferredHeight: 30
		Layout.margins: 10

		Row {
			Label {
				text: "Smoothing: "
			}
			ComboBox {
				model: [ "None", "Exponential", "Moving average", "Holt-Winters" ]
			}
		}

	}

	onSensorChanged: {
		chart.title = sensor.name;
		console.log("YAY", sensor.name);
	}

	sensor.onValuePushed: {
		console.log("QML VAL", newValue);
	}

//	Timer {
//		repeat: true;
//		interval: 100
//		running: true;
//		triggeredOnStart: true
//		onTriggered: {
//			sensor1Series.clear();
//			for (var i = 1; i < xResolution; i++) {
//				var val = Math.random();
//				sensor1Series.append(i, val);
//			}
//		}
//	}
}
