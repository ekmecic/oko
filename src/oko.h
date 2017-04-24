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

class oko : public QMainWindow {
  Q_OBJECT

public:
  explicit oko(QWidget* parent = 0);
  ~oko();

  std::vector<dataStream> dataStreams;
  QBluetoothSocket*       socket;
  ConfigData              configData;

signals:
  void newDataAvailable();

public slots:
  void onNewDataAvailable();

private:
  Plotter*           plots;
  Table*             table;
  Logger*            logs;
  ConnectionHandler* connectionHandler;
  SerialParser*      parser;
  Ui::MainWindow*    ui;
};
