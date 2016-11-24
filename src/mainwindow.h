#pragma once
#define MAINWINDOW_H

#include "./build/ui_mainwindow.h"
#include "../lib/qcustomplot.h"
#include "genBoardInterface.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void setupPlots();
  void setupEngineControlUI();
  void updateDataTable();
  void updatePlots();

public slots:
  void onNewDataAvailable();

private:
  Ui::MainWindow *ui;
};
