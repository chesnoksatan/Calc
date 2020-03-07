QT += qml quick quickcontrols2 widgets

include( ../../../common.pri )
include( ../../../app.pri )

CONFIG += c++11
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Core.cpp \
    FormController/FormController.cpp \
    CalculatorController/CalculatorController.cpp

HEADERS += \
    Core.h \
    FormController/FormController.h \
    CalculatorController/CalculatorController.h

#RESOURCES += \
    #./export/qml/qml.qrc \
 #   ../../../export/qml/qml.qrc

DISTFILES += \
    ../../../export/qml/main.qml \
    ../../../export/qml/ButtonCalculator.qml

LIBS += -lCalcLib
