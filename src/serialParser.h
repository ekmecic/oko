// -*-c++-*-
#pragma once
#include "src/dataStream.h"

#include <QBluetoothSocket>
#include <QRegularExpression>
#include <vector>

class SerialParser : public QObject {
  Q_OBJECT
public:
  void update(QBluetoothSocket* socket, std::vector<dataStream>& vec);
};
