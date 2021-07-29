QT -= gui

CONFIG += c++11 console
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

SOURCES += \
        main.cpp

INCLUDEPATH += $$PWD/../opencv/include
INCLUDEPATH += $$PWD/../opencv/include/core/include
INCLUDEPATH += $$PWD/../opencv/include/imgproc/include
INCLUDEPATH += $$PWD/../opencv/include/highgui/include
INCLUDEPATH += $$PWD/../opencv/include/imgcodecs/include
INCLUDEPATH += $$PWD/../opencv/include/features2d/include
INCLUDEPATH += $$PWD/../opencv/include/video/include
INCLUDEPATH += $$PWD/../opencv/include/videoio/include

DEPENDPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include/core/include
DEPENDPATH += $$PWD/../opencv/include/imgproc/include
DEPENDPATH += $$PWD/../opencv/include/highgui/include
DEPENDPATH += $$PWD/../opencv/include/imgcodecs/include
DEPENDPATH += $$PWD/../opencv/include/features2d/include
DEPENDPATH += $$PWD/../opencv/include/video/include
DEPENDPATH += $$PWD/../opencv/include/videoio/include

DEPENDPATH += $$PWD/../opencv/include
LIBS += -L$$PWD/../opencv/lib

LIBS += -L$$PWD/../opencv/lib \
        libopencv_core411 \
        libopencv_imgcodecs411 \
        libopencv_imgproc411 \
        libopencv_highgui411 \
