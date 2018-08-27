//TODO(Rebecca): Fix these to be proper calls.
bool batteryLow = false;

bool isCompassNorth(const State &state) {
  return state.angle == North;
}

// Termination occurs  when robot gets to end location and is pointing South
bool stateIsTerminal(const State &state) {
  bool atEndPosition = (state.position == END_LOCATION && state.angle == South);
  return atEndPosition;
  //TODO: This will be more complex if Benny actually works...
  //return getLatch();
}

int calculateReward(const State &state, const Action action, const State &statePrime) {
  if(stateIsTerminal(statePrime)) {
    return 500;
  }

  bool hitAWall = state == statePrime;
  if(hitAWall) {
    //cout << "Hit a Wall!!\n";
    return -10;
  }
  
  /*if(batteryLow) {
    return -50;
  }*/

  //TODO: Likely don't need this, but to encourage the right kind of action for now.
  if(isCompassNorth(statePrime)) {
    return -1;
  }

  return -2;
}