// -*-c++-*-
/** \file config.h */
#pragma once

#include "cpptoml.h"
#include "src/dataStream.h"

#include <QColor>
#include <exception>
#include <string>
#include <vector>

typedef struct {
  /** @brief Path in which the log files will be stored. */
  QString logFolderPath;
  /** @brief MAC address of the Bluetooth module. */
  QString MACAddress;
  /** @brief Width of the plot in seconds. */
  int32_t plotWidth;
} ConfigData;

/** @brief Reads config.toml, populates ConfigData and returns the collated vector of dataStreams.
    @param ConfigData The ConfigData instance to be populated with data from config.toml.
    @return {std::vector<dataStream>} A vector of dataStreams corresponding to the metadata in config.toml. */
std::vector<dataStream> readConfig(ConfigData& ConfigData);
