#pragma once
#define MAINWINDOW_H

#include "genBoardInterface.h"
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

  public slots:
    void onNewDataAvailable();

 private:
    Ui::MainWindow *ui;
};
