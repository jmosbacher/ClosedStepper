#include "ClosedStepper.h"
#define MAX_RETRIES 1000

ClosedStepper::ClosedStepper(uint8_t interface = AccelStepper::DRIVER, 
                             uint8_t pin1 = 4, uint8_t pin2 =5 , uint8_t pin3 = 6,
                             uint8_t pin4 = 7, bool enable = true, uint8_t encoderPinA = 2,
                             uint8_t encoderPinB = 3, float stepRatio = 1f) :
                             AccelStepper(interface, pin1, pin2, pin3, pin4, enable) {

    _encoder = Encoder(encoderPinA, encoderPinB);
    _realPosition = _encoder.read;
    _nextStep = 0;
    _failedSteps = 0;
}

ClosedStepper::ClosedStepper(void (*forward)(), void (*backward)(), long (*realPosition)()) : 
                             AccelStepper(forward, backward) {
    _realPosition = realPosition;
    _nextStep = 0;
    _failedSteps = 0;
}

boolean ClosedStepper::runSpeed()
{
    // Dont do anything unless we actually have a step interval
    if (!_stepInterval)
	    return false;
    _currentPos = _realPosition();
    if (_failedSteps >= MAX_RETRIES) {
        moveTo(_currentPos);
        return false;
    }
        

    unsigned long time = micros(); 
        if (time - _lastStepTime >= _stepInterval)
        {
            if (_direction == DIRECTION_CW)
            {
                // Clockwise
                _nextStep = _currentPos+1;
            }
            else
            {
                // Anticlockwise  
                _nextStep = _currentPos-1;
            }
            
            step(_nextStep);
            _currentPos = _realPosition();
            if (_currentPos == _nextStep){ // Step has been succesful.
                _lastStepTime = time;  // Caution: does not account for costs in step()
                _failedSteps = 0;
            } 
            else _failedSteps+=1; // step failed.
            return true;
        }
        else
        {
            return false;
        }
}
