#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "facelogger.h"
#include "facereader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<FaceLogger>("an.qt.FaceLogger", 1, 0, "FaceLogger");
    FaceLogger *m = new FaceLogger;
    engine.rootContext()->setContextProperty("FaceLogger", m);
    engine.addImageProvider(QLatin1String("FaceLogger"), m);

    qmlRegisterType<FaceLogger>("an.qt.FaceReader", 1, 0, "FaceReader");
    FaceReader *r = new FaceReader;
    engine.rootContext()->setContextProperty("FaceReader", r);
    engine.addImageProvider(QLatin1String("FaceReader"), r);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}


/** Includes: **/

//#include "defs.h"
//#include "FaceDetector.h"
//#include "PersonRecognizer.h"

//using namespace std;

//int main(int /*argc*/, char** /*argv*/) {

//    /** Initializations: **/

//    FaceDetector fd(string(CASCADE_PATH), DET_SCALE_FACTOR, DET_MIN_NEIGHBORS, DET_MIN_SIZE_RATIO, DET_MAX_SIZE_RATIO);
//    vector<Mat>  training_set;
//    vector<Rect> faces;
//    Mat          m;

//    VideoCapture m_videoCapture(IN_VID);
//    Mat inMat;
//    while(m_videoCapture.read(inMat)) {
//        //m_iImageWidth = inMat.cols;
//        //m_iImageHeight = inMat.rows;
//        Mat grayMat;
//        cvtColor(inMat, grayMat, COLOR_BGR2GRAY); // default opencv colors "BGR"
//        training_set.push_back(grayMat);
//    }

//    PersonRecognizer pr(training_set, LBPH_RADIUS, LBPH_NEIGHBORS, LBPH_GRID_X, LBPH_GRID_Y, LBPH_THRESHOLD);

//    /**********************/

//    m = imread( "C:\\Users\\vince_li\\Desktop\\6.jpg" );

//    //while (fr.getNext(m))
//    {
//        //detect faces in the image:
//        fd.findFacesInImage(m, faces);

//        bool has_match = false;
//        double match_conf = 0;

//        //analyze each detected face:
//        for (vector<Rect>::const_iterator face = faces.begin() ; face != faces.end() ; face++){
//            Scalar color = NO_MATCH_COLOR;
//            Mat face_img = m(*face);
//            double confidence = 0;
//            bool face_match = false;

//            //try to recognize the face:
//            if (pr.recognize(face_img, confidence)){
//                color = MATCH_COLOR;
//                has_match = true;
//                face_match = true;
//                match_conf = confidence;
//            }

//            Point center(face->x + face->width * 0.5, face->y + face->height * 0.5);
//            circle(m, center, FACE_RADIUS_RATIO * face->width, color, CIRCLE_THICKNESS, LINE_TYPE, 0);
//        }

//        //write some information on the frame:
//        putText(m, format("FPS: %d", 15), cvPoint(10, m.rows - 80),
//                FONT, 2, FONT_COLOR, 1, LINE_TYPE);
//        putText(m, format("Faces: %d", faces.size()), cvPoint(10, m.rows - 55),
//                FONT, 2, FONT_COLOR, 1, LINE_TYPE);
//        putText(m, format("Match: %s", has_match ? "True" : "False"), cvPoint(10, m.rows - 30),
//                FONT, 2, FONT_COLOR, 1, LINE_TYPE);
//        putText(m, format("Confidence: %f", has_match ? match_conf : 0), cvPoint(10, m.rows - 5),
//                FONT, 2, FONT_COLOR, 1, LINE_TYPE);
//        qDebug() << ("Faces: %d", faces.size()) << " " << has_match << " " << match_conf;

////        imshow("Output",m);
////        if ('x' == waitKey(100000)){
////            return 0;
////        }
//    }

//    return 0;
//}
