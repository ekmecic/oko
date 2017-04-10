#include "src/connectionHandler.h"

ConnectionHandler::ConnectionHandler(ConfigData _configData) {
  this->configData = _configData;
}

void ConnectionHandler::setup(QBluetoothSocket& socket) {
  socket.connectToService(QBluetoothAddress(configData.MACAddress), QBluetoothUuid::Sdp);
  connect(&socket, &QBluetoothSocket::disconnected, this, [&] {
    while (socket.state() != QBluetoothSocket::ConnectingState) {
      socket.connectToService(QBluetoothAddress(configData.MACAddress), QBluetoothUuid::Sdp);
    }
  });
}
