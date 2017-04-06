// -*-c++-*-
#include "lib/qcustomplot/qcustomplot.h"
#include "src/config.h"
#include "src/dataStream.h"
#include <QFont>

class Plotter {
public:
  Plotter(QCustomPlot *_mechanicalPlot, QCustomPlot *_electricalPlot, ConfigData configData);
  ~Plotter();

  void setup(std::vector<dataStream> &dataStreams);
  void plot(std::vector<dataStream> &dataStreams);

public slots:
  void togglePlot();

private:
  QCustomPlot *mechanicalPlot;
  QCustomPlot *electricalPlot;
  ConfigData   configData;
};
