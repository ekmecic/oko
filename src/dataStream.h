// -*-c++-*-
#pragma once

#include <QColor>
#include <cstdint>
#include <string>

typedef enum {
  Time,
  Mechanical,
  Electrical,
  CurrentEngineState,
} DataType;

class dataStream {
public:
  dataStream(std::string     _name,
             double          _value,
             double          _multiplier,
             double          _minWarning,
             double          _maxWarning,
             double          _typMin,
             double          _typMax,
             double          _position,
             DataType        _dataType,
             Qt::GlobalColor _colour)
      // clang-format off
      : name(_name),
        value(_value),
        multiplier(_multiplier),
        minWarning(_minWarning),
        maxWarning(_maxWarning),
        typMin(_typMin),
        typMax(_typMax),
        position(_position),
        dataType(_dataType),
        colour(_colour) {}
  // clang-format on

  std::string     name;
  double          value;
  double          multiplier;
  double          minWarning;
  double          maxWarning;
  double          typMin;
  double          typMax;
  double          scaleFactor;
  uint8_t         position;
  DataType        dataType;
  Qt::GlobalColor colour;
  uint8_t         graphNum;
};
