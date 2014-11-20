#ifndef COLORMAKER_H
#define COLORMAKER_H

#include <QObject>
#include <QImage>
#include <QQuickImageProvider>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/contrib/contrib.hpp>

#include "FaceDetector.h"

using namespace cv;

class FaceLogger : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    Q_PROPERTY(QString isValid READ isValid WRITE setFaceSource)
    Q_PROPERTY(QString isClosed READ isClosed WRITE close)

public:
    explicit FaceLogger(QObject *parent = 0);
    ~FaceLogger();

    QQuickImageProvider::ImageType imageType() const { return QQuickImageProvider::Image; }
    QImage requestImage(const QString& /*id*/, QSize* /*size*/, const QSize& /*requestedSize*/);

    Q_INVOKABLE void setFaceSource(const QString& source);
    QString isValid() const;
    QString isClosed() const;
    Q_INVOKABLE void close(const QString& = QString());

private:
    FaceDetector m_faceDetector;
    VideoCapture* m_videoCapture;
    vector<Mat> m_vecMatImages;
    vector<int> m_vecIntLabels;
};

#endif // COLORMAKER_H
