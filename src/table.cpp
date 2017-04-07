#include "src/table.h"

Table::Table(QTableWidget* _table, ConfigData _configData) {
  this->table      = _table;
  this->configData = _configData;
}

void Table::setup(std::vector<dataStream>& dataStreams) {
  this->table->setColumnWidth(1, 70);
  this->table->setColumnWidth(2, 70);
  this->table->setColumnWidth(3, 70);

  for (auto& stream : dataStreams) {
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      this->table->setItem(stream.position, 0, new QTableWidgetItem(stream.name));
      this->table->setItem(stream.position, 1, new QTableWidgetItem(QString::number(0)));
      this->table->setItem(stream.position, 2, new QTableWidgetItem(QString::number(0)));
      this->table->setItem(stream.position, 3, new QTableWidgetItem(QString::number(0)));

      QCheckBox*   plotCheckBox         = new QCheckBox();
      QWidget*     plotLayoutWidget     = new QWidget();
      QHBoxLayout* plotHorizontalLayout = new QHBoxLayout();
      plotHorizontalLayout->setAlignment(Qt::AlignCenter);
      plotHorizontalLayout->addWidget(plotCheckBox);
      plotLayoutWidget->setLayout(plotHorizontalLayout);
      this->table->setCellWidget(stream.position, 4, plotLayoutWidget);
      plotCheckBox->setChecked(true);

      QCheckBox*   axisCheckBox         = new QCheckBox();
      QWidget*     axisLayoutWidget     = new QWidget();
      QHBoxLayout* axisHorizontalLayout = new QHBoxLayout();
      axisHorizontalLayout->setAlignment(Qt::AlignCenter);
      axisHorizontalLayout->addWidget(axisCheckBox);
      axisLayoutWidget->setLayout(axisHorizontalLayout);
      this->table->setCellWidget(stream.position, 5, axisLayoutWidget);

      connect(plotCheckBox, &QCheckBox::stateChanged, this, [&] { emit plotToggled(stream); });
      connect(axisCheckBox, &QCheckBox::stateChanged, this, [&] { emit axisToggled(stream); });
    } else {
      this->table->setItem(stream.position, 0, new QTableWidgetItem(stream.name));
    }
  }
}

void Table::update(std::vector<dataStream>& dataStreams) {
  for (auto& stream : dataStreams) {
    auto val = stream.value * stream.multiplier;
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      this->table->setItem(stream.position, 1, new QTableWidgetItem(QString::number(val)));
      if ((val > stream.maxWarning || val < stream.minWarning) && stream.dataType != DataType::Time) {
        this->table->item(stream.position, 1)->setBackground(Qt::yellow);
      }
      if (val < this->table->item(stream.position, 2)->text().toDouble()) {
        this->table->setItem(stream.position, 2, new QTableWidgetItem(QString::number(val)));
      }
      if (val > this->table->item(stream.position, 3)->text().toDouble()) {
        this->table->setItem(stream.position, 3, new QTableWidgetItem(QString::number(val)));
      }
    } else if (stream.dataType == DataType::CurrentEngineState) {
      this->table->setItem(stream.position, 1, new QTableWidgetItem(parseEngineState(stream.value)));
    } else if (stream.dataType == DataType::Time) {
      this->table->setItem(stream.position, 1, new QTableWidgetItem(QString::number(stream.value)));
    }
  }
}
