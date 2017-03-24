#include "src/config.h"

std::vector<dataStream> readConfig(ConfigData &ConfigData) {
  auto config = cpptoml::parse_file("../config.toml");

  ConfigData.logFilePath = *config->get_qualified_as<std::string>("application.logFilePath");
  ConfigData.MACAddress = *config->get_qualified_as<std::string>("application.MACAddress");
  ConfigData.plotWidth   = *config->get_qualified_as<int32_t>("application.plotWidth");
  ConfigData.mechPlotMin = *config->get_qualified_as<int32_t>("application.mechPlotMin");
  ConfigData.mechPlotMax = *config->get_qualified_as<int32_t>("application.mechPlotMax");
  ConfigData.elecPlotMin = *config->get_qualified_as<int32_t>("application.elecPlotMin");
  ConfigData.elecPlotMax = *config->get_qualified_as<int32_t>("application.elecPlotMax");

  auto                    tarr = config->get_table_array("data");
  std::vector<dataStream> vec;
  for (const auto &table : *tarr) {
    auto            name       = *table->get_as<std::string>("name");
    auto            type       = *table->get_as<std::string>("type");
    auto            colour     = *table->get_as<std::string>("colour");
    auto            position   = *table->get_as<uint8_t>("position");
    auto            multiplier = *table->get_as<double>("multiplier");
    auto            minWarning = *table->get_as<double>("minWarning");
    auto            maxWarning = *table->get_as<double>("maxWarning");
    DataType        actualType;
    Qt::GlobalColor actualColour;

    // Boy, sure wish I had a match statement right about now...
    if (type == "Time") {
      actualType = DataType::Time;
    } else if (type == "Mechanical") {
      actualType = DataType::Mechanical;
    } else if (type == "Electrical") {
      actualType = DataType::Electrical;
    } else if (type == "CurrentEngineState") {
      actualType = DataType::CurrentEngineState;
    } else {
      throw std::logic_error("Invalid data.type specified in config.toml.");
    }

    if (colour == "red") {
      actualColour = Qt::red;
    } else if (colour == "green") {
      actualColour = Qt::green;
    } else if (colour == "blue") {
      actualColour = Qt::blue;
    } else if (colour == "black") {
      actualColour = Qt::black;
    } else if (colour == "cyan") {
      actualColour = Qt::cyan;
    } else if (colour == "magenta") {
      actualColour = Qt::magenta;
    } else if (colour == "none") {
      // Not going to be displayed anyway, so make it the worst color there is
      actualColour = Qt::yellow;
    } else {
      throw std::logic_error("Invalid data.type specified in config.toml.");
    }

    vec.push_back(dataStream(name, 0, multiplier, minWarning, maxWarning, position, actualType, actualColour));
  }
  return vec;
}
