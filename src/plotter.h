// -*-c++-*-
#pragma once

#include "qcustomplot.h"
#include "src/config.h"
#include "src/dataStream.h"

#include <QFont>

/** @brief Initializes and updates the plots in the UI.
    @author Emil Ekmečić
    @date April 2017 */
class Plotter : public QObject {
  Q_OBJECT

public:
  /** @brief Constructs a new Plotter.
      @param _mechanicalPlot The plot that holds all of the mechanical data
      @param _electricalPlot The plot that holds all of the electrical data
      @param _configData Configuration data pulled from config.toml. We only really need it for the plotWidth. */
  Plotter(QCustomPlot* _mechanicalPlot, QCustomPlot* _electricalPlot, const ConfigData _configData);

  /** @brief Assigns dataStreams to the correct plots; sets colors, names, legends, and axes.
      @param dataStreams All of the dataStreams

      setup places the mechanical and electrical plots on the correct plot and gives them their colors and names.
      This leaves the Time and EngineState dataStreams off, which we don't want on the plot anyways.
      It also sets up the axes and legends. */
  void setup(std::vector<dataStream>& dataStreams);

  /** @brief Updates both plots with new values from the dataStreams.
      @param dataStreams All of the dataStreams */
  void update(std::vector<dataStream>& dataStreams);

public slots:
  /** @brief Shows or hides a graph when it's checkbox is toggled in the Table.
      @param stream The dataStream whose checkbox was toggled.

      Checks if the stream is visible and toggles it's state depending on it's state. */
  void onGraphToggled(const dataStream stream);

  /** @brief Toggles a second yAxis with the "true" range of the selected dataStream.
      @param stream The dataStream whose radio button was hit.

      The only axis visible on the plots is a 0-100 percentage axis.
      Each dataStream has a radio button in the Table whose function is to enable a second yAxis.
      This second yAxis goes from typMin-typMax instead of 0-100.
      The make it easier to discern the actual value of a dataStream. */
  void onAxisToggled(const dataStream stream);

private:
  /** The designated plot that holds mechanical dataStreams. */
  QCustomPlot* mechanicalPlot;

  /** The designated plot that holds electrical dataStreams. */
  QCustomPlot* electricalPlot;

  /** @param configData Configuration data pulled from config.toml. We only really need it for the plotWidth. */
  ConfigData configData;
};
