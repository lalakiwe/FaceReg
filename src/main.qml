import QtQuick 2.3
import QtQuick.Window 2.1
import QtQuick.Controls 1.2

Window {
    visible: true
    width: 640
    height: 480
    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

    Timer {
        id: faceLoggerTimer
        interval: 1
        repeat: true
        running: false
        onTriggered: {
            myImg.source = ""
            myImg.source = "image://facelogger"
        }
    }

    Timer {
        id: faceReaderTimer
        interval: 1
        repeat: true
        running: false
        onTriggered: {
            myImg.source = ""
            myImg.source = "image://facereader"
        }
    }

    Image {
        id: myImg
        cache: false
        anchors.fill: parent.fill
        anchors.verticalCenter:  parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        onStatusChanged:
            if(status == Image.Error) {
                FaceReader.close("");
                FaceLogger.close("");
                faceLoggerTimer.running = false;
                faceReaderTimer.running = false;
            }
    }

    Button {
        id: btnCamTrain;
        width: 64;
        height: 64;
        Image {
            source: "qrc:/data/Cam.png"
            anchors.fill: parent
            anchors.margins: 4
        }
        anchors.right: btnReg.left;
        anchors.bottom: parent.bottom;
        onClicked: {
            FaceReader.close("");
            FaceLogger.setFaceSource("0")
            faceLoggerTimer.running = true;
            faceReaderTimer.running = false;
        }
    }

    Button {
        id: btnReg;
        width: 64;
        height: 64;
        Image {
            source: "qrc:/data/Reg.png"
            anchors.fill: parent
            anchors.margins: 4
        }
        anchors.right: btnStop.left;
        anchors.bottom: parent.bottom;
        onClicked: {
            FaceLogger.close("");
            FaceReader.setFaceSource("0")
            faceLoggerTimer.running = false;
            faceReaderTimer.running = true;
        }
    }

    Button {
        id: btnStop;
        width: 64;
        height: 64;
        Image {
            source: "qrc:/data/Pause.png"
            anchors.fill: parent
            anchors.margins: 4
        }
        anchors.right: btnQuit.left;
        anchors.bottom: parent.bottom;
        onClicked: {
            FaceReader.close("");
            FaceLogger.close("");
            faceLoggerTimer.running = false;
            faceReaderTimer.running = false;
        }
    }

    Button {
        id: btnQuit;
        width: 64;
        height: 64;
        Image {
            source: "qrc:/data/Exit.png"
            anchors.fill: parent
            anchors.margins: 4
        }
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        onClicked: {
            Qt.quit();
        }
    }
}
