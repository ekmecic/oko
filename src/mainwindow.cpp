#include "src/mainwindow.h"

INITIALIZE_EASYLOGGINGPP

genBoardInterface *genData = new genBoardInterface();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  setupLogging();
  configure();
  setupPlots();
  setupEngineControlUI();

  connect(this, &MainWindow::quitApplication, genData,
          &genBoardInterface::stopThread);
  connect(genData, &genBoardInterface::newDataAvailable, this,
          &MainWindow::onNewDataAvailable);
  QtConcurrent::run(genData, &genBoardInterface::makeNewFakeData);
}

MainWindow::~MainWindow() {
  emit quitApplication();
  delete ui;
}

void MainWindow::onNewDataAvailable() {
  updateDataTable();
  updatePlots();
}

void MainWindow::configure() {
  try {
    auto config = cpptoml::parse_file("../config.toml");
  } catch (cpptoml::parse_exception &tomlParseError) {
    LOG(INFO) << "ERROR: Parsing the config file returned an error!";
    LOG(INFO) << tomlParseError.what();
  }
  auto config = cpptoml::parse_file("/home/emil/pegasus/oko/config.toml");
}

void MainWindow::setupLogging() {
  el::Configurations loggingConf;

  loggingConf.setToDefault();
  loggingConf.set(el::Level::Global, el::ConfigurationType::Filename,
                  "./logs/PegasusGE30-%datetime{%Y-%M-%d-T%H:%m:%s}.log");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Format,
                  "%datetime{%Y-%M-%d-T%H:%m:%s:%g},%msg");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Enabled,
                  "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToFile,
                  "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput,
                  "false");

  el::Loggers::reconfigureAllLoggers(loggingConf);
  LOG(INFO) << "FORMAT:";
  LOG(INFO) << "BatteryCurrent,BusVoltage,MeasuredPhaseCurrent,"
               "CommandedPhaseCurrent,Speed,ThrottleOutput,EngineTemperature";
  LOG(INFO) << "Time is in the local time of the computer running oko.";
}

void MainWindow::setupPlots() {
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

  // Add 4 graphs to the plot, one for each of the electrical data streams
  ui->electricalPlot->addGraph();
  ui->electricalPlot->addGraph();
  ui->electricalPlot->addGraph();
  ui->electricalPlot->addGraph();
  // Give a name for each graph (for the legend) and give it it's own color
  ui->electricalPlot->graph(0)->setName("Battery current (A)");
  ui->electricalPlot->graph(0)->setPen(QPen(Qt::red));
  ui->electricalPlot->graph(1)->setName("Bus Voltage (V)");
  ui->electricalPlot->graph(1)->setPen(QPen(Qt::green));
  ui->electricalPlot->graph(2)->setName("Measured Phase Current (A)");
  ui->electricalPlot->graph(2)->setPen(QPen(Qt::blue));
  ui->electricalPlot->graph(3)->setName("Commanded Phase Current (A)");
  ui->electricalPlot->graph(3)->setPen(QPen(Qt::black));
  // Make the x-axis dependent on time, and the y-axis an arbitrary number
  ui->electricalPlot->xAxis->setTicker(timeTicker);
  ui->electricalPlot->yAxis->setRange(0, 350);

  // Exact same stuff as above, just for the mechanical data plot instead
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

  // Inherit the font of the main window, but make it a little bit smaller
  QFont legendFont = font();
  legendFont.setPointSize(8);
  // Enable legends for both plots and set their fonts to the smaller version
  ui->electricalPlot->legend->setVisible(true);
  ui->electricalPlot->legend->setFont(legendFont);
  ui->electricalPlot->axisRect()->insetLayout()->setInsetAlignment(
      0, Qt::AlignLeft | Qt::AlignTop);
  ui->mechanicalPlot->legend->setVisible(true);
  ui->mechanicalPlot->legend->setFont(legendFont);
  ui->mechanicalPlot->axisRect()->insetLayout()->setInsetAlignment(
      0, Qt::AlignLeft | Qt::AlignTop);
}

void MainWindow::setupEngineControlUI() {
  // Put some dummy text in all the gains/setpoints fields
  ui->manualThrottleField->setText("1001%");
  ui->scmSPField->setText("500");
  ui->scmKIField->setText("2");
  ui->scmKPField->setText("1");
  ui->ccmSPField->setText("500");
  ui->ccmKIField->setText("2");
  ui->ccmKPField->setText("1");
}

void MainWindow::updateDataTable() {
  // clang-format off
  ui->dataTable->setItem(0, 1, new QTableWidgetItem(QString::number(genData->getBatteryCurrent())));
  ui->dataTable->setItem(1, 1, new QTableWidgetItem(QString::number(genData->getBusVoltage())));
  ui->dataTable->setItem(2, 1, new QTableWidgetItem(QString::number(genData->getMeasuredPhaseCurrent())));
  ui->dataTable->setItem(3, 1, new QTableWidgetItem(QString::number(genData->getCommandedPhaseCurrent())));
  ui->dataTable->setItem(4, 1, new QTableWidgetItem(QString::number(genData->getSpeed())));
  ui->dataTable->setItem(5, 1, new QTableWidgetItem(QString::number(genData->getThrottleOutput())));
  ui->dataTable->setItem(6, 1, new QTableWidgetItem(QString::number(genData->getEngineTemperature())));
  // clang-format on
}

void MainWindow::updatePlots() {
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

  // Shift the axis left for the new data and refresh the graph
  ui->electricalPlot->xAxis->setRange(key, 40, Qt::AlignRight);
  ui->electricalPlot->replot();
  ui->mechanicalPlot->xAxis->setRange(key, 40, Qt::AlignRight);
  ui->mechanicalPlot->replot();
}
