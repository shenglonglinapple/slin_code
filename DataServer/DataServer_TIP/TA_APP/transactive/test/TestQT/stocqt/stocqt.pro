TEMPLATE = app

QT += qml quick
SOURCES += main.cpp
RESOURCES += stocqt.qrc
OTHER_FILES += *.qml content/*.qml content/images/*.png

target.path = ./
INSTALLS += target
