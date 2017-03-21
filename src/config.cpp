#include "src/config.h"

std::vector<dataStream> readConfig() {
  auto config = cpptoml::parse_file("../config.toml");

  auto tarr = config->get_table_array("data");
  std::vector<dataStream> vec;

  for (const auto &table : *tarr) {
    auto name = *table->get_as<std::string>("name");
    auto type = *table->get_as<std::string>("type");
    auto position = *table->get_as<uint8_t>("position");
    auto multiplier = *table->get_as<double>("multiplier");
    auto minWarning = *table->get_as<double>("minWarning");
    auto maxWarning = *table->get_as<double>("maxWarning");
    DataType actualType;

    // Boy, sure wish I had a match statement right about now...
    if (type.compare("Time")) {
      actualType = DataType::Time;
    } else if (type.compare("Mechanical")) {
      actualType = DataType::Mechanical;
    } else if (type.compare("Electrical")) {
      actualType = DataType::Electrical;
    } else if (type.compare("CurrentEngineState")) {
      actualType = DataType::CurrentEngineState;
    } else {
      throw std::logic_error("Invalid data.type specified in config.toml.");
    }

    vec.push_back(dataStream(name, 0, multiplier, minWarning, maxWarning,
                             position, actualType));
  }
  return vec;
}
