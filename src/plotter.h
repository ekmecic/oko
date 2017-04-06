// -*-c++-*-
#pragma once
#include "lib/qcustomplot/qcustomplot.h"
#include "src/config.h"
#include "src/dataStream.h"
#include <QFont>

class Plotter {
public:
  Plotter(QCustomPlot* _mechanicalPlot, QCustomPlot* _electricalPlot, ConfigData configData);
  ~Plotter();

  void setup(std::vector<dataStream>& dataStreams);
  void update(std::vector<dataStream>& dataStreams);

private:
  QCustomPlot* mechanicalPlot;
  QCustomPlot* electricalPlot;
  ConfigData   configData;
};
