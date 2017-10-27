//! \file    SensitivityModule.h
//! \brief   Example processing module for flreconstruct
//! \details Process a things object
#ifndef TESTMODULE_HH
#define TESTMODULE_HH
// Standard Library
// Third Party
//#include <boost/foreach.hpp>
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
#include "bayeux/datatools/service_manager.h"
#include "bayeux/geomtools/manager.h"
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
  bool passes_two_plus_calos_;
  bool passes_two_clusters_;
  bool passes_two_tracks_;
  bool passes_associated_calorimeters_;
  int number_of_electrons_;
  int number_of_gammas_;
  double total_calorimeter_energy_;

  double lower_electron_energy_; // MeV
  double higher_electron_energy_;// MeV
  double true_lower_electron_energy_;
  double true_higher_electron_energy_;

  std::vector<double> electron_energies_;
  std::vector<double> gamma_energies_;
  std::vector<double>* traj_cluster_delayed_time_;

  // Truth info - particle energies in MeV
  double true_highest_primary_energy_;
  double true_second_primary_energy_;
  double true_total_energy_;

  // Get vertex position of up to two tracks in mm
  double first_vertex_x_; // Foil is at x ~ 0, main calo walls are at +/- 434.994 mm according to flvisualize
  double first_vertex_y_; // y direction is horizontal, parallel to the foil, you can see it in top view
  // Foil goes from roughly y = -2500 to 2500mm (look up the actual values), the where we get x-calo blocks
  double first_vertex_z_; // z direction is vertical, parallel to the wires, you can see it in side view
  // edges of foil are about z= -1300 to 1300mm (don't have exact numbers right now)
  double second_vertex_x_;
  double second_vertex_y_;
  double second_vertex_z_;
  // And momenta at the first vertex
  double first_track_direction_x_;
  double first_track_direction_y_;
  double first_track_direction_z_;
  double second_track_direction_x_;
  double second_track_direction_y_;
  double second_track_direction_z_;
  // Use these to estimate the vertex position if the vertex were on the foil (x=0)
  // We only need y and z values for these, as x will always be 0 by definition
  double first_proj_vertex_y_;
  double first_proj_vertex_z_;
  double second_proj_vertex_y_;
  double second_proj_vertex_z_;
  // Use these to calculate the angle between tracks
  double angle_between_tracks_;
  double same_side_of_foil_;

  double vertex_separation_; // How far apart are their vertices (the ones nearest the foil)
  double foil_projection_separation_; // How far apart would the vertices be if the tracks were projected back to the foil? Sometimes a track will not be reconstructed all the way back even if it really was from the foil

  double projection_distance_xy_; // Distance between the end of the track and the foil projected vertex, in the xy plane (ie ignoring distance along wires - gives an indication of how many hits were missed). There are 2 tracks in a good event, and we want the longer of the two distances.
  int vertices_on_foil_; // How many tracks included a vertex on the foil?
  int first_vertices_on_foil_; // How many tracks had their FIRST vertex on the foil? OBSOLETE/USELESS

  // For calculating probability of an  internal/external topology
  double time_delay_;
  bool topology_2e_; // Does it have a 2-electron-like topology?
  double internal_probability_;
  double internal_chi_squared_; // No longer used, was for validation of calculation
  double external_probability_;
  double external_chi_squared_; // No longer used, was for validation of calculation

  // These might help where the clusterer cannot reconstruct tracks all the way to the foil
  double foil_projected_internal_probability_;
  double foil_projected_external_probability_;

  double topology_1e1gamma_; // Does topology look like 1 electron, 1 gamma?
  double topology_1engamma_; //  Does topology look like 1 electron, 1 or more gammas?
  double topology_1e1alpha_; //  Does topology look like 1 electron, 1 alpha?
  
  // For electrons and gammas, get the position of the earliest associated calorimeter hit
  // (for electrons we currently associate only 1 but gamma tracks can hit multiple calos
  std::vector<bool> electron_hits_mainwall_;
  std::vector<bool> electron_hits_xwall_;
  std::vector<bool> electron_hits_gveto_;
  std::vector<bool> gamma_hits_mainwall_;
  std::vector<bool> gamma_hits_xwall_;
  std::vector<bool> gamma_hits_gveto_;
  std::vector<double> gamma_fractions_mainwall_;
  std::vector<double> gamma_fractions_xwall_;
  std::vector<double> gamma_fractions_gveto_;

  // Debug information

  double calorimeter_hit_count_; // How many calorimeter hits over threshold?
  double cluster_count_; // How many clusters with 3 or more hits?
  int track_count_; // How many reconstructed tracks?
  int associated_track_count_; // How many reconstructed tracks with an associated calorimeter?
  int alpha_count_; // How many reconstructed alphas (ie delayed hits)?
  int foil_alpha_count_; //How many reconstructed alphas (ie delayed hits) that we think have a vertex on the foil?
  double latest_delayed_hit_; // Time of the latest delayed hit (if any)
  double small_cluster_count_; // How many clusters with 2 hits?
  double highest_gamma_energy_; // Highest energy gamma
  double edgemost_vertex_; // Y position of the foil vertex nearest the side of the detector

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


  // geometry service
  const geomtools::manager* geometry_manager_; //!< The geometry manager

  double ProbabilityFromChiSquared(double chiSquared);
  void CalculateProbabilities(double &internalProbability, double &externalProbability, double *calorimeterEnergies,  double *betas, double *trackLengths, double *calorimeterTimes, double *totalTimeVariances );
  // Functions used to populate the vectors of info about which calorimeter walls were hit
  int InsertAndGetPosition(double toInsert, std::vector<double> &vec, bool highestFirst);
  void PopulateWallVectors(std::vector<int> &calotypes, std::vector<bool> &mainVec, std::vector<bool> &xVec, std::vector<bool> &vetoVec);
  template <typename T>  void InsertAt(T toInsert, std::vector<T> &vec, int position);
  

  // Macro which automatically creates the interface needed
  // to enable the module to be loaded at runtime
  DPP_MODULE_REGISTRATION_INTERFACE(SensitivityModule);
};
#endif // TESTMODULE_HH
