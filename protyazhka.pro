#-------------------------------------------------
#
# Project created by QtCreator 2018-11-01T11:20:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = protyazhka
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    stockforma.cpp \
    mainmenuforma.cpp \
    exitforma.cpp \
    myqsqlquerymodel.cpp \
    stockinforma.cpp \
    stockoutforma.cpp \
    costmenuforma.cpp \
    coststockforma.cpp \
    costworkforma.cpp

HEADERS += \
        mainwindow.h \
    stockforma.h \
    mainmenuforma.h \
    exitforma.h \
    myqsqlquerymodel.h \
    stockinforma.h \
    stockoutforma.h \
    costmenuforma.h \
    coststockforma.h \
    costworkforma.h

FORMS += \
        mainwindow.ui \
    stockforma.ui \
    mainmenuforma.ui \
    exitforma.ui \
    stockinforma.ui \
    stockoutforma.ui \
    costmenuforma.ui \
    coststockforma.ui \
    costworkforma.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
