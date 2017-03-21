// -*-c++-*-
#pragma once

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
  dataStream(std::string _name, double _value, double _multiplier,
             double _minWarning, double _maxWarning, double _position,
             DataType _dataType)
      : name(_name), value(_value), multiplier(_multiplier),
        minWarning(_minWarning), maxWarning(_maxWarning), position(_position),
        dataType(_dataType) {}

  std::string name;
  double value;
  double multiplier;
  double minWarning;
  double maxWarning;
  uint8_t position;
  DataType dataType;
};
