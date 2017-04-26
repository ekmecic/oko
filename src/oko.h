// -*-c++-*-
#pragma once

#include "build/ui_mainwindow.h"
#include "src/config.h"
#include "src/connectionHandler.h"
#include "src/dataStream.h"
#include "src/engineState.h"
#include "src/logger.h"
#include "src/plotter.h"
#include "src/serialParser.h"
#include "src/table.h"

#include <QMainWindow>
#include <QTableWidget>

/** @brief Everyone's daddy: initializes all subcomponents and calls them when new data is received.
    @author Emil Ekmečić
    @date April 2017 */
class oko : public QMainWindow {
  Q_OBJECT

public:
  explicit oko(QWidget* parent = 0);
  ~oko();

  /** @brief All of the dataStreams. */
  std::vector<dataStream> dataStreams;
  /** @brief Bluetooth socket to be connected to the Bluetooth module. */
  QBluetoothSocket* socket;
  /** @brief Configuration data pulled from config.toml. Passed to whoever needs it. */
  ConfigData configData;

signals:
  /** @brief Emitted when new data is available from the Bluetooth module. */
  void newDataAvailable();

public slots:
  /** @brief Called when new data is received. Updates Plotter/Table/Logger. */
  void onNewDataAvailable();

private:
  /** @brief Initializes and updates the plots. */
  Plotter* plots;
  /** @brief Initializes and updates the table. */
  Table* table;
  /** @brief Initializes and updates the logs. */
  Logger* logs;
  /** @brief Initializes and controls the Bluetooth connection to the Bluetooth module. */
  ConnectionHandler* connectionHandler;
  /** @brief Parses raw ASCII from the Bluetooth module into usable values. */
  SerialParser* parser;
  /** @brief Provides an interface to the UI.*/
  Ui::MainWindow* ui;
};
