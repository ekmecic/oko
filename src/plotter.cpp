#include "src/plotter.h"

Plotter::Plotter(QCustomPlot* _mechanicalPlot, QCustomPlot* _electricalPlot, ConfigData _configData) {
  this->mechanicalPlot = _mechanicalPlot;
  this->electricalPlot = _electricalPlot;
  this->configData     = _configData;
}

void Plotter::setup(std::vector<dataStream>& dataStreams) {
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  uint8_t                           i = 0;
  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Mechanical) {
      this->mechanicalPlot->addGraph();
      stream.graphNum = i;
      this->mechanicalPlot->graph(stream.graphNum)->setName(stream.name);
      this->mechanicalPlot->graph(stream.graphNum)->setPen(QPen(stream.colour));
      i++;
    }
  }
  i = 0;
  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Electrical) {
      this->electricalPlot->addGraph();
      stream.graphNum = i;
      this->electricalPlot->graph(stream.graphNum)->setName(stream.name);
      this->electricalPlot->graph(stream.graphNum)->setPen(QPen(stream.colour));
      i++;
    }
  }
  this->mechanicalPlot->xAxis->setTicker(timeTicker);
  this->mechanicalPlot->yAxis->setRange(0, 100);
  this->electricalPlot->xAxis->setTicker(timeTicker);
  this->electricalPlot->yAxis->setRange(0, 100);

  this->mechanicalPlot->legend->setVisible(true);
  this->mechanicalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
  this->electricalPlot->legend->setVisible(true);
  this->electricalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}

void Plotter::update(std::vector<dataStream>& dataStreams) {
  static QTime time(QTime::currentTime());
  double       key = time.elapsed() / 1000.0;

  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Mechanical) {
      this->mechanicalPlot->graph(stream.graphNum)->addData(key, stream.scaledValue);
    }
    if (stream.dataType == DataType::Electrical) {
      this->electricalPlot->graph(stream.graphNum)->addData(key, stream.scaledValue);
    }
  }

  // Shift the axis left for the new data and refresh the graph
  this->mechanicalPlot->xAxis->setRange(key, configData.plotWidth, Qt::AlignRight);
  this->mechanicalPlot->replot();
  this->electricalPlot->xAxis->setRange(key, configData.plotWidth, Qt::AlignRight);
  this->electricalPlot->replot();
}

void Plotter::onPlotToggled(dataStream stream) {
  if (stream.dataType == DataType::Electrical && this->electricalPlot->graph(stream.graphNum)->visible())
    this->electricalPlot->graph(stream.graphNum)->setVisible(false);
  else if (stream.dataType == DataType::Electrical && !this->electricalPlot->graph(stream.graphNum)->visible())
    this->electricalPlot->graph(stream.graphNum)->setVisible(true);
  else if (stream.dataType == DataType::Mechanical && this->mechanicalPlot->graph(stream.graphNum)->visible())
    this->mechanicalPlot->graph(stream.graphNum)->setVisible(false);
  else if (stream.dataType == DataType::Mechanical && !this->mechanicalPlot->graph(stream.graphNum)->visible())
    this->mechanicalPlot->graph(stream.graphNum)->setVisible(true);
}

void Plotter::onAxisToggled(dataStream stream) {
  if (stream.dataType == DataType::Electrical) {
    this->electricalPlot->yAxis2->setRange(stream.typicalValues[0], stream.typicalValues[1]);
    this->electricalPlot->yAxis2->setVisible(true);
  } else if (stream.dataType == DataType::Mechanical) {
    this->mechanicalPlot->yAxis2->setRange(stream.typicalValues[0], stream.typicalValues[1]);
    this->mechanicalPlot->yAxis2->setVisible(true);
  }
}
