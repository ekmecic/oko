// -*-c++-*-
#include "src/dataStream.h"

#include <QBluetoothSocket>
#include <QRegularExpression>
#include <iostream>

std::vector<double> parseSerial(QBluetoothSocket *socket);
