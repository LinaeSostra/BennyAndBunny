#include <Arduino.h>
#include "Learning.h"

//TODO(Rebecca): Fix these to be proper calls.
bool sensorPressed = false;
bool batteryLow = false;
bool isCompassNorth = false;

bool stateIsTerminal(const State &state) { 
  //TODO: This will be more complex if Benny actually works...
  if(sensorPressed) {
    return true;
  }
  return false;
}

int8_t reward(const State &state, const Action action, const State &statePrime) {
  if(stateIsTerminal(statePrime)) {
    return 50;
  }
  
  bool isXOutOfBounds = abs(statePrime.xPosition) >= 10;
  bool isYOutOfBounds = abs(statePrime.yPosition) >= 10;
  if(isXOutOfBounds || isYOutOfBounds) {
    return -100;
  }
  
  if(batteryLow) {
    return -50;
  }

  //TODO: Likely don't need this, but to encourage the right kind of action for now.
  if(isCompassNorth) {
    return -1;
  }

  return -2;
}
