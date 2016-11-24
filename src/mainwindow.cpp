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

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

  ui->electricalPlot->addGraph();
  ui->electricalPlot->addGraph();
  ui->electricalPlot->addGraph();
  ui->electricalPlot->addGraph();
  ui->electricalPlot->graph(0)->setName("Battery current (A)");
  ui->electricalPlot->graph(0)->setPen(QPen(Qt::red));
  ui->electricalPlot->graph(1)->setName("Bus Voltage (V)");
  ui->electricalPlot->graph(1)->setPen(QPen(Qt::green));
  ui->electricalPlot->graph(2)->setName("Measured Phase Current (A)");
  ui->electricalPlot->graph(2)->setPen(QPen(Qt::blue));
  ui->electricalPlot->graph(3)->setName("Commanded Phase Current (A)");
  ui->electricalPlot->graph(3)->setPen(QPen(Qt::black));
  ui->electricalPlot->xAxis->setTicker(timeTicker);
  ui->electricalPlot->yAxis->setRange(0, 350);

  ui->mechanicalPlot->addGraph();
  ui->mechanicalPlot->addGraph();
  ui->mechanicalPlot->addGraph();
  ui->mechanicalPlot->graph(0)->setName("Speed (RPM)");
  ui->mechanicalPlot->graph(0)->setPen(QPen(Qt::red));
  ui->mechanicalPlot->graph(1)->setName("Throttle Output (%)");
  ui->mechanicalPlot->graph(1)->setPen(QPen(Qt::green));
  ui->mechanicalPlot->graph(2)->setName("Engine Temp. (°C)");
  ui->mechanicalPlot->graph(2)->setPen(QPen(Qt::blue));
  ui->mechanicalPlot->xAxis->setTicker(timeTicker);
  ui->mechanicalPlot->yAxis->setRange(0, 350);

  QFont legendFont = font();
  legendFont.setPointSize(8);
  ui->mechanicalPlot->legend->setVisible(true);
  ui->mechanicalPlot->legend->setFont(legendFont);
  ui->electricalPlot->legend->setVisible(true);
  ui->electricalPlot->legend->setFont(legendFont);

  connect(genData, &genBoardInterface::newDataAvailable, this,
          &MainWindow::onNewDataAvailable);

  QtConcurrent::run(genData, &genBoardInterface::makeNewFakeData);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onNewDataAvailable() {
  // clang-format off
  ui->dataTable->setItem(0, 1, new QTableWidgetItem(QString::number(genData->getBatteryCurrent())));
  ui->dataTable->setItem(1, 1, new QTableWidgetItem(QString::number(genData->getBusVoltage())));
  ui->dataTable->setItem(2, 1, new QTableWidgetItem(QString::number(genData->getMeasuredPhaseCurrent())));
  ui->dataTable->setItem(3, 1, new QTableWidgetItem(QString::number(genData->getCommandedPhaseCurrent())));
  ui->dataTable->setItem(4, 1, new QTableWidgetItem(QString::number(genData->getSpeed())));
  ui->dataTable->setItem(5, 1, new QTableWidgetItem(QString::number(genData->getThrottleOutput())));
  ui->dataTable->setItem(6, 1, new QTableWidgetItem(QString::number(genData->getEngineTemperature())));
  // clang-format on

  static QTime time(QTime::currentTime());
  double key = time.elapsed() / 1000.0;
  static double lastPointKey = 0;

  // clang-format off
  ui->electricalPlot->graph(0)->addData(key, genData->getBatteryCurrent());
  ui->electricalPlot->graph(1)->addData(key, genData->getBusVoltage());
  ui->electricalPlot->graph(2)->addData(key, genData->getMeasuredPhaseCurrent());
  ui->electricalPlot->graph(3)->addData(key, genData->getCommandedPhaseCurrent());
  ui->mechanicalPlot->graph(0)->addData(key, genData->getSpeed());
  ui->mechanicalPlot->graph(1)->addData(key, genData->getThrottleOutput());
  ui->mechanicalPlot->graph(2)->addData(key, genData->getEngineTemperature());
  // clang-format on

  lastPointKey = key;

  ui->electricalPlot->xAxis->setRange(key, 40, Qt::AlignRight);
  ui->electricalPlot->replot();
  ui->mechanicalPlot->xAxis->setRange(key, 40, Qt::AlignRight);
  ui->mechanicalPlot->replot();
}
