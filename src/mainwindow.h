// -*-c++-*-
#pragma once
#define MAINWINDOW_H

#include "lib/qcustomplot/qcustomplot.h"
#include "build/ui_mainwindow.h"
#include "lib/cpptoml/cpptoml.h"
#include "lib/easylogging++/easylogging++.h"

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
  void configure();

  void updateDataTable();
  void updatePlots();

public slots:
  void onNewDataAvailable();

private:
  double data[2][7] = {0};
  Ui::MainWindow *ui;
  int64_t plotXAxisWidth = 40;
  std::string logFilePath = "./logs/";
  double dataWarningThresholds[7] = {0};
};
