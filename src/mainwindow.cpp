#include "src/mainwindow.h"

INITIALIZE_EASYLOGGINGPP

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->dataTable->setColumnWidth(0, 180);
  ui->splitter->setSizes(QList<int>({575, 1000}));

  dataStreams = readConfig(configData);
  socket      = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

  connect(socket, &QBluetoothSocket::readyRead, this, &MainWindow::onNewDataAvailable);
  connectionHandler = new ConnectionHandler(configData);
  connectionHandler->setup(*socket);

  plots = new Plotter(ui->mechanicalPlot, ui->electricalPlot, configData);
  plots->setup(dataStreams);

  table = new Table(ui->dataTable, configData);
  table->setup(dataStreams);

  setupLogging(dataStreams, configData.logFolderPath);
  connect(table, &Table::plotToggled, plots, &Plotter::onPlotToggled);
  connect(table, &Table::axisToggled, plots, &Plotter::onAxisToggled);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onNewDataAvailable() {
  parseSerial(socket, dataStreams);
  for (auto& stream : dataStreams) {
    stream.scaledValue =
        (stream.value - stream.typicalValues[0]) * 100 / (stream.typicalValues[1] - stream.typicalValues[0]);
  }
  plots->update(dataStreams);
  table->update(dataStreams);
  logData(dataStreams);
}
