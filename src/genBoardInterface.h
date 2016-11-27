// -*-c++-*-
/***************************************************************************
  The genBoardInterface class pulls data from the generator board and makes
  it available for oko to display to the user.

  Currently it simply creates a bunch of fake data, but once the board<->PC
  communication protocol is decided upon it'll pull data from a
  serial/BT/wifi/GSM/whatever connection.
  *************************************************************************/

#pragma once

#include "lib/easylogging++/easylogging++.h"

#include <QObject>
#include <QThread>
#include <cstdlib>

class genBoardInterface : public QObject {
  Q_OBJECT

public:
  explicit genBoardInterface(QObject *parent = 0);

  void makeNewFakeData();

  double genBoardValues[2][7] = {0};

signals:
  void newDataAvailable();

public slots:
  void stopThread();
  void onUpdateIntervalFound(int64_t newUpdateInterval);

private:
  // Temporary dummy function to create some fake data
  double makeRandomData();
  void logData();

  bool endThread;
  int64_t updateInterval;
};
