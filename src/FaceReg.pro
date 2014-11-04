TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    facelogger.cpp \
    tmconnector.cpp \
    facereader.cpp \
    FaceDetector.cpp \
    PersonRecognizer.cpp \
    tmjsonobject.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    facelogger.h \
    tmconnector.h \
    facereader.h \
    defs.h \
    FaceDetector.h \
    PersonRecognizer.h \
    tmjsonobject.h
