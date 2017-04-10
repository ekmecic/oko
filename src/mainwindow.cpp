#include "src/mainwindow.h"

INITIALIZE_EASYLOGGINGPP

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->dataTable->setColumnWidth(0, 180);
  ui->splitter->setSizes(QList<int>({575, 1000}));

  this->dataStreams = readConfig(configData);
  this->socket      = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

  connect(socket, &QBluetoothSocket::readyRead, this, &MainWindow::onNewDataAvailable);
  this->connectionHandler = new ConnectionHandler(configData);
  this->connectionHandler->setup(*socket);

  this->plots = new Plotter(ui->mechanicalPlot, ui->electricalPlot, configData);
  this->plots->setup(dataStreams);

  this->table = new Table(ui->dataTable, configData);
  this->table->setup(dataStreams);

  setupLogging(this->dataStreams, configData.logFilePath);
  connect(this->table, &Table::plotToggled, this->plots, &Plotter::onPlotToggled);
  connect(this->table, &Table::axisToggled, this->plots, &Plotter::onAxisToggled);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onNewDataAvailable() {
  parseSerial(this->socket, this->dataStreams);
  for (auto& stream : dataStreams) {
    stream.scaledValue = (stream.value - stream.typMin) * 100 / (stream.typMax - stream.typMin);
  }
  this->plots->update(dataStreams);
  this->table->update(dataStreams);
  logData(this->dataStreams);
}
