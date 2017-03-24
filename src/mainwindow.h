// -*-c++-*-
#pragma once

#include "build/ui_mainwindow.h"
#include "lib/qcustomplot/qcustomplot.h"
#include "lib/qtwaitingspinner/waitingspinnerwidget.h"
#include "src/config.h"
#include "src/dataStream.h"
#include "src/engineState.h"
#include "src/logging.h"
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
  QBluetoothSocket *      socket;
  ConfigData              configData;

  void setupPlots();
  void setupDataTable();

  void updateDataTable();
  void updatePlots();

signals:
  void newDataAvailable();

public slots:
  void onNewDataAvailable();

private:
  Ui::MainWindow *ui;
};
