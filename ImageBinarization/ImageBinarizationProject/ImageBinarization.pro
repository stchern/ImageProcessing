CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH *= $$clean_path($$PWD/../)
include($$PWD/../ImageBinarization/ImageBinarization.pri)

SOURCES += \
        $$PWD/main.cpp \

HEADERS +=

DISTFILES += \
    image.png
