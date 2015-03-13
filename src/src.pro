TEMPLATE = app
TARGET = harbour-saillogger

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QT += qml quick dbus
CONFIG += link_pkgconfig sailfishapp
PKGCONFIG += sailfishapp

SOURCES = main.cpp \

target.path = /usr/bin

INSTALLS += target


