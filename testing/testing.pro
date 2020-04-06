QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_filetest.cpp \
    ../src/model.cpp

HEADERS += \
    ../src/model.h

RESOURCES +=
