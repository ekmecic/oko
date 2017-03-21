// -*-c++-*-
#pragma once

#include "lib/cpptoml/cpptoml.h"
#include "src/dataStream.h"

#include <exception>
#include <string>

std::vector<dataStream> readConfig();
