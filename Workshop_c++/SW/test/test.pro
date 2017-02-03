TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    filter.cpp \
    touppercase.cpp \
    addlinenumber.cpp \
    filetansformer.cpp \
    contains.cpp \
    prettyfier.cpp

HEADERS += \
    filter.h \
    touppercase.h \
    addlinenumber.h \
    filetansformer.h \
    contains.h \
    prettyfier.h
