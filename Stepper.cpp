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

}

void Stepper::stepperTest()
{
    moveByMM(45, Direction::Forwards);
    moveByMM(45, Direction::Backwards);
}
void Stepper::stepperTest2()
{
    moveByMM(45, Direction::Forwards);
    moveByMM(45, Direction::Left);
    moveByMM(45, Direction::Backwards);
    moveByMM(45, Direction::Right);
}

void Stepper::moveByMM(float a_mm, Direction a_dir)
{
    switch(a_dir)
    {
        case 0:     //Backwards
        {
            gpioWrite(M1_DIR, PI_HIGH);
            gpioWrite(M2_DIR, PI_LOW);
            break;
        }
        case 1:     //Forwards
        {
            gpioWrite(M1_DIR, PI_LOW);
            gpioWrite(M2_DIR, PI_HIGH);
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
        case 4:     //Diagonal-Left-Forwards
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
        case 6:     //Diagonal-Right-Forwards
        {
            gpioWrite(M1_DIR, PI_LOW);
            gpioWrite(M2_DIR, PI_HIGH);
            break;
        }
        case 7:     //Diagonal-Left-Backwards
        {
            gpioWrite(M1_DIR, PI_HIGH);
            gpioWrite(M2_DIR, PI_LOW);
            break;
        }
    }

    gpioWrite(ENABLE, PI_LOW);
    if(a_dir <= 3)  // straight
    {
        int reqSteps = a_mm / distancePerStep;  // amount of steps required to travel desired distance
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
    else if(a_dir == 4 || a_dir == 5) // Diagonal Right
    {
        int reqSteps = a_mm / diagonalDistancePerStep;
        for(int i = 0; i < reqSteps; i++)
        {
            gpioWrite(M1_STEP, PI_HIGH);
            gpioWrite(M2_STEP, PI_LOW);
            time_sleep(0.0009);
            gpioWrite(M1_STEP, PI_LOW);
            gpioWrite(M2_STEP, PI_LOW);
            time_sleep(0.0009);
        }
    }
    else    // Diagonal Left
    {
        int reqSteps = a_mm / diagonalDistancePerStep;
        for(int i = 0; i < reqSteps; i++)
        {
            gpioWrite(M1_STEP, PI_LOW);
            gpioWrite(M2_STEP, PI_HIGH);
            time_sleep(0.0009);
            gpioWrite(M1_STEP, PI_LOW);
            gpioWrite(M2_STEP, PI_LOW);
            time_sleep(0.0009);
        }
    }
    gpioWrite(ENABLE, PI_HIGH);
}

void Stepper::calibrate()
{
    //move to lower-left corner until limit switches are triggered then move to closest field (A1)
    while(gpioRead(LIMIT_X_LEFT) == PI_HIGH)
    {
        moveByMM(distancePerStep, Direction::Left);
    }

    while(gpioRead(LIMIT_Y_LOWER) == PI_HIGH)
    {
        moveByMM(distancePerStep, Direction::Backwards);
    }

    moveByMM(X_DISTANCE_TO_A1, Direction::Right);
    moveByMM(Y_DISTANCE_TO_A1, Direction::Forwards);
    
    currPoint = Point(0,7);
}

void Stepper::moveToPoint(Point aDesPoint)
{
    if(aDesPoint != currPoint)
    {
        int xdiff = aDesPoint.x - currPoint.x;
        int ydiff = aDesPoint.y - currPoint.y;

        if(xdiff < 0)
            moveByMM(abs(xdiff)*fieldSize, Direction::Left);
        else if(xdiff > 0)
            moveByMM(abs(xdiff)*fieldSize, Direction::Right);

        if(ydiff < 0)
            moveByMM(abs(ydiff)*fieldSize, Direction::Forwards);
        else if(ydiff > 0)
            moveByMM(abs(ydiff)*fieldSize, Direction::Backwards);
        
        currPoint = aDesPoint;
    }
}