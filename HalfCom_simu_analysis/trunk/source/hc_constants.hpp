//! \file hc_constants.hpp
//
// Copyright (c) 2017 by Guillaume Oliviéro <goliviero@lpccaen.in2p3.fr>
//
// Half Commissioning constants
// (to be include in Falaise/src at term)
//

#ifndef HC_CONSTANTS_HPP
#define HC_CONSTANTS_HPP

// Standard library:
#include <cstdint>

// Third party:
#include <bayeux/datatools/units.h>
#include <bayeux/datatools/clhep_units.h>

struct hc_constants
{
	// Calo :
  static const uint16_t NUMBER_OF_CALO_PER_COLUMN = 13;
	static const uint16_t NUMBER_OF_CALO_COLUMNS    = 20;
	static const uint16_t NUMBER_OF_CALO_COLUMNS_USED = 3;

	// Geiger :
	static const uint16_t NUMBER_OF_GEIGER_LAYERS = 9;
	static const uint16_t NUMBER_OF_GEIGER_ROWS   = 113;

	// Electronics :
	static const std::size_t CALO_COMMISSIONING_HIGH_THRESHOLD_KEV = 15;

};

#endif // HC_CONSTANTS_HPP

// Local Variables: --
// Mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
