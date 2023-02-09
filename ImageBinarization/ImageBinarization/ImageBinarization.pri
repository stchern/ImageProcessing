!IMAGE_BINARIZATION_PRI{
CONFIG += IMAGE_BINARIZATION_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)
include($$PWD/../../OpenCV.pri)

HEADERS += \
    $$PWD/globalbinarization.h \

SOURCES += \
    $$PWD/globalbinarization.cpp \
}

HEADERS += \
    $$PWD/localbinarization.h

SOURCES += \
    $$PWD/localbinarization.cpp
