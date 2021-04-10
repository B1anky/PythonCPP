QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += no_keywords # Python redefines some qt keywords

LIBS = D:/Python3-7-9/libs/python37.lib
INCLUDEPATH += D:/Python3-7-9/include

SOURCES += \
    PythonInterface.cpp \
    PythonInterpreter.cpp \
    main.cpp

HEADERS += \
    PythonInterface.h \
    PythonInterpreter.h

