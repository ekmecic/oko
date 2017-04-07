#include "src/mainwindow.h"

INITIALIZE_EASYLOGGINGPP

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->dataTable->setColumnWidth(0, 180);
  ui->splitter->setSizes(QList<int>({575, 1000}));

  this->vec    = readConfig(configData);
  this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

  connect(socket, &QBluetoothSocket::readyRead, this, &MainWindow::onNewDataAvailable);
  socket->connectToService(QBluetoothAddress(configData.MACAddress), QBluetoothUuid::Sdp);
  connect(socket, &QBluetoothSocket::disconnected, this, [&] {
    socket->connectToService(QBluetoothAddress(configData.MACAddress), QBluetoothUuid::Sdp);
  });

  this->plots = new Plotter(ui->mechanicalPlot, ui->electricalPlot, configData);
  this->plots->setup(vec);
  this->table = new Table(ui->dataTable, configData);
  this->table->setup(vec);
  setupLogging(this->vec, configData.logFilePath);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onNewDataAvailable() {
  parseSerial(this->socket, this->vec);
  for (auto& vec : vec) {
    vec.scaledValue = ((vec.value * vec.multiplier) - vec.typMin) * 100 / (vec.typMax - vec.typMin);
  }
  updateDataTable();
  this->plots->update(vec);
  logData(this->vec);
}

void MainWindow::updateDataTable() {
  for (auto& vec : vec) {
    auto val = vec.value * vec.multiplier;
    if (vec.dataType != DataType::CurrentEngineState && vec.dataType != DataType::Time) {
      ui->dataTable->setItem(vec.position, 1, new QTableWidgetItem(QString::number(val)));
      if ((val > vec.maxWarning || val < vec.minWarning) && vec.dataType != DataType::Time) {
        ui->dataTable->item(vec.position, 1)->setBackground(Qt::yellow);
      }
      if (val < ui->dataTable->item(vec.position, 2)->text().toDouble()) {
        ui->dataTable->setItem(vec.position, 2, new QTableWidgetItem(QString::number(val)));
      }
      if (val > ui->dataTable->item(vec.position, 3)->text().toDouble()) {
        ui->dataTable->setItem(vec.position, 3, new QTableWidgetItem(QString::number(val)));
      }
    } else if (vec.dataType == DataType::CurrentEngineState) {
      ui->dataTable->setItem(vec.position, 1, new QTableWidgetItem(parseEngineState(vec.value)));
    } else if (vec.dataType == DataType::Time) {
      ui->dataTable->setItem(vec.position, 1, new QTableWidgetItem(QString::number(vec.value)));
    }
  }
}
