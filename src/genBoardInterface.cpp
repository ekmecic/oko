#include "src/genBoardInterface.h"

genBoardInterface::genBoardInterface(QObject *parent) : QObject(parent) {
  this->batteryCurrent = 0;
  this->busVoltage = 0;
  this->measuredPhaseCurrent = 0;
  this->commandedPhaseCurrent = 0;
  this->speed = 0;
  this->throttleOutput = 0;
  this->engineTemperature = 0;

  this->endThread = false;
}

void genBoardInterface::makeNewFakeData() {
  for (;;) {
    // Kill the data thread if the user closes the window
    if (endThread) {
      return;
    }

    this->batteryCurrent = makeRandomData() * 0.1;
    this->busVoltage = makeRandomData() * 0.2 + 30;
    this->measuredPhaseCurrent = makeRandomData() * 0.3 + 75;
    this->commandedPhaseCurrent = makeRandomData() * 0.4 + 130;
    this->speed = makeRandomData() * 0.1;
    this->throttleOutput = makeRandomData() * 0.25 + 40;
    this->engineTemperature = makeRandomData() * 0.5 + 100;

    // Send all of the current values to the log file
    logData();

    emit newDataAvailable();
    QThread::currentThread()->msleep(50);
  }
}

void genBoardInterface::stopThread() {
  this->endThread = true;
}

// clang-format off
double genBoardInterface::getBatteryCurrent() const { return batteryCurrent; }
double genBoardInterface::getBusVoltage() const { return busVoltage; }
double genBoardInterface::getMeasuredPhaseCurrent() const { return measuredPhaseCurrent; }
double genBoardInterface::getCommandedPhaseCurrent() const { return commandedPhaseCurrent; }
double genBoardInterface::getSpeed() const { return speed; }
double genBoardInterface::getThrottleOutput() const { return throttleOutput; }
double genBoardInterface::getEngineTemperature() const { return engineTemperature; }

void genBoardInterface::setBatteryCurrent(double batteryCurrent) {
  this->batteryCurrent = batteryCurrent;
}
void genBoardInterface::setBusVoltage(double busVoltage) {
  this->busVoltage = busVoltage;
}
void genBoardInterface::setMeasuredPhaseCurrent(double measuredPhaseCurrent) {
  this->measuredPhaseCurrent = measuredPhaseCurrent;
}
void genBoardInterface::setCommandedPhaseCurrent(double commandedPhaseCurrent) {
  this->commandedPhaseCurrent = commandedPhaseCurrent;
}
void genBoardInterface::setSpeed(double speed) {
  this->speed = speed;
}
void genBoardInterface::setThrottleOutput(double throttleOutput) {
  this->throttleOutput = throttleOutput;
}
void genBoardInterface::setEngineTemperature(double engineTemperature) {
  this->engineTemperature = engineTemperature;
}
// clang-format on

double genBoardInterface::makeRandomData() { return double(rand()) / 1e7; }

void genBoardInterface::logData() {
  // clang-format off
  LOG(INFO) << this->batteryCurrent << ","
            << this->busVoltage << ","
            << this->measuredPhaseCurrent << ","
            << this->commandedPhaseCurrent << ","
            << this->speed << ","
            << this->throttleOutput << ","
            << this->engineTemperature;
  // clang-format on
}
