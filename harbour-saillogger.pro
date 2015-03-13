TEMPLATE = subdirs

src.subdir = src
src.target = sub-src

plugins.subdir = src/plugin
plugins.target = sub-plugin
plugins.depends = sub-src

SUBDIRS = src plugins

QML_FILES = qml/main.qml \
            qml/pages/*.qml \

    
OTHER_FILES += $${QML_FILES} \
            harbour-saillogger.desktop \
            rpm/harbour-saillogger.spec

desktop.files = *.desktop
desktop.path = /usr/share/applications

qml.files = $${QML_FILES}
qml.path = /usr/share/harbour-saillogger/qml

INSTALLS += desktop qml

