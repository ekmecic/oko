// -*-c++-*-
#pragma once

#include "build/ui_mainwindow.h"
#include "lib/cpptoml/cpptoml.h"
#include "lib/easylogging++/easylogging++.h"
#include "lib/qcustomplot/qcustomplot.h"
#include "src/config.h"
#include "src/dataStream.h"
#include "src/engineState.h"
#include "src/serialParser.h"

#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>
#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  std::vector<dataStream> vec;
  QBluetoothSocket *socket;

  void setupLogging();
  void setupPlots();
  void setupDataTable();
  void setupEngineControlUI();

  void updateDataTable();
  void updatePlots();

signals:
  void newDataAvailable();

public slots:
  void onNewDataAvailable();

private:
  double data[2][9] = {0};
  Ui::MainWindow *ui;
  int64_t plotXAxisWidth = 40;
  std::string logFilePath = "./logs/";
  double dataWarningThresholds[9] = {0};
};
