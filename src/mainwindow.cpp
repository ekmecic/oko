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

  setupPlots();

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

void MainWindow::setupPlots() {
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

  // Add 4 graphs to the plot, one for each of the electrical data streams
  MainWindow::ui->electricalPlot->addGraph();
  MainWindow::ui->electricalPlot->addGraph();
  MainWindow::ui->electricalPlot->addGraph();
  MainWindow::ui->electricalPlot->addGraph();
  // Give a name for each graph (for the legend) and give it it's own color
  MainWindow::ui->electricalPlot->graph(0)->setName("Battery current (A)");
  MainWindow::ui->electricalPlot->graph(0)->setPen(QPen(Qt::red));
  MainWindow::ui->electricalPlot->graph(1)->setName("Bus Voltage (V)");
  MainWindow::ui->electricalPlot->graph(1)->setPen(QPen(Qt::green));
  MainWindow::ui->electricalPlot->graph(2)->setName("Measured Phase Current (A)");
  MainWindow::ui->electricalPlot->graph(2)->setPen(QPen(Qt::blue));
  MainWindow::ui->electricalPlot->graph(3)->setName("Commanded Phase Current (A)");
  MainWindow::ui->electricalPlot->graph(3)->setPen(QPen(Qt::black));
  // Make the x-axis dependent on time, and the y-axis an arbitrary number
  MainWindow::ui->electricalPlot->xAxis->setTicker(timeTicker);
  MainWindow::ui->electricalPlot->yAxis->setRange(0, 350);

  // Exact same stuff as above, just for the mechanical data plot instead
  MainWindow::ui->mechanicalPlot->addGraph();
  MainWindow::ui->mechanicalPlot->addGraph();
  MainWindow::ui->mechanicalPlot->addGraph();
  MainWindow::ui->mechanicalPlot->graph(0)->setName("Speed (RPM)");
  MainWindow::ui->mechanicalPlot->graph(0)->setPen(QPen(Qt::red));
  MainWindow::ui->mechanicalPlot->graph(1)->setName("Throttle Output (%)");
  MainWindow::ui->mechanicalPlot->graph(1)->setPen(QPen(Qt::green));
  MainWindow::ui->mechanicalPlot->graph(2)->setName("Engine Temp. (°C)");
  MainWindow::ui->mechanicalPlot->graph(2)->setPen(QPen(Qt::blue));
  MainWindow::ui->mechanicalPlot->xAxis->setTicker(timeTicker);
  MainWindow::ui->mechanicalPlot->yAxis->setRange(0, 350);

  // Inherit the font of the main window, but make it a little bit smaller
  QFont legendFont = font();
  legendFont.setPointSize(8);
  // Enable legends for both plots and set their fonts to the smaller version
  MainWindow::ui->electricalPlot->legend->setVisible(true);
  MainWindow::ui->electricalPlot->legend->setFont(legendFont);
  MainWindow::ui->mechanicalPlot->legend->setVisible(true);
  MainWindow::ui->mechanicalPlot->legend->setFont(legendFont);
}
