#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T14:55:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartTraderQT
TEMPLATE = app


SOURCES += main.cpp\
    src/StockManager.cpp \
    src/ClientMainWindow.cpp

HEADERS  += \
    src/StockManager.h \
    src/ClientMainWindow.h

RESOURCES += \
    Resources/SmartTraderQT.qrc
