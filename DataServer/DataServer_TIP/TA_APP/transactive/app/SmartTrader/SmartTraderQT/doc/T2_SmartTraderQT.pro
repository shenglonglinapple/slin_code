#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T14:55:26
#
#-------------------------------------------------

#set model
TEMPLATE = app

#set language C++
LANGUAGE = C++   

#set Config fro qmake
#CONFIG+= qt warn_on debug release
CONFIG+= qt warn_on debug


#release mode
release {
#set exe file name
TARGET = SmartTraderQT
#set exe file path
DESTDIR += ../../../../../bin/win32_nr  
#set obj file path
OBJECTS_DIR = ../../../../../build/win32_nr/transactive/app/SmartTrader/SmartTraderQT
#set include file path
INCLUDEPATH += .
INCLUDEPATH += ./src
#set lib file
LIBS += QtCore4.lib
LIBS += QtGuid4.lib
LIBS += QtSqld4.lib
#set lib file path
LIBDIR = C:/Qt/4.8.5/lib
QMAKE_LIBDIR = $${LIBDIR}
#set ui to ui.h file path
UI_DIR += $${OBJECTS_DIR}/forms 
#set qrc to qrc.h file path
RCC_DIR += $${OBJECTS_DIR}/tmp
#set moc moc_.* file path
MOC_DIR += $${OBJECTS_DIR}/tmp
}

#debug mode
debug {
#set exe file name
TARGET = SmartTraderQT_d
#set exe file path
DESTDIR += ../../../../../bin/win32_nd 
#set obj file path
OBJECTS_DIR = ../../../../../build/win32_nd/transactive/app/SmartTrader/SmartTraderQT
#set include file path
INCLUDEPATH += .
INCLUDEPATH += ./src
#set lib file
LIBS += QtCore4d.lib
LIBS += QtGuid4d.lib
LIBS += QtSqld4d.lib
#set lib file path
LIBDIR = C:/Qt/4.8.5/lib
QMAKE_LIBDIR = $${LIBDIR}
#set ui to ui.h file path
UI_DIR += $${OBJECTS_DIR}/forms 
#set qrc to qrc.h file path
RCC_DIR += $${OBJECTS_DIR}/tmp
#set moc moc_.* file path
MOC_DIR += $${OBJECTS_DIR}/tmp
}


#set depend path
DEPENDPATH += .
DEPENDPATH += src
DEPENDPATH += $${OBJECTS_DIR}/forms
DEPENDPATH += $${OBJECTS_DIR}/tmp


#-------------------------------------------	
#set HEADERS path
HEADERS  += \
    src/ClientMainWindow.h \
    src/StockManager.h
	
#set Source path
SOURCES += main.cpp\
    src/ClientMainWindow.cpp \
    src/StockManager.cpp

#set RESOURCES path
RESOURCES += \
    Resources/SmartTraderQT.qrc
	
#set ui path
#FORMS = ../form/scdmainform.ui 

#set IMAGES path
#IMAGES = images/substation.png 
#-------------------------------------------


#build message
message($${INCLUDEPATH})	
message($${DEPENDPATH})






#.  .pro
#.. SmartTraderQT
#../.. SmartTrader/SmartTraderQT
#../../.. app/SmartTrader/SmartTraderQT
#../../../.. transactive/app/SmartTrader/SmartTraderQT
#../../../../.. TA_APP/transactive/app/SmartTrader/SmartTraderQT

#DESTDIR += ../../../../../bin/win32_nd
#TARGET = SmartTraderQT
#DESTDIR += ../../../../../bin/win32_nd