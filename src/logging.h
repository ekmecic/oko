// -*-c++-*-
#pragma once

#include "lib/easylogging++/easylogging++.h"
#include "src/dataStream.h"

void setupLogging(const std::vector<dataStream>& vec, QString logFolderPath);
void logData(const std::vector<dataStream>& vec);
