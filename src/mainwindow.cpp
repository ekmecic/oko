#include "src/mainwindow.h"

INITIALIZE_EASYLOGGINGPP

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->dataTable->setColumnWidth(0, 180);
  ui->dataTable->setColumnWidth(1, 70);
  ui->dataTable->setColumnWidth(2, 70);
  ui->splitter->setSizes(QList<int>({575, 1000}));

  this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
  socket->connectToService(QBluetoothAddress("00:06:66:82:79:5C"),
                           QBluetoothUuid::Sdp);
  connect(socket, &QBluetoothSocket::readyRead, this,
          &MainWindow::onNewDataAvailable);
  connect(socket, &QBluetoothSocket::connected, this,
          [] { qDebug() << "connected"; });

  this->vec = readConfig();
  setupLogging();
  setupDataTable();
  setupPlots();
  setupEngineControlUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onNewDataAvailable() {
  auto valueVec = parseSerial(this->socket);
  qDebug() << valueVec;
  if (valueVec.size() == vec.size()) {
    for (uint8_t i = 0; i < vec.size(); i++) {
      vec[i].value = valueVec.at(i);
    }
  }
  updateDataTable();
  updatePlots();
}

void MainWindow::setupLogging() {
  el::Configurations loggingConf;

  loggingConf.setToDefault();
  loggingConf.set(
      el::Level::Global, el::ConfigurationType::Filename,
      logFilePath.append("oko-%datetime{%Y-%M-%d-T%H:%m:%s}.log"));
  loggingConf.set(el::Level::Global, el::ConfigurationType::Format,
                  "%datetime{%Y-%M-%d-T%H:%m:%s:%g},%msg");
  loggingConf.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
  loggingConf.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
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
  uint8_t i = 0;
  for (auto &vec : vec) {
    if (vec.dataType == DataType::Electrical) {
      ui->electricalPlot->addGraph();
      vec.graphNum = i;
      ui->electricalPlot->graph(vec.graphNum)
          ->setName(QString::fromStdString(vec.name));
      ui->electricalPlot->graph(vec.graphNum)->setPen(QPen(vec.colour));
      i++;
    }
  }

  i = 0;
  for (auto &vec : vec) {
    if (vec.dataType == DataType::Mechanical) {
      ui->mechanicalPlot->addGraph();
      vec.graphNum = i;
      ui->mechanicalPlot->graph(vec.graphNum)
          ->setName(QString::fromStdString(vec.name));
      ui->mechanicalPlot->graph(vec.graphNum)->setPen(QPen(vec.colour));
      i++;
    }
  }
  ui->electricalPlot->xAxis->setTicker(timeTicker);
  ui->electricalPlot->yAxis->setRange(0, 350);
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

void MainWindow::setupDataTable() {
  for (auto &vec : vec) {
    if (vec.dataType != DataType::CurrentEngineState) {
      ui->dataTable->setItem(
          vec.position, 0,
          new QTableWidgetItem(QString::fromStdString(vec.name)));
      ui->dataTable->setItem(vec.position, 1,
                             new QTableWidgetItem(QString::number(0)));
      ui->dataTable->setItem(vec.position, 2,
                             new QTableWidgetItem(QString::number(0)));
      ui->dataTable->setItem(vec.position, 3,
                             new QTableWidgetItem(QString::number(0)));
    }
  }
}

void MainWindow::updateDataTable() {
  for (auto &vec : vec) {
    if (vec.dataType != DataType::CurrentEngineState) {
      auto val = vec.value * vec.multiplier;
      ui->dataTable->setItem(vec.position, 1,
                             new QTableWidgetItem(QString::number(val)));
      if ((val > vec.maxWarning || val < vec.minWarning) &&
          vec.dataType != DataType::Time) {
        ui->dataTable->item(vec.position, 1)->setBackground(Qt::yellow);
      }
      if (val < ui->dataTable->item(vec.position, 2)->text().toDouble()) {
        ui->dataTable->setItem(vec.position, 2,
                               new QTableWidgetItem(QString::number(val)));
      }
      if (val > ui->dataTable->item(vec.position, 3)->text().toDouble()) {
        ui->dataTable->setItem(vec.position, 3,
                               new QTableWidgetItem(QString::number(val)));
      }
    }
  }
}

void MainWindow::updatePlots() {
  static QTime time(QTime::currentTime());
  double key = time.elapsed() / 1000.0;

  for (auto &vec : vec) {
    if (vec.dataType == DataType::Electrical) {
      ui->electricalPlot->graph(vec.graphNum)->addData(key, vec.value);
    }
    if (vec.dataType == DataType::Mechanical) {
      ui->mechanicalPlot->graph(vec.graphNum)->addData(key, vec.value);
    }
  }

  // Shift the axis left for the new data and refresh the graph
  ui->electricalPlot->xAxis->setRange(key, plotXAxisWidth, Qt::AlignRight);
  ui->electricalPlot->replot();
  ui->mechanicalPlot->xAxis->setRange(key, plotXAxisWidth, Qt::AlignRight);
  ui->mechanicalPlot->replot();
}
