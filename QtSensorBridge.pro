TEMPLATE = app

QT += widgets serialport websockets charts
CONFIG += c++11

SOURCES += main.cpp \
    sensor.cpp \
    serialconnection.cpp \
    sensoroutput.cpp \
    websocketoutput.cpp \
    ui/mainwindow.cpp \
    ui/websocketsettingswidget.cpp \
    ui/outputsettingswidget.cpp \
    ui/csvfilesettingswidget.cpp \
    ui/sensorwidget.cpp \
    ui/settingsdialog.cpp \
    csvfileoutput.cpp

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    sensor.h \
    serialconnection.h \
    sensoroutput.h \
    websocketoutput.h \
    sensoroutputformatter.h \
    ui/mainwindow.h \
    ui/websocketsettingswidget.h \
    ui/outputsettingswidget.h \
    ui/csvfilesettingswidget.h \
    ui/sensorwidget.h \
    ui/settingsdialog.h \
    csvfileoutput.h

DEFINES += \
    SERIAL_ANALOG_SENSORS=6 \
    APP_VERSION=\\\"0.1.0\\\"
