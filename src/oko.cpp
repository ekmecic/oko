#include "src/oko.h"

INITIALIZE_EASYLOGGINGPP

oko::oko(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->dataTable->setColumnWidth(0, 180);
  ui->splitter->setSizes(QList<int>({575, 1000}));

  dataStreams = readConfig(configData);
  socket      = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

  connect(socket, &QBluetoothSocket::readyRead, this, &oko::onNewDataAvailable);
  connectionHandler = new ConnectionHandler(socket, configData);
  connectionHandler->setup();

  parser = new SerialParser();

  plots = new Plotter(ui->mechanicalPlot, ui->electricalPlot, configData);
  plots->setup(dataStreams);

  table = new Table(ui->dataTable);
  table->setup(dataStreams);

  logs = new Logger(configData);
  logs->setup(dataStreams);

  // Toggle the axes and lines when the user clicks the checkboxes/radio buttons
  connect(table, &Table::graphToggled, plots, &Plotter::onGraphToggled);
  connect(table, &Table::axisToggled, plots, &Plotter::onAxisToggled);
}

oko::~oko() {
  delete ui;
}

void oko::onNewDataAvailable() {
  // Parse the raw ASCII and update the dataStreams with the new data
  parser->update(socket, dataStreams);
  // Scale values to be plotted, i.e. map the values from 0-100
  for (auto& stream : dataStreams) {
    stream.scaledValue =
      (stream.value - stream.typicalValues[0]) * 100 / (stream.typicalValues[1] - stream.typicalValues[0]);
  }
  // Update the plots, table, and logs
  plots->update(dataStreams);
  table->update(dataStreams);
  logs->update(dataStreams);
}
