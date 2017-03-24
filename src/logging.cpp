#include "src/logging.h"

void setupLogging(const std::vector<dataStream> &vec, std::string logFilePath) {
  el::Configurations loggingConf;
  loggingConf.setToDefault();
  loggingConf.set(el::Level::Global,
                  el::ConfigurationType::Filename,
                  logFilePath.append("oko-%datetime{%Y-%M-%d-T%H:%m:%s}.log"));
  loggingConf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime{%Y-%M-%d-T%H:%m:%s:%g},%msg");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput, "false");

  el::Loggers::reconfigureAllLoggers(loggingConf);
  LOG(INFO) << "FORMAT:";
  std::string fmt;
  for (auto &vec : vec) {
    fmt.append(vec.name);
    fmt.append(",");
  }
  fmt.pop_back();
  LOG(INFO) << fmt;
}
