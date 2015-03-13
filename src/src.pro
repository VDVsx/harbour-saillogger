TEMPLATE = app
TARGET = harbour-saillogger

QT += qml quick dbus
CONFIG += link_pkgconfig sailfishapp
PKGCONFIG += sailfishapp

HEADERS += \
    
SOURCES = main.cpp

target.path = /usr/bin

INSTALLS += target


