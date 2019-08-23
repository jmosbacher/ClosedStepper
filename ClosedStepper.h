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

class Encoder;

class ClosedStepper {
  public:
    ~ClosedStepper();
    ClosedStepper(uint8_t enc_pin1=2, uint8_t enc_pin2=3, uint8_t interface = AccelStepper::DRIVER, uint8_t pin1 = 4, uint8_t pin2 = 5 , uint8_t pin3 = 6, uint8_t pin4 = 7, bool enable = true);
    ClosedStepper(Encoder *encoder, AccelStepper *stepper);
    void init();
    void setTarget(long target);
    long getTarget();

    long getCurrentPosition();
    void setCurrentPosition(long position);

    int getTolerance();
    void setTolerance(int tolerance);

    int getEncoderSPR();
    void setEncoderSPR(int spr);

    int getStepperSPR();
    void setStepperSPR(int spr);

    AccelStepper* getStepper();
    Encoder* getEncoder();

    bool run();
    void runToTarget();
    bool runConstSpeed();

  private:
    long _currentTarget;
    int _maxError = 2;
    int _encoderSpr = 400;
    int _stepperSpr = 200;
    long _nmissed = 0;
    AccelStepper* _stepper;
    Encoder* _encoder;
    
};