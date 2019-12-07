#include "ClosedStepper.h"

#define MAX_RETRIES 5
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
  if (target != _currentTarget) {
  _failed = false;
    _nmissed = 0;
    _currentTarget = target;
    _stepper->moveTo(target);
  }
  
}

long ClosedStepper::getTarget() {
    return _currentTarget;
}


float ClosedStepper::getMaxSpeed() {
  return _stepper->maxSpeed();
}

void ClosedStepper::setMaxSpeed(float speed) {
  _stepper->setMaxSpeed(speed);
}


void ClosedStepper::setAcceleration(float accel) {
  _stepper->setAcceleration(accel);
}

long ClosedStepper::getTolerance(){
  return _maxError;
}

void ClosedStepper::setTolerance(long tolerance) {
  _maxError = tolerance;
}

long ClosedStepper::getEncoderSPR() {
  return _encoderSpr;
}

void ClosedStepper::setEncoderSPR(long spr) {
  _encoderSpr = spr;
}

long ClosedStepper::getStepperSPR() {
  return _stepperSpr;
}

void ClosedStepper::setStepperSPR(long spr) {
  _stepperSpr = spr;
}

AccelStepper* ClosedStepper::getStepper() {
  return _stepper;
}

Encoder* ClosedStepper::getEncoder() {
  return _encoder;
}

long ClosedStepper::getCurrentPosition() {
  return _encoder->read()*_stepperSpr/_encoderSpr;
}

void ClosedStepper::setCurrentPosition(long position) {
  long enc_pos = position*_encoderSpr/_stepperSpr;
  _encoder->write(enc_pos);
}

long ClosedStepper::distanceToGo() {
  return _currentTarget - getCurrentPosition();
}
bool ClosedStepper::success() {
  return !_failed;
  }

void ClosedStepper::closeLoop(){
  _stepCount = 0;
  if ((abs(distanceToGo()-_stepper->distanceToGo())>_maxError)){
    _nmissed += abs(distanceToGo() - _stepper->distanceToGo());
    if (_nmissed<_maxMissed){
      _stepper->setCurrentPosition(getCurrentPosition());
      _stepper->moveTo(_currentTarget);
    } else {
      _failed = true;
    }
        }
}

bool ClosedStepper::run(){
  if (_stepCount > _testInterval) {
    closeLoop();
    if (_failed) return false;
    }
  if (_stepper->run()) {
    _stepCount++;
    return true; 
  }
  return false;
}

bool ClosedStepper::runConstSpeed() {
  
  if (_stepCount > _testInterval) {
    closeLoop();
    if (_failed) return false;
    }
  if (_stepper->runSpeed()) {
    _stepCount++;
    return true; 
  }
  return false;
  }

void ClosedStepper::runToTarget() {
  _nmissed = 0;
  while (run());
}

void ClosedStepper::stop(){
    _stepper->stop();
    while (_stepper->run());
    setCurrentPosition(_stepper->currentPosition());

}
