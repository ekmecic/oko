// -*-c++-*-
#include "lib/qcustomplot/qcustomplot.h"
#include "src/dataStream.h"
#include <QFont>

class Plotter {
public:
  Plotter(QCustomPlot *_mechanicalPlot, QCustomPlot *_electricalPlot);
  ~Plotter();

  void setup(std::vector<dataStream> vec);
  void plot();

public slots:
  void togglePlot();

private:
  QCustomPlot *mechanicalPlot;
  QCustomPlot *electricalPlot;
};
