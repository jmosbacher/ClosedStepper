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
    void setTarget(long target);
    long getTarget();
    bool run();
    void runContinuous();
    

  private:
    long _currentTarget;
    int _max_err;
    int _encoder_spr;
    int _stepper_spr;
    AccelStepper* _stepper;
    Encoder* _encoder;
    
};