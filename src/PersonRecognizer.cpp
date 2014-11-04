/* 
 * File:   PersonRecognizer.cpp
 * Author: Eyal Arubas <EyalArubas at gmail>
 */

#include "PersonRecognizer.h"
#include "defs.h"
#include <QDebug>

PersonRecognizer::PersonRecognizer(const QString tranXml, int radius, int neighbors,
        int grid_x, int grid_y, double threshold) : _model(NULL) {
    //all images are faces of the same person, so initialize the same label for all.

    //build recognizer model:
    _model = createLBPHFaceRecognizer(radius, neighbors, grid_x, grid_y, threshold);
    _model->load(tranXml.toUtf8().constData());
}

PersonRecognizer::~PersonRecognizer() {}

bool PersonRecognizer::recognize(const Mat &face, double &confidence) const {
    Mat gray;
    int label = -1;

    if(face.channels() == 3)
    {
        cvtColor(face, gray, CV_BGR2GRAY);
    }
    else
    {
        gray = face.clone();
    }
    resize(gray, gray, face.size());
    _model->predict(gray, label, confidence);
    return label == PERSON_LABEL ? true : false;
}
