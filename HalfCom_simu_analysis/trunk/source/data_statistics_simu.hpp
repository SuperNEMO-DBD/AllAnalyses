//! \file data_statistics.hpp
//
// Copyright (c) 2017 by Guillaume Oliviéro <goliviero@lpccaen.in2p3.fr>
//
// Class containing root histograms for
// half commissioning simulation analysis
//

#ifndef DATA_STATISTICS_SIMU_HPP
#define DATA_STATISTICS_SIMU_HPP

// Standard library:
#include <string>
#include <iostream>
#include <array>

// Root :
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"

// This project :
#include "hc_constants.hpp"

//! \brief
struct data_statistics_simu
{
  /// Default constructor
  data_statistics_simu();

  /// Destructor
  virtual ~data_statistics_simu();

  /// Reset
  virtual void reset();

	/// Initialize
	void initialize();

  // Save histograms in root file
  void save_in_root_file(TFile * root_file_);

  /// Print in a text file data statistics
  virtual void print(std::ostream & out_);

private :

  /// Effective reset method
  void _reset_();

public :

	// Management :
	bool initialized;

  // Histograms for simulation :

  // Calorimeter (only ht in simulation)
  // std::array<TH1F *, hc_constants::NUMBER_OF_CALO_PER_COLUMN> calo_energy_TH1F{};
	std::array<std::array<TH1F *, hc_constants::NUMBER_OF_CALO_PER_COLUMN>, hc_constants::NUMBER_OF_CALO_COLUMNS_USED> calo_ht_energy_TH1F{{}};
  // std::array<TH1F *, hc_constants::NUMBER_OF_CALO_PER_COLUMN> calo_no_ht_energy_TH1F{};
	//  TH2F * calo_distrib_TH2F;
  TH2F * calo_distrib_ht_TH2F;
  // TH2F * calo_distrib_no_ht_TH2F;

  // TH1F * calo_total_energy_TH1F;
  TH1F * calo_ht_total_energy_TH1F;
  // TH1F * calo_no_ht_total_energy_TH1F;

  TH1F * calo_delta_t_calo_tref_TH1F;

  // One calo (HT) :
  // TH1F * one_calo_energy_TH1F;
  // TH2F * one_calo_distribution_TH2F;


  // Tracker :
  TH2F * tracker_total_distribution_TH2F;


	// Calo tracker :

	TH2F * calo_tracker_calo_distrib_TH2F;
	TH2F * calo_tracker_calo_ht_distrib_TH2F;
	TH2F * calo_tracker_tracker_distrib_TH2F;

	TH1F * calo_tracker_delta_t_calo_tref_TH1F;
	TH1F * calo_tracker_delta_t_anode_tref_TH1F;
	TH1F * calo_tracker_delta_t_anode_anode_TH1F;
	TH1F * calo_tracker_delta_t_cathode_tref_TH1F;
	TH1F * calo_tracker_delta_t_anode_cathode_same_hit_TH1F;

};


#endif // DATA_STATISTICS_SIMU_HPP

// Local Variables: --
// Mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
