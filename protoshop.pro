TEMPLATE = app
TARGET = protoshop
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += lib/CImg/CImg.h \
           $$system(find src -name "*.hpp")
SOURCES += $$system(find src -name "*.cpp")

CONFIG += x11 thread c++11
OBJECTS_DIR = bin
