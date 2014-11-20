#include "facelogger.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include "defs.h"
#include <stdio.h>

#define MAX_TRAIN_IMAGE_CNT 100

FaceLogger::FaceLogger(QObject *parent) :
    QObject(parent)
  , QQuickImageProvider(QQuickImageProvider::Image)
  , m_faceDetector(DET_SCALE_FACTOR, DET_MIN_NEIGHBORS, DET_MIN_SIZE, DET_MAX_SIZE)
  , m_videoCapture(NULL)
  , m_vecMatImages()
  , m_vecIntLabels()
{
}

FaceLogger::~FaceLogger()
{
    if(m_videoCapture) {
        if(m_videoCapture->isOpened()) {
            m_videoCapture->release();
        }
        delete m_videoCapture;
    }
}

void FaceLogger::setFaceSource(const QString& source)
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
QString FaceLogger::isValid() const
{
    return (m_videoCapture == NULL)? "" : QString(m_videoCapture->isOpened());
}
QString FaceLogger::isClosed() const
{
    return (m_videoCapture == NULL)? "" : QString(m_videoCapture->isOpened() == false);
}

void FaceLogger::close(const QString&) {
}

QImage FaceLogger::requestImage(const QString& /*id*/, QSize* /*size*/, const QSize& /*requestedSize*/)
{
    if(m_videoCapture == NULL || m_videoCapture->isOpened()==false)
    {
        return QImage();
    }
    Mat inMat;
    if(m_videoCapture->read(inMat) == false || (m_vecMatImages.size() >= MAX_TRAIN_IMAGE_CNT))
    {
        // end of reading
        m_videoCapture->release();
        delete m_videoCapture;
        m_videoCapture = NULL;

        Ptr<FaceRecognizer> m_pModel = createLBPHFaceRecognizer();
        m_pModel->train(m_vecMatImages, m_vecIntLabels);
        QString tempFile = FACE_LOG;
        QFile::remove(tempFile);
        qDebug() << "Save features to file: " <<tempFile.toUtf8().constData();
        m_pModel->save(tempFile.toUtf8().constData());
        m_pModel = NULL;

        m_vecMatImages.clear();
        m_vecIntLabels.clear();

        return QImage();
    }
    else {
        Mat grayMat;
        cvtColor(inMat, grayMat, COLOR_BGR2GRAY); // default opencv colors "BGR"
        vector<Rect> faces;
        m_faceDetector.findFacesInImage(inMat, faces);
        if(faces.size() == 1)
        {
            //draw rectangle
            rectangle(inMat, faces[0], Scalar(0,0,255));

            // save roi only
            Mat roi(grayMat, faces[0]);
            m_vecMatImages.push_back(roi);
            m_vecIntLabels.push_back(PERSON_LABEL);
        }
    }

    // put progress on image
    char buf[64] = {0};
    sprintf(buf, "Progrss: %d %%", (int)((double)m_vecMatImages.size() / MAX_TRAIN_IMAGE_CNT * 100));
    putText(inMat, buf, Point(10, 20), FONT, 1, FONT_COLOR, 1);

    switch ( inMat.type() )
    {
        case CV_8UC4:
        {
            return QImage( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
        }
        case CV_8UC3:
        {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
            return image.rgbSwapped();
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
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
            image.setColorTable( sColorTable );
            return image;
        }
        default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
    }

    return QImage();
}
