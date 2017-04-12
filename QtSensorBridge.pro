TEMPLATE = app

QT += qml quick widgets serialport websockets network
CONFIG += c++11

SOURCES += main.cpp \
    sensor.cpp \
    serialconnection.cpp \
    sensoroutput.cpp \
    websocketoutput.cpp \
    ui/mainwindow.cpp \
    ui/websocketsettingswidget.cpp \
    ui/outputsettingsdialog.cpp \
    ui/outputsettingswidget.cpp \
    ui/csvfilesettingswidget.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

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
    ui/outputsettingsdialog.h \
    ui/outputsettingswidget.h \
    ui/csvfilesettingswidget.h

DEFINES += \
    SERIAL_ANALOG_SENSORS=6 \
    APP_VERSION=\\\"0.1.0\\\"
