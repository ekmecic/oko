#include "src/logger.h"

Logger::Logger(const ConfigData _configData) {
  configData = _configData;
}

void Logger::setup(std::vector<dataStream>& dataStreams) {
  el::Configurations loggingConf;
  loggingConf.setToDefault();
  loggingConf.set(el::Level::Global,
                  el::ConfigurationType::Filename,
                  configData.logFolderPath.toStdString().append("oko-%datetime{%Y-%M-%d-T%H:%m:%s}.log"));
  loggingConf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime{%Y-%M-%d-T%H:%m:%s:%g},%msg");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");

  el::Loggers::reconfigureAllLoggers(loggingConf);
  LOG(INFO) << "FORMAT:";
  QString fmt;
  for (auto& stream : dataStreams) {
    fmt.append(stream.name);
    fmt.append(",");
  }
  fmt.chop(1); // Remove the trailing comma
  LOG(INFO) << fmt.toStdString();
}

void Logger::update(std::vector<dataStream>& dataStreams) {
  QString data;
  for (auto& stream : dataStreams) {
    auto str = QString::number(stream.value);
    data.append(str);
    data.append(",");
  }
  data.chop(1);
  LOG(INFO) << data.toStdString();
}
