TEMPLATE = subdirs

src.subdir = src
src.target = sub-src

SUBDIRS = src

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

