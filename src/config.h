// -*-c++-*-
#pragma once

#include "lib/cpptoml/cpptoml.h"
#include "src/dataStream.h"

#include <QColor>
#include <exception>
#include <string>
#include <vector>

typedef struct {
  QString logFilePath;
  QString MACAddress;
  int32_t plotWidth;
} ConfigData;

std::vector<dataStream> readConfig(ConfigData& ConfigData);
