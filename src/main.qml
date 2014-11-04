import QtQuick 2.3
import QtQuick.Window 2.1
import QtQuick.Controls 1.2

Window {
    visible: true
    width: 640
    height: 480

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

//    Button {
//        id: btnFileTrain;
//        width: 92;
//        Text {
//            anchors.centerIn: parent;
//            font.family: "微軟正黑體";
//            font.pointSize: 13;
//            font.bold: true;
//            text: "File Train"
//        }
//        anchors.left: parent.left;
//        anchors.bottom: parent.bottom;
//        onClicked: {
//            FaceLogger.setFaceSource("C:\\Users\\vince_li\\Downloads\\Vince2.avi")
//            faceLoggerTimer.running = true;
//        }
//    }

    Button {
        id: btnCamTrain;
        width: 92;
        Text {
            anchors.centerIn: parent;
            font.family: "微軟正黑體";
            font.pointSize: 13;
            font.bold: true;
            text: "Cam Train"
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
        Text {
            anchors.centerIn: parent;
            font.family: "微軟正黑體";
            font.pointSize: 13;
            font.bold: true;
            text: "辨識"
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
        Text {
            anchors.centerIn: parent;
            font.family: "微軟正黑體";
            font.pointSize: 13;
            font.bold: true;
            text: "停止"
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
        Text {
            anchors.centerIn: parent;
            font.family: "微軟正黑體";
            font.pointSize: 13;
            font.bold: true;
            text: "離開"
        }
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        onClicked: {
            Qt.quit();
        }
    }
}
