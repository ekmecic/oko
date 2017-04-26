#include "src/logger.h"

Logger::Logger(const ConfigData _configData) {
  configData = _configData;
}

void Logger::setup(std::vector<dataStream>& dataStreams) {
  el::Configurations loggingConf;
  loggingConf.setToDefault();
  // Set the name of the logfile to "oko-FineDate"
  loggingConf.set(el::Level::Global,
                  el::ConfigurationType::Filename,
                  configData.logFolderPath.toStdString().append("oko-%datetime{%Y-%M-%d-T%H:%m:%s}.log"));
  loggingConf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime{%Y-%M-%d-T%H:%m:%s:%g},%msg");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");

  el::Loggers::reconfigureAllLoggers(loggingConf);
  LOG(INFO) << "FORMAT:";
  QString line;
  // Construct the header of the file with the names of each column
  for (auto& stream : dataStreams) {
    line.append(stream.name);
    line.append(",");
  }
  line.chop(1); // Remove the trailing comma
  LOG(INFO) << line.toStdString();
}

void Logger::update(std::vector<dataStream>& dataStreams) {
  QString line;
  // Construct a line with all of the data seperated by commas
  for (auto& stream : dataStreams) {
    auto str = QString::number(stream.value);
    line.append(str);
    line.append(",");
  }
  line.chop(1); // Remove the trailing comma
  LOG(INFO) << line.toStdString();
}
