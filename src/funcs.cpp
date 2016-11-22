#include "funcs.h"

void updateTable(QTableWidget &tbl, genBoardInterface &data) {
  // tbl.setItem(0, 1, new QTableWidgetItem(QString::number(data.getBatteryCurrent())));
  tbl.setItem(0, 1, new QTableWidgetItem(QString::number(data.getBatteryCurrent())));
  tbl.setItem(1, 1, new QTableWidgetItem(QString::number(data.getBusVoltage())));
  tbl.setItem(2, 1, new QTableWidgetItem(QString::number(data.getMeasuredPhaseCurrent())));
  tbl.setItem(3, 1, new QTableWidgetItem(QString::number(data.getCommandedPhaseCurrent())));
  tbl.setItem(4, 1, new QTableWidgetItem(QString::number(data.getSpeed())));
  tbl.setItem(5, 1, new QTableWidgetItem(QString::number(data.getThrottleOutput())));
  tbl.setItem(6, 1, new QTableWidgetItem(QString::number(data.getEngineTemperature())));
}
