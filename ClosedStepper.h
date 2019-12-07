#ifndef ___ClosedStepper__H___
#define ___ClosedStepper__H___

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#endif  // #ifndef ___ClosedStepper__H___

#include <Encoder.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

#include <AccelStepper.h>

class Encoder;

class ClosedStepper {
  public:
      typedef enum
      {
      FUNCTION  = 0, ///< Use the functional interface, implementing your own driver functions (internal use only)
      DRIVER    = 1, ///< Stepper Driver, 2 driver pins required
      FULL2WIRE = 2, ///< 2 wire stepper, 2 motor pins required
      FULL3WIRE = 3, ///< 3 wire stepper, such as HDD spindle, 3 motor pins required
      FULL4WIRE = 4, ///< 4 wire full stepper, 4 motor pins required
      HALF3WIRE = 6, ///< 3 wire half stepper, such as HDD spindle, 3 motor pins required
      HALF4WIRE = 8  ///< 4 wire half stepper, 4 motor pins required
      } MotorInterfaceType;

    ~ClosedStepper();
    ClosedStepper(uint8_t enc_pin1=2, uint8_t enc_pin2=3, uint8_t interface = AccelStepper::DRIVER, uint8_t pin1 = 4, uint8_t pin2 = 5 , uint8_t pin3 = 6, uint8_t pin4 = 7, bool enable = true);
    ClosedStepper(Encoder *encoder, AccelStepper *stepper);
    void init();
    void setTarget(long target);
    long getTarget();

    long distanceToGo();

    long getCurrentPosition();
    void setCurrentPosition(long position);

    float getMaxSpeed();
    void setMaxSpeed(float speed);

    void setAcceleration(float accel);

    long getTolerance();
    void setTolerance(long tolerance);

    long getEncoderSPR();
    void setEncoderSPR(long spr);

    long getStepperSPR();
    void setStepperSPR(long spr);

    AccelStepper* getStepper();
    Encoder* getEncoder();

    bool run();
    bool success();
    void runToTarget();
    bool runConstSpeed();
    void stop();
    void closeLoop();
    
  private:
    long _currentTarget = 0;
    long _maxError = 2;
    long _stepCount = 0;
    long _testInterval = 100;
    long _encoderSpr = 400;
    long _stepperSpr = 200;
    bool _failed = false;
    long _nmissed = 0;
    long _maxMissed = 100000;

    AccelStepper* _stepper;
    Encoder* _encoder;
    
};