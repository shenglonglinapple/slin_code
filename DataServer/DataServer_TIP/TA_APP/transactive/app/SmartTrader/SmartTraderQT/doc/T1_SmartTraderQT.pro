#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T14:55:26
#
#-------------------------------------------------

#模块配置
TEMPLATE = app

#C++语言
LANGUAGE = C++   

#CONFIG用来告诉qmake关于应用程序的配置信息
#CONFIG+= qt warn_on debug release
CONFIG+= qt warn_on debug


#release mode
release {
#指定生成的应用程序名
TARGET = SmartTraderQT
#指定生成的应用程序放置的目录
DESTDIR += ../../../../../bin/win32_nr  
#指定目标文件(obj)的存放目录
OBJECTS_DIR = ../../../../../build/win32_nr/transactive/app/SmartTrader/SmartTraderQT
#头文件包含路径
INCLUDEPATH += .
INCLUDEPATH += ./src
#引入的lib文件,用于引入动态链接库
LIBS += QtCore4.lib
LIBS += QtGuid4.lib
LIBS += QtSqld4.lib
LIBDIR = C:/Qt/4.8.5/lib
QMAKE_LIBDIR = $${LIBDIR}
#指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
#UI_DIR += forms
# .ui文件转会为**.h   存放的目录
UI_HEADERS_DIR = $${OBJECTS_DIR}/forms  
# .ui文件转会为**.cpp 存放的目录
UI_SOURCES_DIR = $${OBJECTS_DIR}/forms  
#指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
RCC_DIR += $${OBJECTS_DIR}/tmp
#指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
MOC_DIR += $${OBJECTS_DIR}/tmp
}

#debug mode
debug {
#指定生成的应用程序名
TARGET = SmartTraderQT_d
#指定生成的应用程序放置的目录
DESTDIR += ../../../../../bin/win32_nd 
#指定目标文件(obj)的存放目录
OBJECTS_DIR = ../../../../../build/win32_nd/transactive/app/SmartTrader/SmartTraderQT
#头文件包含路径
INCLUDEPATH += .
INCLUDEPATH += ./src
#引入的lib文件,用于引入动态链接库
LIBS += QtCore4d.lib
LIBS += QtGuid4d.lib
LIBS += QtSqld4d.lib
LIBDIR = C:/Qt/4.8.5/lib
QMAKE_LIBDIR = $${LIBDIR}

#指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
#UI_DIR += forms
# .ui文件转会为**.h   存放的目录
UI_HEADERS_DIR = $${OBJECTS_DIR}/forms  
# .ui文件转会为**.cpp 存放的目录
UI_SOURCES_DIR = $${OBJECTS_DIR}/forms  
#指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
RCC_DIR += $${OBJECTS_DIR}/tmp
#指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
MOC_DIR += $${OBJECTS_DIR}/tmp
}


#程序编译时依赖的相关路径
DEPENDPATH += .
DEPENDPATH += src
DEPENDPATH += $${OBJECTS_DIR}/forms
DEPENDPATH += $${OBJECTS_DIR}/tmp


#-------------------------------------------	
#工程中包含的头文件
HEADERS  += \
    StockManager.h \
    ClientMainWindow.h
	
#工程中包含的源文件
SOURCES += main.cpp\
    StockManager.cpp \
    ClientMainWindow.cpp	

#工程中包含的资源文件
RESOURCES += \
    Resources/SmartTraderQT.qrc
	
#工程中包含的.ui设计文件
#FORMS = ../form/scdmainform.ui 

#图像文件
#IMAGES = images/substation.png 
#-------------------------------------------


#build message
#头文件包含路径
message($$INCLUDEPATH)
message($${INCLUDEPATH})	

#程序编译时依赖的相关路径
message($$DEPENDPATH)
message($${DEPENDPATH})






#.  .pro
#.. SmartTraderQT
#../.. SmartTrader/SmartTraderQT
#../../.. app/SmartTrader/SmartTraderQT
#../../../.. transactive/app/SmartTrader/SmartTraderQT
#../../../../.. TA_APP/transactive/app/SmartTrader/SmartTraderQT
#指定生成的应用程序放置的目录
#DESTDIR += ../../../../../bin/win32_nd
#指定生成的应用程序名
#TARGET = SmartTraderQT
#指定生成的应用程序放置的目录
#DESTDIR += ../../../../../bin/win32_nd