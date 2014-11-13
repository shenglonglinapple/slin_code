TEMPLATE = app

QT += qml quick widgets sql

SOURCES += main.cpp

RESOURCES += qml.qrc

OTHER_FILES += *.qml qmlfile/*.qml images/*.png

# Default rules for deployment.
include(deployment.pri)
