#include </home/zach/ZACH/Stepper.h>

Stepper::Stepper()
{
    if(gpioInitialise() < 0)
        return; //Failed to initialise

    gpioSetMode(M1_STEP, PI_OUTPUT); 
    gpioSetMode(M1_DIR, PI_OUTPUT);

    gpioSetMode(M2_STEP, PI_OUTPUT);
    gpioSetMode(M2_DIR, PI_OUTPUT);

    gpioWrite(ENABLE, PI_HIGH);

    calibrate();
}

void Stepper::moveByMM(int a_mm, Direction a_dir)
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
        case 4:     //Diagonal-Right-Forwards
        {
            gpioWrite(M1_DIR, PI_LOW);
            gpioWrite(M2_DIR, PI_HIGH);
            break;
        }
        case 5:     //Diagonal-Right-Backwards
        {
            gpioWrite(M1_DIR, PI_HIGH);
            gpioWrite(M2_DIR, PI_LOW);
            break;
        }
        case 6:     //Diagonal-Left-Forwards
        {
            gpioWrite(M1_DIR, PI_LOW);
            gpioWrite(M2_DIR, PI_HIGH);
            break;
        }
        case 7:     //Diagonal-Left-Forwards
        {
            gpioWrite(M1_DIR, PI_HIGH);
            gpioWrite(M2_DIR, PI_LOW);
            break;
        }
    }

    int reqSteps = a_mm / distancePerStep;  // amount of steps required to travel desired distance
    gpioWrite(ENABLE, PI_LOW);
    if(a_dir <= 3)  // straight
    {
        for(int i = 0; i < reqSteps; i++)
        {
            gpioWrite(M1_STEP, PI_HIGH);
            gpioWrite(M2_STEP, PI_HIGH);
            time_sleep(0.0009);
            gpioWrite(M1_STEP, PI_LOW);
            gpioWrite(M2_STEP, PI_LOW);
            time_sleep(0.0009);
        }
    }
    else if(a_dir <= 5) // Diagonal Right
    {
        gpioWrite(M1_STEP, PI_HIGH);
        gpioWrite(M2_STEP, PI_LOW);
        time_sleep(0.0009);
        gpioWrite(M1_STEP, PI_LOW);
        gpioWrite(M2_STEP, PI_LOW);
        time_sleep(0.0009);
    }
    else    // Diagonal Left
    {
        gpioWrite(M1_STEP, PI_LOW);
        gpioWrite(M2_STEP, PI_HIGH);
        time_sleep(0.0009);
        gpioWrite(M1_STEP, PI_LOW);
        gpioWrite(M2_STEP, PI_LOW);
        time_sleep(0.0009);
    }
    gpioWrite(ENABLE, PI_HIGH);
}

void Stepper::calibrate()
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
    
    currPoint = Point(0,7);
}

void moveToPoint(Point aDesPoint)
{
    int xdiff = aDesPoint.x - currPoint.x;
    int ydiff = aDesPoint.y - currPoint.y;

    if(xdiff < 0)
        moveByMM(abs(xdiff)*fieldSize, Direction::Left);
    else if(xdiff > 0)
        moveByMM(abs(xdiff)*fieldSize, Direction::Right);

    if(ydiff < 0)
        moveByMM(abs(ydiff)*fieldSize, Direction::Backwards);
    else if(ydiff > 0)
        moveByMM(abs(ydiff)*fieldSize, Direction::Forwards);
}