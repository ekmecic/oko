// -*-c++-*-
#pragma once

#include "lib/easylogging++/easylogging++.h"
#include "src/config.h"
#include "src/dataStream.h"
#include <QObject>

class Logger : public QObject {
  Q_OBJECT
public:
  Logger(ConfigData _configData);
  void setup(std::vector<dataStream>& dataStreams);
  void update(std::vector<dataStream>& dataStreams);

private:
  ConfigData configData;
};
