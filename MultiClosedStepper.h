// MultiStepper.h

#ifndef MultiStepper_h
#define MultiStepper_h

#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#define CLOSEDSTEPPER_MAX_STEPPERS 10

class ClosedStepper;

class MultiClosedStepper
{
public:
    /// Constructor
    MultiClosedStepper();

    /// Add a stepper to the set of managed steppers
    /// There is an upper limit of MULTISTEPPER_MAX_STEPPERS = 10 to the number of steppers that can be managed
    /// \param[in] stepper Reference to a stepper to add to the managed list
    /// \return true if successful. false if the number of managed steppers would exceed MULTISTEPPER_MAX_STEPPERS
    boolean addStepper(ClosedStepper& stepper);

    /// Set the target positions of all managed steppers 
    /// according to a coordinate array.
    /// New speeds will be computed for each stepper so they will all arrive at their 
    /// respective targets at very close to the same time.
    /// \param[in] absolute An array of desired absolute stepper positions. absolute[0] will be used to set
    /// the absolute position of the first stepper added by addStepper() etc. The array must be at least as long as 
    /// the number of steppers that have been added by addStepper, else results are undefined.
    void setTarget(long target[]);
    
    /// Calls runSpeed() on all the managed steppers
    /// that have not acheived their target position.
    /// \return true if any stepper is still in the process of running to its target position.
    boolean run();

    /// Runs all managed steppers until they acheived their target position.
    /// Blocks until all that position is acheived. If you dont
    /// want blocking consider using run() instead.
    void runToTarget();
    
    
    
    
private:
    /// Array of pointers to the steppers we are controlling.
    /// Fills from 0 onwards
    ClosedStepper* _steppers[CLOSEDSTEPPER_MAX_STEPPERS];

    /// Number of steppers we are controlling and the number
    /// of steppers in _steppers[]
    uint8_t       _num_steppers;
};

/// @example MultiStepper.pde
/// Use MultiStepper class to manage multiple steppers and make them all move to 
/// the same position at the same time for linear 2d (or 3d) motion.

#endif
