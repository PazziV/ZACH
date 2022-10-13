#include <iostream>
#include </home/zach/ZACH/Point.h>
#include <pigpio.h>

using namespace std;

#define stepsPerRotation
#define distancePerStep 0.2 //mm
#define distancePerRotation 40  //mm

#define fieldSize 35 //mm

#define M1_STEP 5     //Stepper 1 Step Pin
#define M1_DIR 6     //Stepper 1 Direction Pin
#define M2_STEP 13     //Stepper 2 Step Pin
#define M2_DIR 19     //Stepper 2 Direction Pin

#define LIMIT_X_LEFT 20  //left Limit Switch X-Axis (Letters)
#define LIMIT_X_RIGHT 21  //right Limit Switch X-Axis (Letters)
#define LIMIT_Y_UPPER 20  //upper Limit Switch Y-Axis (Numbers)
#define LIMIT_Y_LOWER 21  //lower Limit Switch Y-Axis (Numbers)

#define X_DISTANCE_TO_A1 30 //Distance in mm from left X-Axis limit switch to field A1
#define Y_DISTANCE_TO_A1 30 //Distance in mm from lower-left Y-Axis limit switch to field A1

enum Direction{
    Backwards = 0,
    Forwards,
    Left,
    Right
};

Point currPoint();

void moveByMM(int a_mm, Direction a_dir);
void moveTo(Point a_desPoint);
void calibrate();

int main()
{
    if(gpioInitialise() < 0)
        return 1; //Failed to initialise

    gpioSetMode(M1_STEP, PI_OUTPUT); 
    gpioSetMode(M1_DIR, PI_OUTPUT);

    gpioSetMode(M2_STEP, PI_OUTPUT);
    gpioSetMode(M2_DIR, PI_OUTPUT);

    calibrate();

    moveByMM(10, Direction::Forwards);

    return 1;
}

void moveByMM(int a_mm, Direction a_dir)
{
    switch(a_dir)
    {
        case 0:     //Backwards
        {
            gpioWrite(M1_DIR, PI_LOW);
            gpioWrite(M2_DIR, PI_HIGH);
            break;
        }
        case 1:     //Forwards
        {
            gpioWrite(M1_DIR, PI_HIGH);
            gpioWrite(M2_DIR, PI_LOW);
            break;
        }
        case 2:     //Left
        {
            gpioWrite(M1_DIR, PI_HIGH);
            gpioWrite(M2_DIR, PI_HIGH);
            break;
        }
        case 3:     //Right
        {
            gpioWrite(M1_DIR, PI_LOW);
            gpioWrite(M2_DIR, PI_LOW);
            break;
        }
    }

    int reqSteps = a_mm / distancePerStep;  // amount of steps required to travel desired distance
    for(int i = 0; i < reqSteps; i++)
    {
        gpioWrite(M1_STEP, PI_HIGH);
        gpioWrite(M2_STEP, PI_HIGH);
        time_sleep(0.001);
        gpioWrite(M1_STEP, PI_LOW);
        gpioWrite(M2_STEP, PI_LOW);
        time_sleep(0.001);
    }
}

void moveTo(Direction a_desPoint)
{
    
}

void calibrate()
{
    // move to lower-left corner until limit switches are triggered then move to closest field (A1)
    while(gpioRead(LIMIT_X_LEFT) == PI_LOW)
    {
        gpioWrite(M1_DIR, PI_HIGH);
        gpioWrite(M2_DIR, PI_HIGH);

        gpioWrite(M1_STEP, PI_HIGH);
        gpioWrite(M2_STEP, PI_HIGH);
        time_sleep(0.001);
        gpioWrite(M1_STEP, PI_LOW);
        gpioWrite(M2_STEP, PI_LOW);
        time_sleep(0.001);
    }

    while(gpioRead(LIMIT_Y_LOWER) == PI_LOW)
    {
        gpioWrite(M1_DIR, PI_LOW);
        gpioWrite(M2_DIR, PI_HIGH);

        gpioWrite(M1_STEP, PI_HIGH);
        gpioWrite(M2_STEP, PI_HIGH);
        time_sleep(0.001);
        gpioWrite(M1_STEP, PI_LOW);
        gpioWrite(M2_STEP, PI_LOW);
        time_sleep(0.001);
    }

    moveByMM(X_DISTANCE_TO_A1, Direction::Right);
    moveByMM(Y_DISTANCE_TO_A1, Direction::Forwards);

    Point point(0,7);
    currPoint = point;
}