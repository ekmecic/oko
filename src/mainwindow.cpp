#include "mainwindow.h"

genBoardInterface *genData = new genBoardInterface();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Put some dummy text in all the gains/setpoints fields
  ui->manualThrottleField->setText("1001%");
  ui->scmSPField->setText("500");
  ui->scmKIField->setText("2");
  ui->scmKPField->setText("1");
  ui->ccmSPField->setText("500");
  ui->ccmKIField->setText("2");
  ui->ccmKPField->setText("1");

  connect(genData,
          &genBoardInterface::newDataAvailable,
          this,
          &MainWindow::onNewDataAvailable);

  QtConcurrent::run(genData, &genBoardInterface::makeNewFakeData);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onNewDataAvailable() {
  ui->dataTable->setItem(0, 1, new QTableWidgetItem(QString::number(genData->getBatteryCurrent())));
  ui->dataTable->setItem(1, 1, new QTableWidgetItem(QString::number(genData->getBusVoltage())));
  ui->dataTable->setItem(2, 1, new QTableWidgetItem(QString::number(genData->getMeasuredPhaseCurrent())));
  ui->dataTable->setItem(3, 1, new QTableWidgetItem(QString::number(genData->getCommandedPhaseCurrent())));
  ui->dataTable->setItem(4, 1, new QTableWidgetItem(QString::number(genData->getSpeed())));
  ui->dataTable->setItem(5, 1, new QTableWidgetItem(QString::number(genData->getThrottleOutput())));
  ui->dataTable->setItem(6, 1, new QTableWidgetItem(QString::number(genData->getEngineTemperature())));
}
