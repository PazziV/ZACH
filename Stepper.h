#include <iostream>
#include </home/zach/ZACH/Point.h>
#include <pigpio.h>

using namespace std;

#define stepsPerRotation
#define distancePerStep 0.2 //mm
#define distancePerRotation 40  //mm

#define fieldSize 45 //mm

#define M1_STEP 5     //Stepper 1 Step Pin
#define M1_DIR 6     //Stepper 1 Direction Pin
#define M2_STEP 13     //Stepper 2 Step Pin
#define M2_DIR 19     //Stepper 2 Direction Pin

#define LIMIT_X_LEFT 20  //left Limit Switch X-Axis (Letters)
#define LIMIT_X_RIGHT 21  //right Limit Switch X-Axis (Letters)
#define LIMIT_Y_UPPER 12  //upper Limit Switch Y-Axis (Numbers)
#define LIMIT_Y_LOWER 16  //lower Limit Switch Y-Axis (Numbers)

#define ENABLE 26   //HIGH => Input off; LOW => Input on

#define X_DISTANCE_TO_A1 43 //Distance in mm from left X-Axis limit switch to field A1
#define Y_DISTANCE_TO_A1 10 //Distance in mm from lower-left Y-Axis limit switch to field A1

enum Direction{
    Backwards = 0,
    Forwards,
    Left,
    Right,
    DiagonalRF, //Diagonal-Right-Forwards
    DiagonalRB, //Diagonal-Right-Backwards
    DiagonalLF, //Diagonal-Left-Forwards
    DiagonalLB  //Diagonal-Left-Backwards
};

class Stepper
{
    public:
        Point currPoint;

        Stepper();
        void moveByMM(int a_mm, Direction a_dir);
        void calibrate();
        void moveToPoint(Point aDesPoint);
};