// -*-c++-*-
#pragma once

#include "lib/cpptoml/cpptoml.h"
#include "src/dataStream.h"

#include <QColor>
#include <exception>
#include <string>

typedef struct {
  std::string logFilePath;
  int32_t plotWidth;
  int32_t mechPlotMin;
  int32_t mechPlotMax;
  int32_t elecPlotMin;
  int32_t elecPlotMax;
} ConfigData;

std::vector<dataStream> readConfig(ConfigData &ConfigData);
