#include "src/genBoardInterface.h"

genBoardInterface::genBoardInterface(QObject *parent) : QObject(parent) {
  this->endThread = false;
  this->updateInterval = 50;
}

void genBoardInterface::makeNewFakeData() {
  for (;;) {
    // Kill the data thread if the user closes the window
    if (endThread) {
      return;
    }

    genBoardValues[0][0] = makeRandomData() * 0.1;
    genBoardValues[0][1] = makeRandomData() * 0.2 + 30;
    genBoardValues[0][2] = makeRandomData() * 0.3 + 75;
    genBoardValues[0][3] = makeRandomData() * 0.4 + 130;
    genBoardValues[0][4] = makeRandomData() * 0.1;
    genBoardValues[0][5] = makeRandomData() * 0.25 + 40;
    genBoardValues[0][6] = makeRandomData() * 0.5 + 100;

    // Send all of the current values to the log file
    logData();

    emit newDataAvailable();
    QThread::currentThread()->msleep(this->updateInterval);
  }
}

void genBoardInterface::stopThread() {
  this->endThread = true;
}

void genBoardInterface::onUpdateIntervalFound(int64_t newUpdateInterval) {
  this->updateInterval = newUpdateInterval;
}

double genBoardInterface::makeRandomData() { return double(rand()) / 1e7; }

void genBoardInterface::logData() {
  LOG(INFO) << this->genBoardValues[0][0] << ","
            << this->genBoardValues[0][1] << ","
            << this->genBoardValues[0][2] << ","
            << this->genBoardValues[0][3] << ","
            << this->genBoardValues[0][4] << ","
            << this->genBoardValues[0][5] << ","
            << this->genBoardValues[0][6] << ",";
}
