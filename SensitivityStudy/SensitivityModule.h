//! \file    SensitivityModule.h
//! \brief   Example processing module for flreconstruct
//! \details Process a things object
#ifndef TESTMODULE_HH
#define TESTMODULE_HH
// Standard Library
// Third Party
#include <boost/foreach.hpp>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TF1.h"
#include "TVector3.h"

// - Bayeux
#include "bayeux/dpp/base_module.h"
#include "bayeux/mctools/simulated_data.h"
#include "bayeux/genbb_help/primary_particle.h"
#include "bayeux/genbb_help/primary_event.h"
#include "bayeux/geomtools/geometry_service.h"
#include "bayeux/geomtools/line_3d.h"
#include "bayeux/geomtools/helix_3d.h"

// - Falaise
#include "falaise/snemo/datamodels/calibrated_data.h"
#include "falaise/snemo/datamodels/tracker_clustering_data.h"
#include "falaise/snemo/datamodels/tracker_clustering_solution.h"
#include "falaise/snemo/datamodels/particle_track_data.h"

typedef struct SensitivityEventStorage{
  bool passes_two_calorimeters_;
  bool passes_two_clusters_;
  bool passes_two_tracks_;
  bool passes_associated_calorimeters_;
  int number_of_electrons_;
  double total_calorimeter_energy_;

  double lower_electron_energy_; // MeV
  double higher_electron_energy_;// MeV
  double true_lower_electron_energy_;
  double true_higher_electron_energy_;
  // Truth info - particle energies in MeV
  double true_highest_primary_energy_;
  double true_second_primary_energy_;
  double true_total_energy_;
  
  // Get vertex position of up to two tracks in mm
  double first_vertex_x_; // Foil is at x ~ 0
  double first_vertex_y_;
  double first_vertex_z_;
  double second_vertex_x_;
  double second_vertex_y_;
  double second_vertex_z_;
  // And momenta at the first vertex
  double first_track_momentum_x_;
  double first_track_momentum_y_;
  double first_track_momentum_z_;
  double second_track_momentum_x_;
  double second_track_momentum_y_;
  double second_track_momentum_z_;
  // Use these to estimate the vertex position if the vertex were on the foil (x=0)
  // We only need y and z values for these, as x will always be 0 by definition
  double first_projected_vertex_y_;
  double first_projected_vertex_z_;
  double second_projected_vertex_y_;
  double second_projected_vertex_z_;
  // Use these to calculate the angle between tracks
  double angle_between_tracks_;
  double same_side_of_foil_;
  
  double vertex_separation_; // How far apart are their vertices (the ones nearest the foil)
  double foil_projection_separation_; // How far apart would the vertices be if the tracks were projected back to the foil? Sometimes a track will not be reconstructed all the way back even if it really was from the foil
  int vertices_on_foil_; // How many tracks included a vertex on the foil?
  int first_vertices_on_foil_; // How many tracks had their FIRST vertex on the foil?
  
  double time_delay_;
  double internal_probability_;
  double internal_chi_squared_;
  double external_probability_;
  double external_chi_squared_;

}sensitivityeventstorage;

typedef struct TruthEventStorage{ 
  double lower_electron_energy_;
  double higher_electron_energy_;
}trutheventstorage;
// This Project
class SensitivityModule : public dpp::base_module {
  static const uint minHitsInCluster=3;
 public:
  //! Construct module
  SensitivityModule();
  //! Destructor
  virtual ~SensitivityModule();
  //! Configure the module
  virtual void initialize(const datatools::properties& myConfig,
                          datatools::service_manager& flServices,
                          dpp::module_handle_dict_type& moduleDict);
  //! Process supplied data record
  virtual dpp::base_module::process_status process(datatools::things& workItem);
  //! Reset the module
  virtual void reset();
 private:
  TFile* hfile_;
  TTree* tree_;
  SensitivityEventStorage sensitivity_;
  TTree* truthtree_;
  TruthEventStorage truth_;
  
  double ProbabilityFromChiSquared(double chiSquared);
  
  // Macro which automatically creates the interface needed
  // to enable the module to be loaded at runtime
  DPP_MODULE_REGISTRATION_INTERFACE(SensitivityModule);
};
#endif // TESTMODULE_HH
