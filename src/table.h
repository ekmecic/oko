// -*-c++-*-
#pragma once

#include <QCheckBox>
#include <QHBoxLayout>
#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "src/config.h"
#include "src/dataStream.h"

class Table : public QObject {
  Q_OBJECT
public:
  Table(QTableWidget* _table, ConfigData _configData);

  void setup(std::vector<dataStream>& dataStreams);
  void update(std::vector<dataStream>& dataStreams);

signals:
  void plotToggled(dataStream stream);
  void axisToggled(dataStream stream);

private:
  QTableWidget* table;
  ConfigData    configData;
};
