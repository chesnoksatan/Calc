include( ../../../common.pri )
include( ../../../lib.pri )

QT       += widgets

TARGET = CalcLib$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += CALCLIB_LIBRARY

SOURCES += \
        CalcLib.cpp

HEADERS += \
        ../../include/CalcLib.h \
        ../../include/calclib_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    QMAKE_TARGET_PRODUCT = Calc Lib
    QMAKE_TARGET_DESCRIPTION = Library for calculating the simplest mathematical operations
}
