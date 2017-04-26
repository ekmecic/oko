#include "src/connectionHandler.h"

ConnectionHandler::ConnectionHandler(QBluetoothSocket* _socket, const ConfigData _configData) {
  socket     = _socket;
  configData = _configData;
}

void ConnectionHandler::setup() {
  // Connect to the Bluetooth module using the MAC address from the config file
  socket->connectToService(QBluetoothAddress(configData.MACAddress), QBluetoothUuid::Sdp);
  // If there's an interruption to the connection, try reconnect to the Bluetooth module
  // TODO: The current implementation of the reconnect functionality is slow to reconnect
  //       since it waits for a connection error to occur before reconnecting.
  //       This process takes upwards of 20 seconds.
  //       Ideally this should take less than 5 seconds.
  connect(socket, &QBluetoothSocket::disconnected, this, [&] {
      while (socket->state() != QBluetoothSocket::ConnectingState) {
        socket->connectToService(QBluetoothAddress(configData.MACAddress), QBluetoothUuid::Sdp);
      }
    });
}
