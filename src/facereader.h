#ifndef FACEREADER2_H
#define FACEREADER2_H


#include <QObject>
#include <QQuickImageProvider>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/contrib/contrib.hpp>

#include "FaceDetector.h"
#include "PersonRecognizer.h"

using namespace cv;

class FaceReader : public QObject, public QQuickImageProvider
{
    Q_OBJECT

    Q_PROPERTY(QString isValid READ isValid WRITE setFaceSource)
    Q_PROPERTY(QString isClosed READ isClosed WRITE close)

public:
    explicit FaceReader(QObject *parent = 0);
    ~FaceReader();

    QQuickImageProvider::ImageType imageType() const { return QQuickImageProvider::Image; }
    QImage requestImage(const QString& /*id*/, QSize* /*size*/, const QSize& /*requestedSize*/);
    double facePredict(Mat& m, QImage& qimage);

    Q_INVOKABLE void setFaceSource(const QString& source);
    QString isValid() const;
    QString isClosed() const;
    Q_INVOKABLE void close(const QString& = QString());

signals:

public slots:

private:
    FaceDetector m_faceDetector;
    VideoCapture* m_videoCapture;
    vector<Mat> m_vecMatImages;
    vector<int> m_vecIntLabels;
    QImage  m_qimage;
    PersonRecognizer* m_pPersonRecognizer;
};

#endif // FACEREADER2_H
