// -*-c++-*-
#pragma once

#include <QColor>
#include <string>
#include <vector>

/**
   @brief Describes the type of each dataStream

   Most datastreams will be either Mechanical or Electrical, but there are two edge cases.
   The "time since start" and EngineState have their own types because it wouldn't make sense make them Mech/Elec.
   This setup makes it easier to categorize each dataStream in the main UI.
   For example, deciding which dataStream is plotted and on which plot etc.
*/
typedef enum {
  Time,
  Mechanical,
  Electrical,
  CurrentEngineState,
} DataType;

/** @brief A container for each piece of data from the Bluetooth module.
    @author Emil Ekmečić
    @date April 2017

    This class is the foundation of most of oko.
    All data coming off the Bluetooth module is structured into dataStreams, which make the data easier to process in the GUI.
    This makes it easier to work with by putting all the information for each piece of data into one location.

    At GUI initialization a dataStreams are created according to user-specified config.toml.
    Each piece of data gets its own dataStream.
    These dataStreams are then collated together in a vector and passed around to the Plotter, Table, Logger as needed.
*/
class dataStream {
public:
  /** @brief Constructs a dataStream. */
  dataStream(QString             _name,
             double              _multiplier,
             std::vector<double> _warningThresholds,
             std::vector<double> _typicalValues,
             double              _position,
             DataType            _dataType,
             Qt::GlobalColor     _colour)
    // clang-format off
    : name(_name),
      multiplier(_multiplier),
      warningThresholds(_warningThresholds),
      typicalValues(_typicalValues),
      position(_position),
      dataType(_dataType),
      colour(_colour) {}
  // clang-format on

  /** @brief Name of the dataStream which is displayed in the Table and Plotter legend. For example: "Battery Voltage"
   */
  QString name;

  /** @brief The raw value from the Bluetooth module. For Engine RPM this could be anywhere from 0-7000RPM. */
  double value;

  /** @brief The raw value from the Bluetooth module scaled from 0-100 according to the "typicalValues" configuration option.

      When engine RPM is 6600RPM, this might be 90% although it depends on the typicalValues chosen by the user. */
  double scaledValue;

  /** @brief Each value from the Bluetooth module will be multiplied by this number.

      Some values might come in in weird units i.e. RPM could be in kRPM instead of RPM.
      To account for this, we provide an option to multiply each value so it's in a sensible value.
      For the engine RPM, an appropriate multiplier would be 1000.*/
  double multiplier;

  /** @brief If a value is above or below this threshold, the Table cell for the value will be colored yellow.

      Use these values to draw attention to a value and indicate to the user that an operating parameter is outside of
      normal operating ranges.
      As an example, values for bus voltage might be something like [22, 26].

      This vector should always have size = 2, although we currently don't check (TODO).
      The first value is assumed to be the minium and the second the maximum.
      dataStreams that aren't Mechanical or Electrical should have both values set to 0 per convention. */
  std::vector<double> warningThresholds;

  /** @brief Used to map values to 0-100 for plotting.

      Data from the Bluetooth module varies widely in scale (i.e. 0-30V for voltages compared to 0-7000RPM for the engine).
      Plotting varying data on the same plot is hard so instead we map each value from it's typical range to 0-100.
      In effect, you're plotting data as a percentage instead of absolutely.

      typicalValues is what dictates the mapping from raw value to a scaledValue, which is done according to:

      scaledValue = (value - typMin) * 100 / (typMax - typMin)

      where typMin and typMax are the 0th and 1st value of typicalValues, respectively.
      This vector should always have size = 2, although we currently don't check (TODO).
      The first value is assumed to be the minimum and the second the maximum.
      dataStreams that aren't Mechanical or Electrical should have both values set to 0 per convention. */
  std::vector<double> typicalValues;

  /** @brief Position of the value in the ASCII line coming from the Bluetooth module. */
  uint8_t position;

  /** @brief The type of the dataStream. */
  DataType dataType;

  /** @brief The line colour of plotted dataStream. */
  Qt::GlobalColor colour;

  /** @brief Internally used to keep track of which graph on the plot each dataStream is assigned to. */
  uint8_t graphNum;
};
