#ifndef ___ClosedStepper__H___
#define ___ClosedStepper__H___

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#endif  // #ifndef ___ClosedStepper__H___

#include <Encoder.h>
#include <AccelStepper.h>

class ClosedStepper : public AccelStepper
{
public:
    ClosedStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 4, uint8_t pin2 =5 , uint8_t pin3 = 6, uint8_t pin4 = 7, bool enable = true, uint8_t encoderPinA = 2, uint8_t encoderPinB = 3, float stepRatio = 1f);
    ClosedStepper(void (*forward)(), void (*backward)(), long (*realPosition)());

private:
    long (*_realPosition)();
    long _nextStep;
    long _failedSteps
    Encoder _encoder;

}