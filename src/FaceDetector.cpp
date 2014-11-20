/* 
 * File:   FaceDetector.cpp
 * Author: Eyal Arubas <EyalArubas at gmail>
 */

#include <vector>

#include "FaceDetector.h"
#include <QDebug>
#include <QFile>
#include <QDir>

FaceDetector::FaceDetector(
        double scaleFactor,
        int    minNeighbors,
        double minSize,
        double maxSize):
    _scaleFactor(scaleFactor), _minNeighbors(minNeighbors), _minSize(minSize, minSize), _maxSize(maxSize, maxSize){

    QFile faceXML(":/data/haarcascade_frontalface_default.xml");
    QFile tempXML( QDir::toNativeSeparators(QDir::tempPath() + QDir::separator() + "faceDetection.xml"));

    if(tempXML.exists())
    {
        tempXML.remove();
    }
    faceXML.copy(tempXML.fileName());
    if(tempXML.exists())
    {
        if( _cascade.load(tempXML.fileName().toStdString()) == false )
        {
            qDebug() << "load cascade template failed: " << tempXML.fileName();
        }
        else
        {
            qDebug() << "Load cascade template successed: " << tempXML.fileName();
        }
    }
    else
    {
        qDebug() << "face detection XML not found";
    }
}

FaceDetector::~FaceDetector() {}

void FaceDetector::findFacesInImage(const Mat &img, vector<Rect> &res) {
    Mat gray, equal;
    //convert the image to grayscale and normalize histogram:
    if(img.channels() == 3) {
        cvtColor(img, gray, CV_BGR2GRAY);
    }
    else {
        img.copyTo(gray);
    }
    equalizeHist(gray, equal);
    
    //clear the vector:
    res.clear();
    
    //detect faces:
    _cascade.detectMultiScale(equal, res, _scaleFactor, _minNeighbors, 0|CV_HAAR_SCALE_IMAGE, _minSize, _maxSize);

    //face_cascade.detectMultiScale( equal, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );
    //_cascade.detectMultiScale(tmp, res, _scaleFactor, _minNeighbors);
}
