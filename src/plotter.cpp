#include "src/plotter.h"

Plotter::Plotter(QCustomPlot* _mechanicalPlot, QCustomPlot* _electricalPlot, const ConfigData _configData) {
  mechanicalPlot = _mechanicalPlot;
  electricalPlot = _electricalPlot;
  configData     = _configData;
}

void Plotter::setup(std::vector<dataStream>& dataStreams) {
  uint8_t i = 0;
  // Assign all of the mechanical datastreams to the mechanical plot,
  // set their name and colour, and remember their graph number
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
  // Do the same, but for the electrical streams
  for (auto& stream : dataStreams) {
    if (stream.dataType == DataType::Electrical) {
      electricalPlot->addGraph();
      stream.graphNum = i;
      electricalPlot->graph(stream.graphNum)->setName(stream.name);
      electricalPlot->graph(stream.graphNum)->setPen(QPen(stream.colour));
      i++;
    }
  }
  // Set the xAxis to time and the yAxis to 0-100
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  mechanicalPlot->xAxis->setTicker(timeTicker);
  mechanicalPlot->yAxis->setRange(0, 100);
  electricalPlot->xAxis->setTicker(timeTicker);
  electricalPlot->yAxis->setRange(0, 100);

  // Enable the legends and put them at the top left
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

void Plotter::onGraphToggled(const dataStream stream) {
  // The logic here is overcomplicated for what it's actually doing
  // which is only checking what type a stream is and if it's visible or not
  if (stream.dataType == DataType::Electrical && electricalPlot->graph(stream.graphNum)->visible())
    electricalPlot->graph(stream.graphNum)->setVisible(false);
  else if (stream.dataType == DataType::Electrical && !electricalPlot->graph(stream.graphNum)->visible())
    electricalPlot->graph(stream.graphNum)->setVisible(true);
  else if (stream.dataType == DataType::Mechanical && mechanicalPlot->graph(stream.graphNum)->visible())
    mechanicalPlot->graph(stream.graphNum)->setVisible(false);
  else if (stream.dataType == DataType::Mechanical && !mechanicalPlot->graph(stream.graphNum)->visible())
    mechanicalPlot->graph(stream.graphNum)->setVisible(true);
}

void Plotter::onAxisToggled(const dataStream stream) {
  if (stream.dataType == DataType::Electrical) {
    electricalPlot->yAxis2->setRange(stream.typicalValues[0], stream.typicalValues[1]);
    electricalPlot->yAxis2->setVisible(true);
  } else if (stream.dataType == DataType::Mechanical) {
    mechanicalPlot->yAxis2->setRange(stream.typicalValues[0], stream.typicalValues[1]);
    mechanicalPlot->yAxis2->setVisible(true);
  }
}
