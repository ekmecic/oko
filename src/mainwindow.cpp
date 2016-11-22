#include "mainwindow.h"
#include "./build/ui_mainwindow.h"
#include "controllerData.h"
#include "funcs.h"
#include "genBoardInterface.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->dataTable->setColumnWidth(0, 170);

  // Put some dummy text in all the gains/setpoints fields
  ui->manualThrottleField->setText("1001%");
  ui->scmSPField->setText("500");
  ui->scmKIField->setText("2");
  ui->scmKPField->setText("1");
  ui->ccmSPField->setText("500");
  ui->ccmKIField->setText("2");
  ui->ccmKPField->setText("1");

  genBoardInterface generatorData;

  auto timer = new QTimer();
  connect(timer, &QTimer::timeout, [&] {
      updateTable(*MainWindow::ui->dataTable, generatorData);
  });
  timer->setInterval(250);
  timer->start();
}

MainWindow::~MainWindow() { delete ui; }
