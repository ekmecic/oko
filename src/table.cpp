#include "src/table.h"

Table::Table(QTableWidget* _table) {
  table = _table;
}

void Table::setup(std::vector<dataStream>& dataStreams) {
  // It wouldn't make sense to be able to have multiple second yAxes, so we
  // make the mechanical and electrical axis selection buttons exclusive
  mechanicalButtons = new QButtonGroup(this);
  electricalButtons = new QButtonGroup(this);

  for (auto& stream : dataStreams) {
    // For all of the mechanical
    if (stream.dataType != DataType::CurrentEngineState && stream.dataType != DataType::Time) {
      // Set the "Name" cell to the stream name and then set all numerical cells to 0
      table->setItem(stream.position, TableColumn::Name, new QTableWidgetItem(stream.name));
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(0)));
      table->setItem(stream.position, TableColumn::Min, new QTableWidgetItem(QString::number(0)));
      table->setItem(stream.position, TableColumn::Max, new QTableWidgetItem(QString::number(0)));

      // The table looks better when the checkboxes and radio buttons are centered in their cells
      // Unfortunately, there's no easy way to center them so we use a convoluted
      // QWidget -> HBox (centered) -> Checkbox/Radio button setup which gets the job done.
      QCheckBox*   plotCheckBox         = new QCheckBox();
      QWidget*     plotLayoutWidget     = new QWidget();
      QHBoxLayout* plotHorizontalLayout = new QHBoxLayout();
      plotHorizontalLayout->setAlignment(Qt::AlignCenter);
      plotHorizontalLayout->addWidget(plotCheckBox);
      plotLayoutWidget->setLayout(plotHorizontalLayout);
      table->setCellWidget(stream.position, TableColumn::Plotted, plotLayoutWidget);
      plotCheckBox->setChecked(true);

      QRadioButton* axisRadioButton      = new QRadioButton();
      QWidget*      axisLayoutWidget     = new QWidget();
      QHBoxLayout*  axisHorizontalLayout = new QHBoxLayout();
      axisHorizontalLayout->setAlignment(Qt::AlignCenter);
      axisHorizontalLayout->addWidget(axisRadioButton);
      axisLayoutWidget->setLayout(axisHorizontalLayout);
      table->setCellWidget(stream.position, TableColumn::AxisVisible, axisLayoutWidget);

      // Assign the radio button to the correct exclusion group
      if (stream.dataType == DataType::Mechanical) {
        mechanicalButtons->addButton(axisRadioButton);
      }
      if (stream.dataType == DataType::Electrical) {
        electricalButtons->addButton(axisRadioButton);
      }
      // Connect the graph/axis toggled signals to their slots
      connect(plotCheckBox, &QCheckBox::stateChanged, this, [&] { emit graphToggled(stream); });
      connect(axisRadioButton, &QCheckBox::pressed, this, [&] { emit axisToggled(stream); });
    }
    // Just set the "Name" cell for the Time and EngineState dataStreams
    else {
      table->setItem(stream.position, TableColumn::Name, new QTableWidgetItem(stream.name));
    }
  }
}

void Table::update(std::vector<dataStream>& dataStreams) {
  for (auto& stream : dataStreams) {
    // Update the "Value" cells for Mechanical and Electrical dataStreams
    // Updates min/maxes and paints cell yellow if it exceeds warning thresholds
    if (stream.dataType == DataType::Mechanical || stream.dataType == DataType::Electrical) {
      // Set the new value
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(stream.value)));
      // If the new value exceeds either of the warning thresholds
      if ((stream.value > stream.warningThresholds[1] || stream.value < stream.warningThresholds[0]) &&
          stream.dataType != DataType::Time) {
        table->item(stream.position, TableColumn::Value)->setBackground(Qt::yellow);
      }
      // If the new value exceeds the previously set minumum
      if (stream.value < table->item(stream.position, TableColumn::Min)->text().toDouble()) {
        table->setItem(stream.position, TableColumn::Min, new QTableWidgetItem(QString::number(stream.value)));
      }
      // If the new value exceeds the previously set maximum
      if (stream.value > table->item(stream.position, TableColumn::Max)->text().toDouble()) {
        table->setItem(stream.position, TableColumn::Max, new QTableWidgetItem(QString::number(stream.value)));
      }
    }
    // Set the EngineState string for EngineState dataStreams and time for Time dataStreams.
    else if (stream.dataType == DataType::CurrentEngineState) {
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(parseEngineState(stream.value)));
    } else if (stream.dataType == DataType::Time) {
      table->setItem(stream.position, TableColumn::Value, new QTableWidgetItem(QString::number(stream.value)));
    }
  }
}
