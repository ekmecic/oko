// -*-c++-*-
#pragma once

#include "src/config.h"

#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>

class ConnectionHandler : public QObject {
  Q_OBJECT
public:
  ConnectionHandler(const ConfigData _configData);
  void setup(QBluetoothSocket& socket);

private:
  QBluetoothSocket* socket;
  ConfigData        configData;
};
