// -*-c++-*-
#pragma once

#include "cpptoml.h"
#include "src/dataStream.h"

#include <QColor>
#include <exception>
#include <string>
#include <vector>

typedef struct {
  QString logFolderPath;
  QString MACAddress;
  int32_t plotWidth;
} ConfigData;

std::vector<dataStream> readConfig(ConfigData& ConfigData);
