// -*-c++-*-
#pragma once

#include "easylogging++.h"
#include "src/config.h"
#include "src/dataStream.h"
#include <QObject>

/** @brief Logs all Bluetooth module data to a text file.
    @author Emil Ekmečić
    @date April 2017

    Each time new data is received from the Bluetooth module it is logged to a text file using this object.
    Data is outputted in CSV format and each line is dated down to the millisecond.
    Logger is indiscriminate in what it logs, it logs all the value fields of every dataStream passed to it. */
class Logger : public QObject {
  Q_OBJECT
public:
  /** @brief Constructs a new Logger using the ConfigData from the main program.
      @param _configData Configuration data pulled from config.toml. We only really need it for the folder where the
      log file goes. */
  Logger(const ConfigData _configData);
  /** @brief Sets up the logging framework with the correct options.

      Sets file name (according to date), file location, and disables a few other options we don't like.
      Also prints the file header which contains the "legend" indicating which column is what.
      @param dataStreams All of the dataStreams. */
  void setup(std::vector<dataStream>& dataStreams);

  /** @brief Updates the log file with new values.

      Sets file name (according to date), file location, and disables a few other options we don't like.
      Also prints the file header which contains the "legend" indicating which column is what.
      @param dataStreams All of the dataStreams. */
  void update(std::vector<dataStream>& dataStreams);

private:
  /** @brief Configuration data pulled from config.toml. We only really need it for the folder in which the logs go. */
  ConfigData configData;
};
