QT -= gui

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = TPlab2

SOURCES += \
    source/main.cpp \
    source/ClassUnit.cpp \
    source/MethodUnit.cpp \
    source/PrintOperatorUnit.cpp

HEADERS += \
    source/Unit.h \
    source/Modifiers.h \
    source/ClassUnit.h \
    source/MethodUnit.h \
    source/PrintOperatorUnit.h