#include "src/mainwindow.h"

INITIALIZE_EASYLOGGINGPP

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->dataTable->setColumnWidth(0, 180);
  ui->splitter->setSizes(QList<int>({575, 1000}));

  ConfigData cnf;
  this->vec                     = readConfig(cnf);
  configData                    = cnf;
  WaitingSpinnerWidget *spinner = new WaitingSpinnerWidget(this, Qt::ApplicationModal, true);
  spinner->setRoundness(70.0);
  spinner->setNumberOfLines(16);
  spinner->setLineLength(10);
  spinner->setLineWidth(10);
  spinner->setInnerRadius(20);
  spinner->setLineLength(40);
  spinner->setRevolutionsPerSecond(1);
  this->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
  connect(socket, &QBluetoothSocket::readyRead, this, &MainWindow::onNewDataAvailable);
  connect(socket, &QBluetoothSocket::connected, spinner, &WaitingSpinnerWidget::stop);
  spinner->start();
  socket->connectToService(QBluetoothAddress(QString::fromStdString(configData.MACAddress)), QBluetoothUuid::Sdp);

  setupLogging(this->vec, configData.logFilePath);
  setupPlots();
  setupDataTable();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onNewDataAvailable() {
  parseSerial(this->socket, this->vec);
  for (auto &vec : vec) {
    vec.scaledValue = (vec.value - vec.typMin) * 100 / (vec.typMax - vec.typMin);
  }
  updateDataTable();
  updatePlots();
  logData(this->vec);
}

void MainWindow::setupPlots() {
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  uint8_t                           i = 0;
  for (auto &vec : vec) {
    if (vec.dataType == DataType::Mechanical) {
      ui->mechanicalPlot->addGraph();
      vec.graphNum = i;
      ui->mechanicalPlot->graph(vec.graphNum)->setName(QString::fromStdString(vec.name));
      ui->mechanicalPlot->graph(vec.graphNum)->setPen(QPen(vec.colour));
      i++;
    }
  }
  i = 0;
  for (auto &vec : vec) {
    if (vec.dataType == DataType::Electrical) {
      ui->electricalPlot->addGraph();
      vec.graphNum = i;
      ui->electricalPlot->graph(vec.graphNum)->setName(QString::fromStdString(vec.name));
      ui->electricalPlot->graph(vec.graphNum)->setPen(QPen(vec.colour));
      i++;
    }
  }

  ui->mechanicalPlot->xAxis->setTicker(timeTicker);
  ui->mechanicalPlot->yAxis->setRange(configData.mechPlotMin, configData.mechPlotMax);
  ui->electricalPlot->xAxis->setTicker(timeTicker);
  ui->electricalPlot->yAxis->setRange(configData.elecPlotMin, configData.elecPlotMax);

  // Inherit the font of the main window, but make it a little bit smaller
  QFont legendFont = font();
  legendFont.setPointSize(8);
  // Enable legends for both plots and set their fonts to the smaller version
  ui->mechanicalPlot->legend->setVisible(true);
  ui->mechanicalPlot->legend->setFont(legendFont);
  ui->mechanicalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
  ui->electricalPlot->legend->setVisible(true);
  ui->electricalPlot->legend->setFont(legendFont);
  ui->electricalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}

void MainWindow::setupDataTable() {
  ui->dataTable->setColumnWidth(1, 70);
  ui->dataTable->setColumnWidth(2, 70);
  ui->dataTable->setColumnWidth(3, 70);

  for (auto &vec : vec) {
    if (vec.dataType != DataType::CurrentEngineState) {
      ui->dataTable->setItem(vec.position, 0, new QTableWidgetItem(QString::fromStdString(vec.name)));
      ui->dataTable->setItem(vec.position, 1, new QTableWidgetItem(QString::number(0)));
      ui->dataTable->setItem(vec.position, 2, new QTableWidgetItem(QString::number(0)));
      ui->dataTable->setItem(vec.position, 3, new QTableWidgetItem(QString::number(0)));

      QCheckBox *plotCheckBox = new QCheckBox();
      plotCheckBox->setChecked(true);
      ui->dataTable->setCellWidget(vec.position, 4, plotCheckBox);
      connect(plotCheckBox, &QCheckBox::stateChanged, this, [&] {
        if (vec.dataType == DataType::Electrical && ui->electricalPlot->graph(vec.graphNum)->visible())
          ui->electricalPlot->graph(vec.graphNum)->setVisible(false);
        else if (vec.dataType == DataType::Electrical && !ui->electricalPlot->graph(vec.graphNum)->visible())
          ui->electricalPlot->graph(vec.graphNum)->setVisible(true);
        else if (vec.dataType == DataType::Mechanical && ui->mechanicalPlot->graph(vec.graphNum)->visible())
          ui->mechanicalPlot->graph(vec.graphNum)->setVisible(false);
        else if (vec.dataType == DataType::Mechanical && !ui->mechanicalPlot->graph(vec.graphNum)->visible())
          ui->mechanicalPlot->graph(vec.graphNum)->setVisible(true);
      });
      QCheckBox *axisCheckBox = new QCheckBox();
      ui->dataTable->setCellWidget(vec.position, 5, axisCheckBox);
      connect(axisCheckBox, &QCheckBox::stateChanged, this, [&] {
        if (vec.dataType == DataType::Electrical) {
          ui->electricalPlot->yAxis2->setRange(vec.typMin, vec.typMax);
          ui->electricalPlot->yAxis2->setVisible(true);
        } else if (vec.dataType == DataType::Mechanical) {
          ui->mechanicalPlot->yAxis2->setRange(vec.typMin, vec.typMax);
          ui->mechanicalPlot->yAxis2->setVisible(true);
        }
      });
    } else {
      ui->dataTable->setItem(vec.position, 0, new QTableWidgetItem(QString::fromStdString(vec.name)));
    }
  }
}

void MainWindow::updateDataTable() {
  for (auto &vec : vec) {
    if (vec.dataType != DataType::CurrentEngineState) {
      auto val = vec.value * vec.multiplier;
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
    } else {
      ui->dataTable->setItem(vec.position, 1, new QTableWidgetItem(parseEngineState(vec.value)));
    }
  }
}

void MainWindow::updatePlots() {
  static QTime time(QTime::currentTime());
  double       key = time.elapsed() / 1000.0;

  for (auto &vec : vec) {
    if (vec.dataType == DataType::Mechanical) {
      ui->mechanicalPlot->graph(vec.graphNum)->addData(key, vec.scaledValue);
    }
    if (vec.dataType == DataType::Electrical) {
      ui->electricalPlot->graph(vec.graphNum)->addData(key, vec.scaledValue);
    }
  }

  // Shift the axis left for the new data and refresh the graph
  ui->mechanicalPlot->xAxis->setRange(key, configData.plotWidth, Qt::AlignRight);
  ui->mechanicalPlot->replot();
  ui->electricalPlot->xAxis->setRange(key, configData.plotWidth, Qt::AlignRight);
  ui->electricalPlot->replot();
}
