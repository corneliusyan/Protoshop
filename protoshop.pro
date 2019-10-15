TEMPLATE = app
TARGET = protoshop
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += lib/CImg/CImg.h \
           $$system(find src -name "*.hpp")
SOURCES += $$system(find src -name "*.cpp") \
    src/adjustment/brighten.cpp \
    src/adjustment/flip.cpp \
    src/adjustment/grayscaling.cpp \
    src/adjustment/inverse.cpp \
    src/adjustment/rotate.cpp \
    src/adjustment/translate.cpp \
    src/adjustment/zoom.cpp \
    src/image/b_w.cpp \
    src/image/base.cpp \
    src/image/grayscale.cpp \
    src/image/pixel.cpp \
    src/image/r_g_b.cpp \
    src/main.cpp \
    src/ui/imageviewer.cpp \
    src/utils/reader.cpp \
    src/utils/string.cpp

CONFIG += x11 thread c++11
OBJECTS_DIR = bin
QT += widgets printsupport
