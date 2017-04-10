#include "src/logging.h"

void setupLogging(const std::vector<dataStream>& vec, QString logFolderPath) {
  el::Configurations loggingConf;
  loggingConf.setToDefault();
  loggingConf.set(el::Level::Global,
                  el::ConfigurationType::Filename,
                  logFolderPath.toStdString().append("oko-%datetime{%Y-%M-%d-T%H:%m:%s}.log"));
  loggingConf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime{%Y-%M-%d-T%H:%m:%s:%g},%msg");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");

  el::Loggers::reconfigureAllLoggers(loggingConf);
  LOG(INFO) << "FORMAT:";
  QString fmt;
  for (auto& vec : vec) {
    fmt.append(vec.name);
    fmt.append(",");
  }
  fmt.chop(1); // Remove the trailing comma
  LOG(INFO) << fmt.toStdString();
}

void logData(const std::vector<dataStream>& vec) {
  QString data;
  for (auto& vec : vec) {
    auto str = QString::number(vec.value);
    data.append(str);
    data.append(",");
  }
  data.chop(1);
  LOG(INFO) << data.toStdString();
}
