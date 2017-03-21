#include "src/config.h"

std::vector<dataStream> readConfig() {
  auto config = cpptoml::parse_file("../config.toml");

  auto tarr = config->get_table_array("data");
  std::vector<dataStream> vec;

  for (const auto &table : *tarr) {
    auto name = *table->get_as<std::string>("name");
    auto type = *table->get_as<std::string>("type");
    auto colour = *table->get_as<std::string>("colour");
    auto position = *table->get_as<uint8_t>("position");
    auto multiplier = *table->get_as<double>("multiplier");
    auto minWarning = *table->get_as<double>("minWarning");
    auto maxWarning = *table->get_as<double>("maxWarning");
    DataType actualType;
    Qt::GlobalColor actualColour;

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

    if (colour.compare("red")) {
      actualColour = Qt::red;
    } else if (colour.compare("green")) {
      actualColour = Qt::green;
    } else if (colour.compare("blue")) {
      actualColour = Qt::blue;
    } else if (colour.compare("black")) {
      actualColour = Qt::black;
    } else if (colour.compare("cyan")) {
      actualColour = Qt::cyan;
    } else if (colour.compare("magenta")) {
      actualColour = Qt::magenta;
    } else if (colour.compare("none")) {
      // Not going to be displayed anyway, so make it the worst color there is
      actualColour = Qt::yellow;
    } else {
      throw std::logic_error("Invalid data.type specified in config.toml.");
    }

    vec.push_back(dataStream(name, 0, multiplier, minWarning, maxWarning,
                             position, actualType, actualColour));
  }
  return vec;
}
