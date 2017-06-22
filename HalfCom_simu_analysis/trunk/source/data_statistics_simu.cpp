//! \file data_statistics_simu.cpp
//
// Copyright (c) 2017 by Guillaume Oliviéro <goliviero@lpccaen.in2p3.fr>
//


// Standard library:
#include <limits>

// Ourselves:
#include <data_statistics_simu.hpp>

data_statistics_simu::data_statistics_simu()
{
  reset();
}

data_statistics_simu::~data_statistics_simu()
{
}

void data_statistics_simu::reset()
{
  _reset_();
  return;
}

void data_statistics_simu::_reset_()
{
  // Histogram ptr :
  for (unsigned int icol = 0; icol < hc_constants::NUMBER_OF_CALO_COLUMNS_USED; icol++) {
    for (unsigned int irow = 0; irow < hc_constants::NUMBER_OF_CALO_PER_COLUMN; irow++) {
      // calo_energy_TH1F[icalo] = nullptr;
      calo_ht_energy_TH1F[icol][irow] = nullptr;
      // calo_no_ht_energy_TH1F[icalo] = nullptr;
    }
  }

  // calo_distrib_TH2F = nullptr;
  calo_distrib_ht_TH2F = nullptr;
  // calo_distrib_no_ht_TH2F = nullptr;

  // calo_total_energy_TH1F = nullptr;
  calo_ht_total_energy_TH1F = nullptr;;
  // calo_no_ht_total_energy_TH1F = nullptr;;

  calo_delta_t_calo_tref_TH1F = nullptr;

  // one_calo_energy_TH1F = nullptr;
  // one_calo_distribution_TH2F = nullptr;

  tracker_total_distribution_TH2F = nullptr;

  calo_tracker_calo_distrib_TH2F = nullptr;
  calo_tracker_calo_ht_distrib_TH2F = nullptr;
  calo_tracker_tracker_distrib_TH2F = nullptr;

  calo_tracker_delta_t_calo_tref_TH1F = nullptr;
  calo_tracker_delta_t_anode_tref_TH1F = nullptr;
  calo_tracker_delta_t_anode_anode_TH1F = nullptr;
  calo_tracker_delta_t_cathode_tref_TH1F = nullptr;
  calo_tracker_delta_t_anode_cathode_same_hit_TH1F = nullptr;

  initialized = false;

  return;
}

void data_statistics_simu::initialize()
{

  // Initialize all histograms :
  std::string string_buffer = "";
  for (unsigned int icol = 0; icol < hc_constants::NUMBER_OF_CALO_COLUMNS_USED; icol++) {

    for (unsigned int irow = 0; irow < hc_constants::NUMBER_OF_CALO_PER_COLUMN; irow++) {
      // string_buffer = "calo_energy_" + std::to_string(icalo);
      // calo_energy_TH1F[icalo] = new TH1F(string_buffer.c_str(),
      // 				       Form("Calorimeter energy, row %i", icalo),
      // 				       1000, 0, 3000);

      string_buffer = "calo_ht_energy_col" + std::to_string(icol) + "_row" + std::to_string(irow);
      calo_ht_energy_TH1F[icol][irow] = new TH1F(string_buffer.c_str(),
						 Form("Calorimeter HT energy, column %i, row %i", icol, irow),
						 1000, 0, 3000);

      // string_buffer = "calo_no_ht_energy_" + std::to_string(icalo);
      // calo_no_ht_energy_TH1F[icalo] = new TH1F(string_buffer.c_str(),
      // 				       Form("Calorimeter no HT energy, row %i", icalo),
      // 				       1000, 0, 3000);
    } // end of irow
  } // end of for icol

  // string_buffer = "calo_distrib_TH2F";
  // calo_distrib_TH2F =  new TH2F(string_buffer.c_str(),
  // 				Form("All calo distribution"),
  // 				20, 0, 20,
  // 				14, 0, 14);

  string_buffer = "calo_distrib_ht_TH2F";
  calo_distrib_ht_TH2F =  new TH2F(string_buffer.c_str(),
				   Form("Calo HT distribution"),
				   20, 0, 20,
				   14, 0, 14);

  // string_buffer = "calo_distrib_no_ht_TH2F";
  // calo_distrib_no_ht_TH2F =  new TH2F(string_buffer.c_str(),
  // 				      Form("Calo no HT distribution"),
  // 				      20, 0, 20,
  // 				      14, 0, 14);

  // string_buffer = "calo_total_energy_TH1F";
  // calo_total_energy_TH1F = new TH1F(string_buffer.c_str(),
  // 				    Form("Calorimeter total energy"),
  // 				    1000, 0, 3000);


  string_buffer = "calo_ht_total_energy_TH1F";
  calo_ht_total_energy_TH1F = new TH1F(string_buffer.c_str(),
				       Form("Calorimeter HT total energy"),
				       1000, 0, 3000);

  // string_buffer = "calo_no_ht_total_energy_TH1F";
  // calo_no_ht_total_energy_TH1F = new TH1F(string_buffer.c_str(),
  // 					  Form("Calorimeter no HT total energy"),
  // 					  1000, 0, 3000);

  string_buffer = "calo_delta_t_calo_tref_TH1F";
  calo_delta_t_calo_tref_TH1F = new TH1F(string_buffer.c_str(),
					 Form("Calo events 2+ calo HT, DT(calo_X - calo_tref)"),
					 100, 0, 100);

  string_buffer = "tracker_total_distribution_TH2F";
  tracker_total_distribution_TH2F = new TH2F(string_buffer.c_str(),
					     Form("Tracker cell total distribution"),
					     6, 0, 6,
					     10, 0, 10);

  string_buffer = "calo_tracker_calo_distrib_TH2F";
  calo_tracker_calo_distrib_TH2F  = new TH2F(string_buffer.c_str(),
					     Form("Calo distribution if calo + tracker events"),
					     20, 0, 20,
					     14, 0, 14);

  string_buffer = "calo_tracker_calo_ht_distrib_TH2F";
  calo_tracker_calo_ht_distrib_TH2F  = new TH2F(string_buffer.c_str(),
						Form("Calo distribution if calo HT + tracker events"),
						20, 0, 20,
						14, 0, 14);

  string_buffer = "calo_tracker_tracker_distrib_TH2F";
  calo_tracker_tracker_distrib_TH2F  = new TH2F(string_buffer.c_str(),
						Form("Tracker cell distribution if calo + tracker events"),
						6, 0, 6,
						10, 0, 10);

  string_buffer = "calo_tracker_delta_t_calo_tref_TH1F";
  calo_tracker_delta_t_calo_tref_TH1F = new TH1F(string_buffer.c_str(),
						 Form("Calo + tracker events, DT(calo_X - calo_tref)"),
						 1000, 0, 1000);

  string_buffer = "calo_tracker_delta_t_anode_tref_TH1F";
  calo_tracker_delta_t_anode_tref_TH1F = new TH1F(string_buffer.c_str(),
						  Form("Calo + tracker events, DT(anode_X - calo_tref)"),
						  1000, 0, 200000);

  string_buffer = "calo_tracker_delta_t_anode_anode_TH1F";
  calo_tracker_delta_t_anode_anode_TH1F = new TH1F(string_buffer.c_str(),
						   Form("Calo + tracker events, DT(anode_X - anode_Y)"),
						   1000, 0, 200000);

  string_buffer = "calo_tracker_delta_t_cathode_tref_TH1F";
  calo_tracker_delta_t_cathode_tref_TH1F = new TH1F(string_buffer.c_str(),
						    Form("Calo + tracker events, DT(cathode_X - calo_tref)"),
						    1000, 0, 200000);

  string_buffer = "calo_tracker_delta_t_anode_cathode_same_hit_TH1F";
  calo_tracker_delta_t_anode_cathode_same_hit_TH1F = new TH1F(string_buffer.c_str(),
							      Form("Calo + tracker events, DT(anode_X - cathode_X)"),
							      1000, 0, 10000);


  initialized = true;
  return;
}

void data_statistics_simu::save_in_root_file(TFile * root_file_)
{
  root_file_->cd("single_calo_energy");

  for (unsigned int icol = 0; icol < hc_constants::NUMBER_OF_CALO_COLUMNS_USED; icol++) {
    for (unsigned int irow = 0; irow < hc_constants::NUMBER_OF_CALO_PER_COLUMN; irow++) {
      calo_ht_energy_TH1F[icol][irow]->Write("", TObject::kOverwrite);
    }
  }

  root_file_->cd();

  calo_distrib_ht_TH2F->Write("", TObject::kOverwrite);
  calo_ht_total_energy_TH1F->Write("", TObject::kOverwrite);;
  calo_delta_t_calo_tref_TH1F->Write("", TObject::kOverwrite);

  // Segfault because histograms are not initialized
  // one_calo_energy_TH1F->Write("", TObject::kOverwrite);
  // one_calo_distribution_TH2F->Write("", TObject::kOverwrite);


  tracker_total_distribution_TH2F->Write("", TObject::kOverwrite);

  calo_tracker_calo_distrib_TH2F->Write("", TObject::kOverwrite);
  calo_tracker_calo_ht_distrib_TH2F->Write("", TObject::kOverwrite);
  calo_tracker_tracker_distrib_TH2F->Write("", TObject::kOverwrite);
  calo_tracker_delta_t_calo_tref_TH1F->Write("", TObject::kOverwrite);
  calo_tracker_delta_t_anode_tref_TH1F->Write("", TObject::kOverwrite);
  calo_tracker_delta_t_anode_anode_TH1F->Write("", TObject::kOverwrite);
  calo_tracker_delta_t_cathode_tref_TH1F->Write("", TObject::kOverwrite);
  calo_tracker_delta_t_anode_cathode_same_hit_TH1F->Write("", TObject::kOverwrite);

  return;
}

void data_statistics_simu::print(std::ostream & out_)
{
  out_ << std::endl;

  return;
}
