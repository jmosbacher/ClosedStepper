// MultiClosedStepper.h

#ifndef MultiClosedStepper_h
#define MultiClosedStepper_h

#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#define MULTISTEPPER_MAX_STEPPERS 10

class ClosedStepper;

/////////////////////////////////////////////////////////////////////
/// \class MultiClosedStepper MultiClosedStepper.h <MultiClosedStepper.h>
/// \brief Operate multiple ClosedSteppers in a co-ordinated fashion
///
/// This class can manage multiple ClosedSteppers (up to ClosedStepper_MAX_STEPPERS = 10), 
/// and cause them all to move
/// to selected positions at such a (constant) speed that they all arrive at their
/// target position at the same time. This can be used to support devices with multiple steppers
/// on say multiple axes to cause linear diagonal motion. Suitable for use with X-Y plotters, flatbeds,
/// 3D printers etc
/// to get linear straight line movement between arbitrary 2d (or 3d or ...) positions.
///
/// Caution: only constant speed stepper motion is supported: Closederation and deceleration is not supported
/// All the steppers managed by ClosedStepper will step at a constant speed to their
/// target (albeit perhaps different speeds for each stepper).
class MultiClosedStepper: MultiStepper
{
public:
    /// Constructor
    MultiClosedStepper();

    /// Add a stepper to the set of managed steppers
    /// There is an upper limit of MULTISTEPPER_MAX_STEPPERS = 10 to the number of steppers that can be managed
    /// \param[in] stepper Reference to a stepper to add to the managed list
    /// \return true if successful. false if the number of managed steppers would exceed MULTISTEPPER_MAX_STEPPERS
    boolean addStepper(ClosedStepper& stepper);

private:
    /// Array of pointers to the steppers we are controlling.
    /// Fills from 0 onwards
    ClosedStepper* _steppers[MULTISTEPPER_MAX_STEPPERS];

};

/// @example MultiClosedStepper.ino
/// Use MultiClosedStepper class to manage multiple steppers and make them all move to 
/// the same position at the same time for linear 2d (or 3d) motion.

#endif
