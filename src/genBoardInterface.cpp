#include "genBoardInterface.h"

genBoardInterface::genBoardInterface(QObject *parent) : QObject(parent) {}

void genBoardInterface::makeNewFakeData() {
  for (;;) {
    this->batteryCurrent = makeRandomData();
    this->busVoltage = makeRandomData();
    this->measuredPhaseCurrent = makeRandomData();
    this->commandedPhaseCurrent = makeRandomData();
    this->speed = makeRandomData();
    this->throttleOutput = makeRandomData();
    this->engineTemperature = makeRandomData();

    emit newDataAvailable();
    QThread::currentThread()->msleep(200);
  }
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

double genBoardInterface::makeRandomData() { return double(rand()); }
// clang-format on
