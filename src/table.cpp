#include "src/table.h"

Table::Table(QTableWidget* _table, ConfigData _configData) {
  table      = _table;
  configData = _configData;
}

void Table::setup(std::vector<dataStream>& dataStreams) {
  mechanicalButtons = new QButtonGroup(this);
  electricalButtons = new QButtonGroup(this);

  for (auto& stream : dataStreams) {
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      table->setItem(stream.position, TableColumn::Field, new QTableWidgetItem(stream.name));
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(0)));
      table->setItem(stream.position, TableColumn::Min, new QTableWidgetItem(QString::number(0)));
      table->setItem(stream.position, TableColumn::Max, new QTableWidgetItem(QString::number(0)));

      QCheckBox*   plotCheckBox         = new QCheckBox();
      QWidget*     plotLayoutWidget     = new QWidget();
      QHBoxLayout* plotHorizontalLayout = new QHBoxLayout();
      plotHorizontalLayout->setAlignment(Qt::AlignCenter);
      plotHorizontalLayout->addWidget(plotCheckBox);
      plotLayoutWidget->setLayout(plotHorizontalLayout);
      table->setCellWidget(stream.position, TableColumn::Plot, plotLayoutWidget);
      plotCheckBox->setChecked(true);

      QRadioButton* axisRadioButton      = new QRadioButton();
      QWidget*      axisLayoutWidget     = new QWidget();
      QHBoxLayout*  axisHorizontalLayout = new QHBoxLayout();
      axisHorizontalLayout->setAlignment(Qt::AlignCenter);
      axisHorizontalLayout->addWidget(axisRadioButton);
      axisLayoutWidget->setLayout(axisHorizontalLayout);
      table->setCellWidget(stream.position, TableColumn::Axis, axisLayoutWidget);

      if (stream.dataType == DataType::Mechanical) {
        mechanicalButtons->addButton(axisRadioButton);
      }
      if (stream.dataType == DataType::Electrical) {
        electricalButtons->addButton(axisRadioButton);
      }
      connect(plotCheckBox, &QCheckBox::stateChanged, this, [&] { emit plotToggled(stream); });
      connect(axisRadioButton, &QCheckBox::pressed, this, [&] { emit axisToggled(stream); });
    } else {
      table->setItem(stream.position, 0, new QTableWidgetItem(stream.name));
    }
  }
}

void Table::update(std::vector<dataStream>& dataStreams) {
  for (auto& stream : dataStreams) {
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(stream.value)));
      if ((stream.value > stream.warningThresholds[1] || stream.value < stream.warningThresholds[0]) &&
          stream.dataType != DataType::Time) {
        table->item(stream.position, TableColumn::Value)->setBackground(Qt::yellow);
      }
      if (stream.value < table->item(stream.position, TableColumn::Min)->text().toDouble()) {
        table->setItem(stream.position, TableColumn::Min, new QTableWidgetItem(QString::number(stream.value)));
      }
      if (stream.value > table->item(stream.position, TableColumn::Max)->text().toDouble()) {
        table->setItem(stream.position, TableColumn::Max, new QTableWidgetItem(QString::number(stream.value)));
      }
    } else if (stream.dataType == DataType::CurrentEngineState) {
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(parseEngineState(stream.value)));
    } else if (stream.dataType == DataType::Time) {
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(stream.value)));
    }
  }
}
