// Bounce.ino
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2019 Yossi Mosbacher


#include <ClosedStepper.h>

// Define a stepper and the pins it will use
ClosedStepper stepper(2,3,AccelStepper::DRIVER,4,5); // Defaults to AccelStepper::DRIVER (driver) with pins: 4 - step, 5 - dir, 2 - encoder A, 3 encoder B

void setup()
{  
  stepper.setTarget(500);
  stepper.setMaxSpeed(600);
  stepper.setAcceleration(2000);
  stepper.setEncoderSPR(1600);
  stepper.setStepperSPR(800);
  stepper.getStepper()->setPinsInverted(true,true,false);
}

void loop()
{
    // If at the end of travel go to the other end
    if (!stepper.run())
      stepper.setTarget(-stepper.getTarget());
    
}