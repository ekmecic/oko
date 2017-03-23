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
             double          _position,
             DataType        _dataType,
             Qt::GlobalColor _colour)
      : name(_name), value(_value), multiplier(_multiplier), minWarning(_minWarning), maxWarning(_maxWarning),
        position(_position), dataType(_dataType), colour(_colour) {
  }

  std::string     name;
  double          value;
  double          multiplier;
  double          minWarning;
  double          maxWarning;
  uint8_t         position;
  DataType        dataType;
  Qt::GlobalColor colour;
  uint8_t         graphNum;
};
