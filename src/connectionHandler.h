// -*-c++-*-
#pragma once

#include "src/config.h"

#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>
#include <QTime>
#include <QTimer>

class ConnectionHandler : public QObject {
  Q_OBJECT
public:
  ConnectionHandler(ConfigData _configData);
  void setup(QBluetoothSocket& socket);
  void updateTimestamp();

private:
  QBluetoothSocket* socket;
  ConfigData        configData;
  QTime             timestamp;
};
