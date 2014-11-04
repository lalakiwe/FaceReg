#include "facereader.h"
#include <QDebug>
#include <QDir>
#include "defs.h"


#define MAX_TRAIN_IMAGE_CNT 100

FaceReader::FaceReader(QObject *parent) :
    QObject(parent)
  , QQuickImageProvider(QQuickImageProvider::Image)
  , m_faceDetector(DET_SCALE_FACTOR, DET_MIN_NEIGHBORS, DET_MIN_SIZE, DET_MAX_SIZE)
  , m_videoCapture(NULL)
  , m_vecMatImages()
  , m_vecIntLabels()
  , m_pPersonRecognizer(NULL)
{
}

FaceReader::~FaceReader()
{
    if(m_pPersonRecognizer) {
        delete m_pPersonRecognizer;
        m_pPersonRecognizer = NULL;
    }

    if(m_videoCapture) {
        if(m_videoCapture->isOpened()) {
            m_videoCapture->release();
        }
        delete m_videoCapture;
    }
}

void FaceReader::setFaceSource(const QString& source)
{
    if(m_videoCapture) {
        if(m_videoCapture->isOpened()) {
            m_videoCapture->release();
        }
        delete m_videoCapture;
        m_videoCapture = NULL;
    }

    if(source == "0" || source == "1" || source == "2")
    {
        if(m_videoCapture == NULL) {
            m_videoCapture = new VideoCapture(source.toInt());
        }
    }
    else
    {
        if(m_videoCapture == NULL) {
            m_videoCapture = new VideoCapture(source.toUtf8().constData());
        }
    }
}
QString FaceReader::isValid() const
{
    return (m_videoCapture == NULL)? "" : QString(m_videoCapture->isOpened());
}
QString FaceReader::isClosed() const
{
    return (m_videoCapture == NULL)? "" : QString(m_videoCapture->isOpened() == false);
}

void FaceReader::close(const QString&) {
}

QImage FaceReader::requestImage(const QString& /*id*/, QSize* /*size*/, const QSize& /*requestedSize*/)
{
    QImage qimage;
    Mat inMat;

    if((m_videoCapture == NULL)|| m_videoCapture->isOpened()==false)
    {

    }
    else if(m_videoCapture->read(inMat) == false)
    {
        // end of reading
        m_videoCapture->release();
        delete m_videoCapture;
        m_videoCapture = NULL;
    }
    else
    {
        facePredict(inMat, qimage);
    }

    return qimage;
}


double FaceReader::facePredict(Mat& m, QImage& qimage)
{
    if(m.empty())
    {
        qWarning() << "empty mat";
        return 0;
    }

    Mat grayMat;
    cvtColor(m, grayMat, COLOR_BGR2GRAY); // default opencv colors "BGR"

    //detect faces in the image:
    vector<Rect> faces;
    m_faceDetector.findFacesInImage(grayMat, faces);

    bool has_match = false;
    double match = 0;
    if(m_pPersonRecognizer == NULL) {
        QString faceXmlFile = FACE_LOG;
        m_pPersonRecognizer = new PersonRecognizer(faceXmlFile, LBPH_RADIUS, LBPH_NEIGHBORS, LBPH_GRID_X, LBPH_GRID_Y, LBPH_THRESHOLD);
    }

    //analyze each detected face:
    for (vector<Rect>::const_iterator face = faces.begin() ; face != faces.end() ; face++) {
        Mat face_img = grayMat(*face);
        double confidence = 0;

        //try to recognize the face in roi
        if (m_pPersonRecognizer->recognize(face_img, confidence)){
            has_match = true;
            match = confidence;
        }
        else {
            confidence = 0;
        }
        Scalar color = ( confidence > 20 ) ? MATCH_COLOR : NO_MATCH_COLOR;

        Point center(face->x + face->width * 0.5, face->y + face->height * 0.5);
        circle(m, center, FACE_RADIUS_RATIO * face->width, color, CIRCLE_THICKNESS, LINE_TYPE, 0);
    }

    if(faces.empty() == false) {
        //write some information on the frame:
        putText(m, format("Match: %s", has_match ? "True" : "False"), cvPoint(10, m.rows - 30),
                FONT, 1, FONT_COLOR, 1, LINE_TYPE);
    }
    else {
        putText(m, format("Match: %s", "None"), cvPoint(10, m.rows - 30), FONT, 1, FONT_COLOR, 1, LINE_TYPE);
    }
    putText(m, format("Confidence: %d", has_match ? (int)match : 0), cvPoint(10, m.rows - 5), FONT, 1, FONT_COLOR, 1, LINE_TYPE);



    switch ( m.type() )
    {
        case CV_8UC4:
        {
            qimage = QImage( m.data, m.cols, m.rows, m.step, QImage::Format_RGB32 );
            break;
        }
        case CV_8UC3:
        {
            QImage image( m.data, m.cols, m.rows, m.step, QImage::Format_RGB888 );
            qimage = image.rgbSwapped();
            break;
        }
        case CV_8UC1:
        {
            static QVector<QRgb>  sColorTable;
            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
                for ( int i = 0; i < 256; ++i )
                    sColorTable.push_back( qRgb( i, i, i ) );
            }
            QImage image( m.data, m.cols, m.rows, m.step, QImage::Format_Indexed8 );
            image.setColorTable( sColorTable );
            qimage = image;
            break;
        }
        default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << m.type();
            break;
    }

    return match;
}
