QT -= gui

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = TPlab2

SOURCES += \
    source/main.cpp \
    source/ClassUnit.cpp \
    source/MethodUnit.cpp

HEADERS += \
    source/Unit.h \
    source/ClassUnit.h \
    source/MethodUnit.h