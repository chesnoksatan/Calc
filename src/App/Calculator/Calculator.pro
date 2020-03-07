QT += qml quick quickcontrols2 widgets

include( ../../../common.pri )
include( ../../../app.pri )

SOURCES += main.cpp \
    Core.cpp \
    FormController/FormController.cpp \
    CalculatorController/CalculatorController.cpp

HEADERS += \
    Core.h \
    FormController/FormController.h \
    CalculatorController/CalculatorController.h

DISTFILES += \
    ../../../export/qml/main.qml \
    ../../../export/qml/ButtonCalculator.qml

LIBS += -lCalcLib$${LIB_SUFFIX}
