// -*-c++-*-
/** @file */
#pragma once

#include <QString>

/** @brief Parses engine state into an useful state that can be displayed in the Table.
    @param value The state in which the engine is currently in, as an integer.
    @return A string containing the state the engine is currently in.

    The return values are deliberately short to take up as little space as possible in the table. */
QString parseEngineState(const double value);
