QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE = app
TARGET = protoshop
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS

# Input
<<<<<<< HEAD
HEADERS += $$system(find src -name "\*.hpp")

=======
HEADERS += $$system(find src -name "\*.hpp") \
    $$system(find src -name "\*.h")
>>>>>>> ab15867779192aff958407f992abf013801646ba
SOURCES += $$system(find src -name "\*.cpp")

CONFIG += x11 thread c++11
OBJECTS_DIR = bin
