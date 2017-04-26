#include "src/config.h"

std::vector<dataStream> readConfig(ConfigData& ConfigData) {
  // Open up config.toml, read all of the "basic" values, and populate ConfigData with them.
  auto config = cpptoml::parse_file("../config.toml");
  ConfigData.logFolderPath =

    QString::fromStdString(*config->get_qualified_as<std::string>("application.logFolderPath"));
  ConfigData.MACAddress = QString::fromStdString(*config->get_qualified_as<std::string>("application.MACAddress"));
  ConfigData.plotWidth  = *config->get_qualified_as<int32_t>("application.plotWidth");

  // The rest of this function processes all of the dataStream tables in config.toml
  // Open up the table array
  auto                    tarr = config->get_table_array("dataStream");
  std::vector<dataStream> vec;
  for (const auto& table : *tarr) {
    // Read all of the values into temporary variables
    auto            name              = *table->get_as<std::string>("name");
    auto            type              = *table->get_as<std::string>("type");
    auto            colour            = *table->get_as<std::string>("colour");
    auto            position          = *table->get_as<uint8_t>("position");
    auto            multiplier        = *table->get_as<double>("multiplier");
    auto            warningThresholds = *table->get_qualified_array_of<double>("warningThresholds");
    auto            typicalValues     = *table->get_qualified_array_of<double>("typicalValues");
    DataType        actualType;
    Qt::GlobalColor actualColour;

    // Match the DataType and color to the correct values
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
      actualColour = Qt::yellow; // Not going to be displayed anyway, who cares if it's yellow
    } else {
      throw std::logic_error("Invalid data.type specified in config.toml.");
    }

    // clang-format off
    // Create a dataStream with the information we've read and add it to the vector
    vec.push_back(dataStream(QString::fromStdString(name),
                             multiplier,
                             warningThresholds,
                             typicalValues,
                             position,
                             actualType,
                             actualColour));
  }
  // clang-format on
  return vec;
}
