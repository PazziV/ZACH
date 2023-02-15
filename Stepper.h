#ifndef STEPPER_H
#define STEPPER_H

#include <iostream>
#include </home/zach/ZACH/Point.h>
#include <pigpio.h>

using namespace std;

#define stepsPerRotation
#define distancePerStep 0.2 //mm
#define distancePerRotation 40  //mm

#define diagonalDistancePerStep 0.1424 //mm

#define fieldSize 50 //mm

#define X_DISTANCE_TO_A1 48 //Distance in mm from left X-Axis limit switch to field A1
#define Y_DISTANCE_TO_A1 5 //Distance in mm from lower-left Y-Axis limit switch to field A1

#define M1_STEP 5     //Stepper 1 Step Pin
#define M1_DIR 6     //Stepper 1 Direction Pin
#define M2_STEP 13     //Stepper 2 Step Pin
#define M2_DIR 19     //Stepper 2 Direction Pin

#define ENABLE 26   //HIGH => Input off; LOW => Input on

#define LIMIT_X_LEFT 20  //left Limit Switch X-Axis (Letters)
#define LIMIT_Y_LOWER 16  //lower Limit Switch Y-Axis (Numbers)

#define MAGNET_PIN 21

enum Direction{
    Backwards = 0,
    Forwards,
    Left,
    Right,
    DiagonalRF, //Diagonal-Right-Forwards
    DiagonalLB, //Diagonal-Left-Backwards
    DiagonalLF, //Diagonal-Left-Forwards
    DiagonalRB  //Diagonal-Right-Backwards
};

class Stepper
{
    public:
        Point currPoint;

        Stepper();
        void moveByMM(float a_mm, Direction a_dir);
        void calibrate();
        void moveToPoint(Point aDesPoint);
        void stepperTest();
        void stepperTest2();
};
#endif