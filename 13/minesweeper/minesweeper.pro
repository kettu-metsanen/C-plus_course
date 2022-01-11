TEMPLATE = app
CONFIG += console c++14 warn_on
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    gameboard.cpp \
    square.cpp

HEADERS += \
    gameboard.hh \
    square.hh

QMAKE_CXXFLAGS += -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
