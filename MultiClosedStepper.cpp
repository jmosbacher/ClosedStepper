// MultiClosedStepper.cpp
//
// Copyright (C) 2019 Yossi Mosbacher


#include "MultiClosedStepper.h"
#include "ClosedStepper.h"

MultiClosedStepper::MultiClosedStepper() 
{
    _num_steppers = 0;
}

boolean MultiClosedStepper::addStepper(ClosedStepper& stepper)
{
    if (_num_steppers >= CLOSEDSTEPPER_MAX_STEPPERS)
	return false; // No room for more
    _steppers[_num_steppers++] = &stepper;
    return true;
}


void MultiClosedStepper::setTarget(long target[])
{
    // First find the stepper that will take the longest time to move
    float longestTime = 0.0;

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
	long thisDistance = target[i] - _steppers[i]->getCurrentPosition();
	float thisTime = abs(thisDistance) / _steppers[i]->getStepper()->maxSpeed();

	if (thisTime > longestTime)
	    longestTime = thisTime;
    }

    if (longestTime > 0.0)
    {
	// Now work out a new max speed for each stepper so they will all 
	// arrived at the same time of longestTime
	for (i = 0; i < _num_steppers; i++)
	{
	    long thisDistance = target[i] - _steppers[i]->getCurrentPosition();
	    float thisSpeed = thisDistance / longestTime;
	    _steppers[i]->setTarget(target[i]); // New target position (resets speed)
	    _steppers[i]->getStepper()->setSpeed(thisSpeed); // New speed
	}
    }
}

// Returns true if any motor is still running to the target position.
boolean MultiClosedStepper::run()
{
    uint8_t i;
    boolean ret = false;
    for (i = 0; i < _num_steppers; i++)
    {
	    if (_steppers[i]->runConstSpeed());
	    ret = true;
    }
    return ret;
}

// Blocks until all steppers reach their target position and are stopped
void    MultiClosedStepper::runToTarget()
{
    while (run());
}
