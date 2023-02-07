!OPENCV_PRI {
CONFIG += OPENCV_PRI

OPENCV_BUILD_DIR += "/usr/local/"
INCLUDEPATH *= $$clean_path("$$OPENCV_BUILD_DIR/include/opencv4")

LIBS += -L$$OPENCV_BUILD_DIR/lib
LIBS += -lopencv_core
LIBS += -lopencv_calib3d
LIBS += -lopencv_dnn
LIBS += -lopencv_features2d
LIBS += -lopencv_flann
LIBS += -lopencv_highgui
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_video


QMAKE_LFLAGS += "-Wl,-rpath,\'$$OPENCV_BUILD_DIR/lib\'"
QMAKE_CXXFLAGS *= -D_GLIBCXX_USE_CXX17_ABI=0

}
