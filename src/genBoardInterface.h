// -*-c++-*-
/***************************************************************************
  The genBoardInterface class pulls data from the generator board and makes
  it available for oko to display to the user.

  Currently it simply creates a bunch of fake data, but once the board<->PC
  communication protocol is decided upon it'll pull data from a
  serial/BT/wifi/GSM/whatever connection.
  *************************************************************************/

#pragma once
#include <cstdlib>

class genBoardInterface {
public:
  // Default constructor
  genBoardInterface() {
    this->batteryCurrent = 0;
    this->busVoltage = 0;
    this->measuredPhaseCurrent = 0;
    this->commandedPhaseCurrent = 0;
    this->speed = 0;
    this->throttleOutput = 0;
    this->engineTemperature = 0;
  }

  void makeNewFakeData();

  double getBatteryCurrent() const;
  double getBusVoltage() const;
  double getMeasuredPhaseCurrent() const;
  double getCommandedPhaseCurrent() const;
  double getSpeed() const;
  double getThrottleOutput() const;
  double getEngineTemperature() const;

  void setBatteryCurrent(double batteryCurrent);
  void setBusVoltage(double busVoltage);
  void setMeasuredPhaseCurrent(double measuredPhaseCurrent);
  void setCommandedPhaseCurrent(double commandedPhaseCurrent);
  void setSpeed(double speed);
  void setThrottleOutput(double throttleOutput);
  void setEngineTemperature(double engineTemperature);

private:
  // Temporary dummy function to create some fake data
  double makeRandomData();

  double batteryCurrent;
  double busVoltage;
  double measuredPhaseCurrent;
  double commandedPhaseCurrent;
  double speed;
  double throttleOutput;
  double engineTemperature;
};
