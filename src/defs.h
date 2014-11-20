/* 
 * File:   defs.h
 * Author: Eyal Arubas <EyalArubas at gmail>
 */

#ifndef DEFS_H
#define	DEFS_H

#define PERSON_LABEL 80486852 //some arbitrary label

#define FACE_TRAINNING_DATA  "face_trainnig_data"
#define FACE_LOG             (QDir::tempPath() + QDir::separator() + FACE_TRAINNING_DATA);

/** Inputs: **/
//#define IN_VID        "input_vid/031213_POTUS_ExportCouncil_HD.mp4"
#define IN_VID        "C:\\Users\\vince_li\\Downloads\\Vince2.avi"
#define TRAINING_LIST "obama_faces/list"

/** Colors, fonts, lines... **/
#define NO_MATCH_COLOR    Scalar(0,0,255) //red
#define MATCH_COLOR       Scalar(0,255,0) //green
#define FACE_RADIUS_RATIO 0.75
#define CIRCLE_THICKNESS  2.5
#define LINE_TYPE         CV_AA
#define FONT              FONT_HERSHEY_PLAIN
#define FONT_COLOR        Scalar(10,10,240)
#define THICKNESS_TITLE   1.9
#define SCALE_TITLE       1.9
#define POS_TITLE         cvPoint(10, 30)
#define THICKNESS_LINK    1.6
#define SCALE_LINK        1.3
#define POS_LINK          cvPoint(10, 55)

/** Face detector: **/
//#define DET_SCALE_FACTOR   1.01
//#define DET_MIN_NEIGHBORS  40
//#define DET_MIN_SIZE_RATIO 0.06
//#define DET_MAX_SIZE_RATIO 0.18
#define DET_SCALE_FACTOR   1.1
#define DET_MIN_NEIGHBORS  2
#define DET_MIN_SIZE 200
#define DET_MAX_SIZE 1000

/** LBPH face recognizer: **/
#define LBPH_RADIUS    3
#define LBPH_NEIGHBORS 8
#define LBPH_GRID_X    8
#define LBPH_GRID_Y    8
#define LBPH_THRESHOLD 180.0

#endif	/* DEFS_H */

