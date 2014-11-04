/* 
 * File:   PersonRecognizer.h
 * Author: Eyal Arubas <EyalArubas at gmail>
 */

#ifndef PERSONRECOGNIZER_H
#define	PERSONRECOGNIZER_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <QString>

using namespace std;
using namespace cv;

class PersonRecognizer {
public:
    PersonRecognizer(const QString tranXml, int radius, int neighbors,
            int grid_x, int grid_y, double threshold);
    virtual ~PersonRecognizer();
    bool recognize(const Mat &face, double &confidence) const;
private:
    Ptr<FaceRecognizer> _model;
};

#endif	/* PERSONRECOGNIZER_H */

