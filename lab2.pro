
QT       += core gui
QT += core gui widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = lab2
TEMPLATE = app
CONFIG += c++17
CONFIG += warn_on


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    iconizedlineedit.cpp \
    ledindicator.cpp

HEADERS += \
    mainwindow.h \
    iconizedlineedit.h \
    ledindicator.h


RESOURCES += \
    resources.qrc





