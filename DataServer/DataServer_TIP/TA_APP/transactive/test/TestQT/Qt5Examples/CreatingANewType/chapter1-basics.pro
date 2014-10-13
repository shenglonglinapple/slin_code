QT += qml quick

HEADERS += piechart.h \
    person.h
SOURCES += piechart.cpp \
           main.cpp \
    person.cpp

RESOURCES += chapter1-basics.qrc

DESTPATH = ./
target.path = $$DESTPATH

qml.files = *.qml
qml.path = $$DESTPATH

INSTALLS += target qml
