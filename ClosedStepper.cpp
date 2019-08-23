#include "ClosedStepper.h"

#define MAX_RETRIES 30
#define MAX_ACCELERATION 10000

ClosedStepper::~ClosedStepper(){
    delete _stepper;
    delete _encoder;
}

ClosedStepper::ClosedStepper(uint8_t enc_pin1, uint8_t enc_pin2, uint8_t interface, uint8_t pin1, uint8_t pin2 , uint8_t pin3, uint8_t pin4, bool enable) {
 
 _stepper = new AccelStepper(interface, pin1, pin2, pin3, pin4, enable);
 _encoder = new Encoder(enc_pin1, enc_pin2);
 this->init();

}

ClosedStepper::ClosedStepper(Encoder *encoder, AccelStepper *stepper) {
    _stepper = stepper;
    _encoder = encoder;
    this->init();
}


void ClosedStepper::init() {
  _currentTarget = _encoder->read();
  _stepper->setCurrentPosition(_currentTarget);
  _stepper->setMaxSpeed(60);
  _stepper->setAcceleration(MAX_ACCELERATION);
}

void ClosedStepper::setTarget(long target) {
    _currentTarget = target;
}
long ClosedStepper::getTarget() {
    return _currentTarget;
}


int ClosedStepper::getTolerance(){
  return _maxError;
}

void ClosedStepper::setTolerance(int tolerance) {
  _maxError = tolerance;
}

int ClosedStepper::getEncoderSPR() {
  return _encoderSpr;
}

void ClosedStepper::setEncoderSPR(int spr) {
  _encoderSpr = spr;
}

int ClosedStepper::getStepperSPR() {
  return _stepperSpr;
}

void ClosedStepper::setStepperSPR(int spr) {
  _stepperSpr = spr;
}

AccelStepper* ClosedStepper::getStepper() {
  return _stepper;
}

Encoder* ClosedStepper::getEncoder() {
  return _encoder;
}

long ClosedStepper::getCurrentPosition() {
  return map(_encoder->read(), 0, _encoderSpr, 0, _stepperSpr);
}

void ClosedStepper::setCurrentPosition(long position) {
  long enc_pos = map(position, 0, _stepperSpr, 0, _encoderSpr);
  _encoder->write(enc_pos);
}


bool ClosedStepper::run(){
    if (_stepper->distanceToGo() == 0) {
      long realPos = map(_encoder->read(), 0, _encoderSpr, 0, _stepperSpr);
      if (abs(realPos - _currentTarget)>_maxError && _nmissed<MAX_RETRIES){
        _stepper->setCurrentPosition(realPos);
        _stepper->moveTo(_currentTarget);
        _nmissed++;
        return true;
        }
      else {
        return false;}
       }
    else {
        _stepper->run();
        _nmissed = 0;
        return true;
       } 
}

bool ClosedStepper::runConstSpeed() {
      if (_stepper->distanceToGo() == 0) {
      long realPos = map(_encoder->read(), 0, _encoderSpr, 0, _stepperSpr);
      if ((abs(realPos - _currentTarget)>_maxError) && (_nmissed<MAX_RETRIES)){
        _stepper->setCurrentPosition(realPos);
        _stepper->moveTo(_currentTarget);
        _nmissed++;
        return true;
        }
      else {
        return false;}
       }
    else {
        _stepper->runSpeed();
        _nmissed = 0;
        return true;
       } 
}

void ClosedStepper::runToTarget() {
  while (run());
  
}
