// -*-c++-*-
#pragma once
#define MAINWINDOW_H

#include "build/ui_mainwindow.h"
#include "src/config.h"
#include "lib/cpptoml/cpptoml.h"
#include "lib/easylogging++/easylogging++.h"
#include "lib/qcustomplot/qcustomplot.h"

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

  void setupLogging();
  void setupPlots();
  void setupEngineControlUI();

  void updateDataTable();
  void updatePlots();

signals:
  void newDataAvailable();

public slots:
  void onNewDataAvailable();
  void msg();

private:
  QBluetoothSocket *socket;
  double data[2][9] = {0};
  Ui::MainWindow *ui;
  int64_t plotXAxisWidth = 40;
  std::string logFilePath = "./logs/";
  double dataWarningThresholds[9] = {0};
};
