// -*-c++-*-
#pragma once

#include "src/config.h"

#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>

/** @brief Handles the Bluetooth connection from the GUI to the Bluetooth module.
    @author Emil Ekmečić
    @date April 2017

    Connects the GUI to the Bluetooth module according to the MAC address specified in config.toml.
    It also automatically reconnects the GUI to the Bluetooth module in case of interruption, albeit slowly. */
class ConnectionHandler : public QObject {
  Q_OBJECT

public:
  /** @brief Constructs a new ConnectionHandler using the QBluetoothSocket and ConfigData from the main program.
      @param _socket The BluetoothSocket created in the oko object.
      @param _configData Configuration data pulled from config.toml.
      We only really need it for the MACAddress. */
  ConnectionHandler(QBluetoothSocket* _socket, const ConfigData _configData);

  /** @brief Connects to the Bluetooth module and sets up the automatic reconnection functionality. */
  void setup();

private:
  /** @param socket The Bluetooth socket created in the oko object. */
  QBluetoothSocket* socket;

  /** @param configData Configuration data pulled from config.toml. We only really need it for the plotWidth. */
  ConfigData configData;
};
