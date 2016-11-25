// -*-c++-*-
#pragma once
#define MAINWINDOW_H

#include "lib/qcustomplot/qcustomplot.h"
#include "build/ui_mainwindow.h"
#include "src/genBoardInterface.h"
#include "lib/easylogging++/easylogging++.h"

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
  void setupLogging();

signals:
  void quitApplication();

public slots:
  void onNewDataAvailable();

private:
  Ui::MainWindow *ui;
};
