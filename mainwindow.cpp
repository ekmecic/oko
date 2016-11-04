#include "mainwindow.h"
#include "./build/ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QTimer>
#include <cstdlib>

double getRandNum() { return rand() / 1e9; }

void updateTableCell(QTableWidget &tbl);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->dataTable->setColumnWidth(0, 170);

  // Put some dummy text in all the gains/setpoints fields
  ui->manualThrottleField->setText("1001%");
  ui->scmSPField->setText("500");
  ui->scmKIField->setText("2");
  ui->scmKPField->setText("1");
  ui->ccmSPField->setText("500");
  ui->ccmKIField->setText("2");
  ui->ccmKPField->setText("1");

  auto timer = new QTimer(parent);
  connect(timer, &QTimer::timeout,
          [&] { updateTableCell(*MainWindow::ui->dataTable); });
  timer->setInterval(75);
  timer->start();

  // QTimer::singleShot(10, [&] {
  //     updateTableCell(*MainWindow::ui->dataTable);
  // });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_manualThrottleButton_clicked() {
  // check that the manualThrottleField value differs from the value supplied by
  // the Generator control board
}

void MainWindow::on_ESTOPButton_clicked() {
  // Kill the engine
  QMessageBox msgBox;
  msgBox.setText("The ESTOP button was clicked. Engine stopping now");
  msgBox.exec();
}

void MainWindow::on_scmSPButton_clicked() {
  ui->scmSPField->setText("setpoint");
}

void updateTableCell(QTableWidget &tbl) {
  tbl.setItem(0, 1, new QTableWidgetItem(QString::number(0.75 * getRandNum())));
  tbl.setItem(1, 1, new QTableWidgetItem(QString::number(getRandNum())));
  tbl.setItem(2, 1, new QTableWidgetItem(QString::number(2 * getRandNum())));
  tbl.setItem(3, 1, new QTableWidgetItem(QString::number(2.5 * getRandNum())));
  tbl.setItem(4, 1, new QTableWidgetItem(QString::number(1.25 * getRandNum())));
  tbl.setItem(5, 1, new QTableWidgetItem(QString::number(0.5 * getRandNum())));
  tbl.setItem(6, 1, new QTableWidgetItem(QString::number(0.25 * getRandNum())));
}
