// -*-c++-*-
#pragma once

#include "src/config.h"
#include "src/dataStream.h"
#include "src/engineState.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QObject>
#include <QRadioButton>
#include <QTableWidget>
#include <QTableWidgetItem>

/** @brief Convenience enum that names table columns

    This stops us from referring to columns in the UI with magic numbers,
    and instead lets us refer to them by their column labels. */
typedef enum {
  Field,
  Value,
  Min,
  Max,
  Plot,
  Axis,
} TableColumn;

/** @brief Initializes the Table in the UI and updates it with new values.
    @author Emil Ekmečić
    @date April 2017 */
class Table : public QObject {
  Q_OBJECT

public:
  /** @brief Constructs a new Table.
      @param _table The table that displays all of the dataStreams. */
  Table(QTableWidget* _table);

  /** @brief Initializes the Table with the dataStreams
      @param dataStreams All of the dataStreams.

      Sets the "Field" column of all dataStreams, initializes all of the numerical columns to 0 for Mechanical and
      Electrical dataStreams, and sets up the checkboxes/radio buttons for graph/axis toggling. */
  void setup(std::vector<dataStream>& dataStreams);

  /** @brief Updates the Table with new values from the dataStreams
      @param dataStreams All of the dataStreams.

      Updates the "Value" column for all dataStreams.
      For Mechanical and Electrical dataStreams: paints cells that exceed warning thresholds yellow; updates the
      minimums and maximums of the dataStreams that exceed them.

      For EngineState and Time dataStreams it simply updates the value. */
  void update(std::vector<dataStream>& dataStreams);

signals:
  /** @brief Emitted when the "Plot" checkbox is toggled
      @param stream The dataStream that was toggled

      Connects to the onGraphToggled slot which toggles the visibility of the toggled dataStream. */
  void graphToggled(const dataStream stream);

  /** @brief Emitted when the "Axis" radio button is toggled
      @param stream The dataStream that was toggled

      Connects to the onGraphToggled slot which toggles the visibility of the toggled dataStream's "real" axis. */
  void axisToggled(const dataStream stream);

private:
  /** @brief The table from the oko object */
  QTableWidget* table;

  /** @brief Button group that keeps the Mechanical axis-toggling radio buttons exclusive from each other. */
  QButtonGroup* mechanicalButtons;

  /** @brief Button group that keeps the Electrical axis-toggling radio buttons exclusive from each other. */
  QButtonGroup* electricalButtons;
};
