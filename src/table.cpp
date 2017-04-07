#include "src/table.h"

Table::Table(QTableWidget* _table, ConfigData _configData) {
  this->table      = _table;
  this->configData = _configData;
}

void Table::setup(std::vector<dataStream>& dataStreams) {
  mechanicalButtons = new QButtonGroup(this);
  electricalButtons = new QButtonGroup(this);

  for (auto& stream : dataStreams) {
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      this->table->setItem(stream.position, TableColumn::Field, new QTableWidgetItem(stream.name));
      this->table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(0)));
      this->table->setItem(stream.position, TableColumn::Min, new QTableWidgetItem(QString::number(0)));
      this->table->setItem(stream.position, TableColumn::Max, new QTableWidgetItem(QString::number(0)));

      QCheckBox*   plotCheckBox         = new QCheckBox();
      QWidget*     plotLayoutWidget     = new QWidget();
      QHBoxLayout* plotHorizontalLayout = new QHBoxLayout();
      plotHorizontalLayout->setAlignment(Qt::AlignCenter);
      plotHorizontalLayout->addWidget(plotCheckBox);
      plotLayoutWidget->setLayout(plotHorizontalLayout);
      this->table->setCellWidget(stream.position, TableColumn::Plot, plotLayoutWidget);
      plotCheckBox->setChecked(true);

      QRadioButton* axisRadioButton      = new QRadioButton();
      QWidget*      axisLayoutWidget     = new QWidget();
      QHBoxLayout*  axisHorizontalLayout = new QHBoxLayout();
      axisHorizontalLayout->setAlignment(Qt::AlignCenter);
      axisHorizontalLayout->addWidget(axisRadioButton);
      axisLayoutWidget->setLayout(axisHorizontalLayout);
      this->table->setCellWidget(stream.position, TableColumn::Axis, axisLayoutWidget);

      if (stream.dataType == DataType::Mechanical) {
        mechanicalButtons->addButton(axisRadioButton);
      }
      if (stream.dataType == DataType::Electrical) {
        electricalButtons->addButton(axisRadioButton);
      }
      connect(plotCheckBox, &QCheckBox::stateChanged, this, [&] { emit plotToggled(stream); });
      connect(axisRadioButton, &QCheckBox::pressed, this, [&] { emit axisToggled(stream); });
    } else {
      this->table->setItem(stream.position, 0, new QTableWidgetItem(stream.name));
    }
  }
}

void Table::update(std::vector<dataStream>& dataStreams) {
  for (auto& stream : dataStreams) {
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      this->table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(stream.value)));
      if ((stream.value > stream.maxWarning || stream.value < stream.minWarning) && stream.dataType != DataType::Time) {
        this->table->item(stream.position, TableColumn::Value)->setBackground(Qt::yellow);
      }
      if (stream.value < this->table->item(stream.position, TableColumn::Min)->text().toDouble()) {
        this->table->setItem(stream.position, TableColumn::Min, new QTableWidgetItem(QString::number(stream.value)));
      }
      if (stream.value > this->table->item(stream.position, TableColumn::Max)->text().toDouble()) {
        this->table->setItem(stream.position, TableColumn::Max, new QTableWidgetItem(QString::number(stream.value)));
      }
    } else if (stream.dataType == DataType::CurrentEngineState) {
      this->table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(parseEngineState(stream.value)));
    } else if (stream.dataType == DataType::Time) {
      this->table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(stream.value)));
    }
  }
}
