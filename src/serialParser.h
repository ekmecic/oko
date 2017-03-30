// -*-c++-*-
#include "src/dataStream.h"

#include <QBluetoothSocket>
#include <QRegularExpression>
#include <iostream>

void parseSerial(QBluetoothSocket *socket, std::vector<dataStream> &vec);
