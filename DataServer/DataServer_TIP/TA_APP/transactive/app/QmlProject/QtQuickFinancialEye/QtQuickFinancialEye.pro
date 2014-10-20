TEMPLATE = app

QT += qml quick
SOURCES += main.cpp \
    src/quotetypevalue.cpp
RESOURCES += QtQuickFinancialEye.qrc
OTHER_FILES += *.qml content/*.qml images/*.png

target.path = ./
INSTALLS += target

HEADERS += \
    src/quotetypevalue.h
