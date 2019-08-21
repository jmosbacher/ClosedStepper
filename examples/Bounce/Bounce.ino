// Bounce.ino
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2019 Yossi Mosbacher


#include <ClosedStepper.h>

// Define a stepper and the pins it will use
ClosedStepper stepper; // Defaults to AccelStepper::DRIVER (driver) on 4 - step, 5 - dir, 2 - encoder A, 3 encoder B

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(20);
  stepper.setTarget(500);
}

void loop()
{
    // If at the end of travel go to the other end
    if (!stepper.run())
      stepper.setTarget(-stepper.getTarget());
    
}
