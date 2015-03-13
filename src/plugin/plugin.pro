TEMPLATE = lib
TARGET = harboursaillogger
PLUGIN_IMPORT_PATH = harbour/saillogger/
QT -= gui
CONFIG += qt plugin hide_symbols link_pkgconfig

QT += qml
target.path = /usr/share/harbour-saillogger/qml/harbour/saillogger

HEADERS += emaillogger.h \
    exchangeactivesynclogger.h

SOURCES += plugin.cpp \
    emaillogger.cpp \
    exchangeactivesynclogger.cpp

OTHER_FILES += qmldir

qmldir.files += $$_PRO_FILE_PWD_/qmldir
qmldir.path +=  $$target.path
INSTALLS += target qmldir
