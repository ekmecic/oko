#include "src/logging.h"

void setupLogging(std::string logFilePath) {
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
  LOG(INFO) << "BatteryCurrent,BusVoltage,MeasuredPhaseCurrent,"
               "CommandedPhaseCurrent,Speed,ThrottleOutput,EngineTemperature";
  LOG(INFO) << "Time is in the local time of the computer running oko.";
}
