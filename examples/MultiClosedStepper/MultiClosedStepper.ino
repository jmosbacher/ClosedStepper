// MultiClosedStepper.pde
// -*- mode: C++ -*-
// Use MultiClosedStepper class to manage multiple steppers and make them all move to 
// the same position at the same time for linear 2d (or 3d) motion.

#include <ClosedStepper.h>
#include <MultiClosedStepper.h>

// EG X-Y position bed driven by 2 steppers
ClosedStepper stepper1(2,4, ClosedStepper::DRIVER,5,6);
ClosedStepper stepper2(3,7 ClosedStepper::DRIVER, 8, 9);

// Up to 10 steppers can be handled as a group by MultiClosedStepper
MultiClosedStepper steppers;

void setup() {
  Serial.begin(9600);

  // Configure each stepper
  stepper1.setMaxSpeed(100);
  stepper2.setMaxSpeed(100);

  // Then give them to MultiClosedStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
}

void loop() {
  long positions[2] = {1000,50}; // Array of desired stepper positions

  steppers.setTarget(positions);
  steppers.runToTarget(); // Blocks until all are in position
  delay(1000);
  
  // Move to a different coordinate
  positions[0] = -100;
  positions[1] = 100;
  steppers.setTarget(positions);
  steppers.runToTarget(); // Blocks until all are in position
  delay(1000);
}
