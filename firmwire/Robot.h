#ifndef ROBOT_H
#define ROBOT_H
#include "Learning.h"

State getCurrentState(); // Returns the current state of the robot
void resetPosition(); // Reset robot to starting location
void resetToRandomPosition(); // Reset robot to random starting location
void logState(); // Save the robot's state
void apply(Action action); // Adjust the robot's states
#endif
