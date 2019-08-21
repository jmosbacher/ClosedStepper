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
    if (_num_steppers >= MULTISTEPPER_MAX_STEPPERS)
	return false; // No room for more
    _steppers[_num_steppers++] = &stepper;
    return true;
}


