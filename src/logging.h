// -*-c++-*-
#pragma once

#include "lib/easylogging++/easylogging++.h"
#include "src/dataStream.h"

void setupLogging(const std::vector<dataStream> &vec, std::string logFilePath);
