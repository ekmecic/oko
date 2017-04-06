#include "src/plotter.h"

Plotter::Plotter(QCustomPlot *_mechanicalPlot, QCustomPlot *_electricalPlot, ConfigData _configData) {
  this->mechanicalPlot = _mechanicalPlot;
  this->electricalPlot = _electricalPlot;
  this->configData     = _configData;
}

void Plotter::setup(std::vector<dataStream> &dataStreams) {
  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  uint8_t                           i = 0;
  for (auto &stream : dataStreams) {
    if (stream.dataType == DataType::Mechanical) {
      this->mechanicalPlot->addGraph();
      stream.graphNum = i;
      this->mechanicalPlot->graph(stream.graphNum)->setName(stream.name);
      this->mechanicalPlot->graph(stream.graphNum)->setPen(QPen(stream.colour));
      i++;
    }
  }
  i = 0;
  for (auto &stream : dataStreams) {
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
