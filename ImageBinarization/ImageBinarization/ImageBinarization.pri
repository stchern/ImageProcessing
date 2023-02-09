!IMAGE_BINARIZATION_PRI{
CONFIG += IMAGE_BINARIZATION_PRI

INCLUDEPATH *= $$clean_path($$PWD/../)
include($$PWD/../../OpenCV.pri)

HEADERS += \
    $$PWD/globalbinarization.h \
    $$PWD/localbinarization.h


SOURCES += \
    $$PWD/globalbinarization.cpp \
    $$PWD/localbinarization.cpp
}
