// -*-c++-*-
#pragma once
#include "src/dataStream.h"

#include <QBluetoothSocket>
#include <QRegularExpression>
#include <iostream>
#include <vector>

void parseSerial(QBluetoothSocket* socket, std::vector<dataStream>& vec);
