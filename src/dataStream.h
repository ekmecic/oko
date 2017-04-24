// -*-c++-*-
#pragma once

#include <QColor>
#include <string>
#include <vector>

typedef enum {
  Time,
  Mechanical,
  Electrical,
  CurrentEngineState,
} DataType;

class dataStream {
public:
  dataStream(QString             _name,
             double              _multiplier,
             std::vector<double> _warningThresholds,
             std::vector<double> _typicalValues,
             double              _position,
             DataType            _dataType,
             Qt::GlobalColor     _colour)
      // clang-format off
      : name(_name),
        multiplier(_multiplier),
        warningThresholds(_warningThresholds),
        typicalValues(_typicalValues),
        position(_position),
        dataType(_dataType),
        colour(_colour) {}
  // clang-format on

  QString             name;
  double              value;
  double              scaledValue;
  double              multiplier;
  std::vector<double> warningThresholds;
  std::vector<double> typicalValues;
  uint8_t             position;
  DataType            dataType;
  Qt::GlobalColor     colour;
  uint8_t             graphNum;
};
