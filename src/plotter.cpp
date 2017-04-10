#include "src/plotter.h"

Plotter::Plotter(QCustomPlot* _mechanicalPlot, QCustomPlot* _electricalPlot, ConfigData _configData) {
  mechanicalPlot = _mechanicalPlot;
  electricalPlot = _electricalPlot;
  configData     = _configData;
}

void Plotter::setup(std::vector<dataStream>& dataStreams) {
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  uint8_t                           i = 0;
  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Mechanical) {
      mechanicalPlot->addGraph();
      stream.graphNum = i;
      mechanicalPlot->graph(stream.graphNum)->setName(stream.name);
      mechanicalPlot->graph(stream.graphNum)->setPen(QPen(stream.colour));
      i++;
    }
  }
  i = 0;
  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Electrical) {
      electricalPlot->addGraph();
      stream.graphNum = i;
      electricalPlot->graph(stream.graphNum)->setName(stream.name);
      electricalPlot->graph(stream.graphNum)->setPen(QPen(stream.colour));
      i++;
    }
  }
  mechanicalPlot->xAxis->setTicker(timeTicker);
  mechanicalPlot->yAxis->setRange(0, 100);
  electricalPlot->xAxis->setTicker(timeTicker);
  electricalPlot->yAxis->setRange(0, 100);

  mechanicalPlot->legend->setVisible(true);
  mechanicalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
  electricalPlot->legend->setVisible(true);
  electricalPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}

void Plotter::update(std::vector<dataStream>& dataStreams) {
  static QTime time(QTime::currentTime());
  double       key = time.elapsed() / 1000.0;

  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Mechanical) {
      mechanicalPlot->graph(stream.graphNum)->addData(key, stream.scaledValue);
    }
    if (stream.dataType == DataType::Electrical) {
      electricalPlot->graph(stream.graphNum)->addData(key, stream.scaledValue);
    }
  }

  // Shift the axis left for the new data and refresh the graph
  mechanicalPlot->xAxis->setRange(key, configData.plotWidth, Qt::AlignRight);
  mechanicalPlot->replot();
  electricalPlot->xAxis->setRange(key, configData.plotWidth, Qt::AlignRight);
  electricalPlot->replot();
}

void Plotter::onPlotToggled(dataStream stream) {
  if (stream.dataType == DataType::Electrical && electricalPlot->graph(stream.graphNum)->visible())
    electricalPlot->graph(stream.graphNum)->setVisible(false);
  else if (stream.dataType == DataType::Electrical && !electricalPlot->graph(stream.graphNum)->visible())
    electricalPlot->graph(stream.graphNum)->setVisible(true);
  else if (stream.dataType == DataType::Mechanical && mechanicalPlot->graph(stream.graphNum)->visible())
    mechanicalPlot->graph(stream.graphNum)->setVisible(false);
  else if (stream.dataType == DataType::Mechanical && !mechanicalPlot->graph(stream.graphNum)->visible())
    mechanicalPlot->graph(stream.graphNum)->setVisible(true);
}

void Plotter::onAxisToggled(dataStream stream) {
  if (stream.dataType == DataType::Electrical) {
    electricalPlot->yAxis2->setRange(stream.typicalValues[0], stream.typicalValues[1]);
    electricalPlot->yAxis2->setVisible(true);
  } else if (stream.dataType == DataType::Mechanical) {
    mechanicalPlot->yAxis2->setRange(stream.typicalValues[0], stream.typicalValues[1]);
    mechanicalPlot->yAxis2->setVisible(true);
  }
}
