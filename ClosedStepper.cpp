#include "ClosedStepper.h"

#define MAX_RETRIES 1000

ClosedStepper::~ClosedStepper(){
    delete _stepper;
    delete _encoder;
}
ClosedStepper::ClosedStepper(uint8_t enc_pin1, uint8_t enc_pin2, uint8_t interface, uint8_t pin1, uint8_t pin2 , uint8_t pin3, uint8_t pin4, bool enable) {
 
 _stepper = new AccelStepper(interface, pin1, pin2, pin3, pin4, enable);
 _encoder = new Encoder(enc_pin1, enc_pin2);
 _currentTarget = _encoder->read();
 _max_err = 4;
 _encoder_spr = 400;
 _stepper_spr = 200;

}

ClosedStepper::ClosedStepper(Encoder *encoder, AccelStepper *stepper) {
    _stepper = stepper;
    _encoder = encoder;
    _currentTarget = _encoder->read();
    _max_err = 4;
    _encoder_spr = 400;
    _stepper_spr = 200;
}

void ClosedStepper::setTarget(long target) {
    _currentTarget = target;
}
long ClosedStepper::getTarget() {
    return _currentTarget;
}

bool ClosedStepper::run(){
    if (_stepper->distanceToGo() == 0) {
      long realPos = map(_encoder->read(), 0, _encoder_spr, 0, _stepper_spr);
      if (abs(realPos - _currentTarget)>_max_err){
        _stepper->setCurrentPosition(realPos);
        _stepper->moveTo(_currentTarget);
        return true;
        }
      else return false;
       }
    else {
           _stepper->run();
           return false;
       }
      
}
void ClosedStepper::runContinuous(){
    while(1){
      if (_stepper->distanceToGo() == 0) {
        long realPos = map(_encoder->read(), 0, _encoder_spr, 0, _stepper_spr);
      if (abs(realPos - _currentTarget)>_max_err){
        _stepper->setCurrentPosition(realPos);
        _stepper->moveTo(_currentTarget);
        }
        else return;
       }
       else _stepper->run();
    }
}
