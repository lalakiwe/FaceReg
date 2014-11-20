#CONFIG += silent         # build in silent mode
CONFIG += release        # build in release mode
#CONFIG += warn_on        # enable compiler warnning
CONFIG -= debug          # disable build in debug mode
#CONFIG -= exceptions     # disable exceptions support
#CONFIG += console       # enable console output
CONFIG += C++0x

QMAKE_CXXFLAGS -= -O1 -O2
QMAKE_CXXFLAGS += -O3 -Wall
QMAKE_CFLAGS -= -O1 -O2
QMAKE_CFLAGS += -O3 -Wall

android-no-sdk {
    target.path = /data/user/qt
    export(target.path)
    INSTALLS += target
} else:android {
    x86 {
        target.path = /libs/x86
    } else: armeabi-v7a {
        target.path = /libs/armeabi-v7a
    } else {
        target.path = /libs/armeabi
    }
    export(target.path)
    INSTALLS += target
} else:unix {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += /usr/local/include/opencv2
    INCLUDEPATH += /usr/local/include/opencv

    LIBS += -L/usr/local/lib
    LIBS += -lopencv_highgui \
            -lopencv_imgproc \
            -lopencv_core  \
            -lopencv_objdetect \
            -lopencv_features2d \
            -lopencv_contrib

    INSTALLS += target
} else:win32 {
    INCLUDEPATH += C:\Qt\opencv-2.4.10\build\include\
    INCLUDEPATH += C:\Qt\opencv-2.4.10\build\include\opencv2\
    INCLUDEPATH += C:\Qt\opencv-2.4.10\build\include\opencv\

    !contains(QMAKE_TARGET.arch, x86_64) {
	LIBS += -LC:\Qt\opencv-2.4.10\build\x86\vc11\lib
    } else {
	LIBS += -LC:\Qt\opencv-2.4.10\build\x64\vc11\lib
    }
    LIBS += -lopencv_highgui2410 \
	    -lopencv_imgproc2410 \
	    -lopencv_core2410  \
	    -lopencv_objdetect2410 \
	    -lopencv_features2d2410 \
	    -lopencv_contrib2410

    isEmpty(target.path) {
	target.path = C:\$${TARGET}/bin
	export(target.path)
    }
    INSTALLS += target
}

export(INSTALLS)
