// -*-c++-*-
#pragma once

#include "build/ui_mainwindow.h"
#include "src/config.h"
#include "src/dataStream.h"
#include "src/engineState.h"
#include "src/logging.h"
#include "src/plotter.h"
#include "src/serialParser.h"
#include "src/table.h"

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
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

  std::vector<dataStream> vec;
  QBluetoothSocket*       socket;
  ConfigData              configData;

signals:
  void newDataAvailable();

public slots:
  void onNewDataAvailable();

private:
  Plotter*        plots;
  Table*          table;
  Ui::MainWindow* ui;
};
