#include "src/engineState.h"

QString parseEngineState(const double value) {
  // Sample values
  switch (static_cast<int>(value)) {
  case 0: {
    return "Init";
    break;
  }
  case 1: {
    return "Starting";
    break;
  }
  case 2: {
    return "No control";
    break;
  }
  case 3: {
    return "Manual";
    break;
  }
  case 4: {
    return "Idle";
    break;
  }
  case 5: {
    return "Speed/torque control";
    break;
  }
  case 6: {
    return "Fault";
    break;
  }
  default:
    return "Unknown";
    break;
  }
}
