#include "SensitivityModule.h"
const double highEnergyLimit=0.150;// 150 keV
const double lowEnergyLimit=0.050; // 50 keV
const double electronMass=0.5109989461; // From pdg
const double speedOfLight=299792458 * 1e-9 * 1000; // Millimeters per nanosecond
using namespace std;
DPP_MODULE_REGISTRATION_IMPLEMENT(SensitivityModule,"SensitivityModule");
SensitivityModule::SensitivityModule() : dpp::base_module()
{}
SensitivityModule::~SensitivityModule() {
  if (is_initialized()) this->reset();
}
void SensitivityModule::initialize(const datatools::properties& myConfig,
                                   datatools::service_manager& flServices,
                                   dpp::module_handle_dict_type& /*moduleDict*/){

  // Look for services
  if (flServices.has("geometry")) {
    const geomtools::geometry_service& GS = flServices.get<geomtools::geometry_service> ("geometry");

    // initialize geometry manager
    //    std::cout << "Initialize geo manager " << std::endl;
    geometry_manager_ = &GS.get_geom_manager();
    DT_THROW_IF(!geometry_manager_,
                std::runtime_error,
                "Null pointer to geometry manager return by geometry_service");
  }

 // Use the method of PTD2ROOT to create a root file with just the branches we need for the sensitivity analysis

  hfile_ = new TFile("sensitivity.root","RECREATE","Output file of Simulation data");
  hfile_->cd();
  tree_ = new TTree("Sensitivity","Sensitivity");
  tree_->SetDirectory(hfile_);
  tree_->Branch("sensitivity.total_calorimeter_energy",&sensitivity_.total_calorimeter_energy_);
  tree_->Branch("sensitivity.passes_two_calorimeters",&sensitivity_.passes_two_calorimeters_);
  tree_->Branch("sensitivity.passes_two_plus_calos",&sensitivity_.passes_two_plus_calos_);
  tree_->Branch("sensitivity.passes_two_clusters",&sensitivity_.passes_two_clusters_);
  tree_->Branch("sensitivity.passes_two_tracks",&sensitivity_.passes_two_tracks_);
  tree_->Branch("sensitivity.passes_associated_calorimeters",&sensitivity_.passes_associated_calorimeters_);
  tree_->Branch("sensitivity.number_of_electrons",&sensitivity_.number_of_electrons_);
  tree_->Branch("sensitivity.number_of_gammas",&sensitivity_.number_of_gammas_);
  tree_->Branch("sensitivity.higher_electron_energy",&sensitivity_.higher_electron_energy_);
  tree_->Branch("sensitivity.lower_electron_energy",&sensitivity_.lower_electron_energy_);
  tree_->Branch("sensitivity.electron_energies",&sensitivity_.electron_energies_);
  tree_->Branch("sensitivity.gamma_energies",&sensitivity_.gamma_energies_);

  tree_->Branch("sensitivity.true_higher_electron_energy",&sensitivity_.true_higher_electron_energy_);
  tree_->Branch("sensitivity.true_lower_electron_energy",&sensitivity_.true_lower_electron_energy_);
  tree_->Branch("sensitivity.true_highest_primary_energy",&sensitivity_.true_highest_primary_energy_);
  tree_->Branch("sensitivity.true_second_primary_energy",&sensitivity_.true_second_primary_energy_);
  tree_->Branch("sensitivity.true_total_energy",&sensitivity_.true_total_energy_);

  tree_->Branch("sensitivity.first_vertex_x",&sensitivity_.first_vertex_x_);
  tree_->Branch("sensitivity.first_vertex_y",&sensitivity_.first_vertex_y_);
  tree_->Branch("sensitivity.first_vertex_z",&sensitivity_.first_vertex_z_);
  tree_->Branch("sensitivity.second_vertex_x",&sensitivity_.second_vertex_x_);
  tree_->Branch("sensitivity.second_vertex_y",&sensitivity_.second_vertex_y_);
  tree_->Branch("sensitivity.second_vertex_z",&sensitivity_.second_vertex_z_);
  tree_->Branch("sensitivity.first_proj_vertex_y",&sensitivity_.first_proj_vertex_y_);
  tree_->Branch("sensitivity.first_proj_vertex_z",&sensitivity_.first_proj_vertex_z_);  tree_->Branch("sensitivity.second_proj_vertex_y",&sensitivity_.second_proj_vertex_y_);
  tree_->Branch("sensitivity.second_proj_vertex_z",&sensitivity_.second_proj_vertex_z_);
  tree_->Branch("sensitivity.vertex_separation",&sensitivity_.vertex_separation_);
  tree_->Branch("sensitivity.foil_projection_separation",&sensitivity_.foil_projection_separation_);
  tree_->Branch("sensitivity.projection_distance_xy",&sensitivity_.projection_distance_xy_);


  tree_->Branch("sensitivity.vertices_on_foil",&sensitivity_.vertices_on_foil_);
  tree_->Branch("sensitivity.first_vertices_on_foil",&sensitivity_.first_vertices_on_foil_); // Obsolete, kept for legacy in case it is used anywhere
  tree_->Branch("sensitivity.angle_between_tracks",&sensitivity_.angle_between_tracks_);
  tree_->Branch("sensitivity.same_side_of_foil",&sensitivity_.same_side_of_foil_);
  tree_->Branch("sensitivity.first_track_direction_x",&sensitivity_.first_track_direction_x_);
  tree_->Branch("sensitivity.first_track_direction_y",&sensitivity_.first_track_direction_y_);
  tree_->Branch("sensitivity.first_track_direction_z",&sensitivity_.first_track_direction_z_);
  tree_->Branch("sensitivity.second_track_direction_x",&sensitivity_.second_track_direction_x_);
  tree_->Branch("sensitivity.second_track_direction_y",&sensitivity_.second_track_direction_y_);
  tree_->Branch("sensitivity.second_track_direction_z",&sensitivity_.second_track_direction_z_);

  tree_->Branch("sensitivity.time_delay",&sensitivity_.time_delay_);
  tree_->Branch("sensitivity.traj_cl_del_time",&sensitivity_.traj_cluster_delayed_time_);
  tree_->Branch("sensitivity.topology_2e",&sensitivity_.topology_2e_);
  tree_->Branch("sensitivity.internal_probability",&sensitivity_.internal_probability_);
  tree_->Branch("sensitivity.internal_chi_squared",&sensitivity_.internal_chi_squared_);
  tree_->Branch("sensitivity.external_probability",&sensitivity_.external_probability_);
  tree_->Branch("sensitivity.external_chi_squared",&sensitivity_.external_chi_squared_);
  tree_->Branch("sensitivity.foil_projected_internal_probability",&sensitivity_.foil_projected_internal_probability_);
  tree_->Branch("sensitivity.foil_projected_external_probability",&sensitivity_.foil_projected_external_probability_);
  tree_->Branch("sensitivity.topology_1e1gamma",&sensitivity_.topology_1e1gamma_);
  tree_->Branch("sensitivity.topology_1e1alpha",&sensitivity_.topology_1e1alpha_);
  tree_->Branch("sensitivity.topology_1engamma",&sensitivity_.topology_1engamma_);


  tree_->Branch("sensitivity.calorimeter_hit_count",&sensitivity_.calorimeter_hit_count_);
  tree_->Branch("sensitivity.cluster_count",&sensitivity_.cluster_count_);
  tree_->Branch("sensitivity.track_count",&sensitivity_.track_count_);
  tree_->Branch("sensitivity.associated_track_count",&sensitivity_.associated_track_count_);
  tree_->Branch("sensitivity.alpha_count",&sensitivity_.alpha_count_);
  tree_->Branch("sensitivity.foil_alpha_count",&sensitivity_.foil_alpha_count_);
  tree_->Branch("sensitivity.latest_delayed_hit",&sensitivity_.latest_delayed_hit_);
  tree_->Branch("sensitivity.small_cluster_count",&sensitivity_.small_cluster_count_);
  tree_->Branch("sensitivity.third_calo_energy",&sensitivity_.highest_gamma_energy_);// Highest energy gamma (dupe of highest_gamma_energy for legacy)
  tree_->Branch("sensitivity.highest_gamma_energy",&sensitivity_.highest_gamma_energy_);
  tree_->Branch("sensitivity.edgemost_vertex",&sensitivity_.edgemost_vertex_);

  truthtree_ = new TTree("Truth","Truth");
  truthtree_->SetDirectory(hfile_);
  truthtree_->Branch("truth.lower_electron_energy",&truth_.lower_electron_energy_);
  truthtree_->Branch("truth.higher_electron_energy",&truth_.higher_electron_energy_);

  this->_set_initialized(true);
}
//! [SensitivityModule::Process]
dpp::base_module::process_status
SensitivityModule::process(datatools::things& workItem) {

  bool passesTwoCalorimeters=false;
  bool passesTwoPlusCalos=false;
  bool passesTwoClusters=false;
  bool passesTwoTracks=false;
  bool passesAssociatedCalorimeters=false;
  uint numberOfElectrons=0;
  uint numberOfGammas=0;
  double totalCalorimeterEnergy=0;
  double higherElectronEnergy=0;
  double lowerElectronEnergy=0;
  int verticesOnFoil=0;
  int firstVerticesOnFoil=0;
  double timeDelay=-1;
  bool is2electron=false;
  double internalProbability=-1;
  double internalChiSquared=-1;
  double externalChiSquared=-1;
  double externalProbability=-1;
  double foilProjectedExternalProbability=-1;
  double foilProjectedInternalProbability=-1;
  bool is1e1gamma=false;
  bool is1engamma=false;
  bool is1e1alpha=false;
  double electrongammaInternalProbability=-1;
  double electrongammaExternalProbability=-1;
  double electrongammaProjInternalProb=-1;
  double electrongammaProjExternalProb=-1;
  double higherTrueEnergy=0;
  double lowerTrueEnergy=0;
  double totalTrueEnergy=0;
  double clusterCount=0;
  int trackCount=0;
  int alphaCount=0;
  int foilAlphaCount=0;
  int associatedTrackCount=0;
  double smallClusterCount=0;
  double maxAlphaTime=-1;
  double caloHitCount=0;
  double highestGammaEnergy=0;
  double edgemostVertex=0;

  std::vector<snemo::datamodel::particle_track> gammaCandidates;
  std::vector<snemo::datamodel::particle_track> electronCandidates;
  std::vector<snemo::datamodel::particle_track> alphaCandidates;

  std::vector<double> gammaEnergies;
  std::vector<double> electronEnergies;
  std::vector<double> traj_cl_delayed_time;

  // Set to a value outside the detector
  TVector3 vertexPosition[2];
  for (int i=0;i<2;i++)
    vertexPosition[i].SetXYZ(-9999,-9999,-9999);
  // Define another vertex position for alphas etc
  TVector3 vertexPositionAlpha[1];
  for (int i=0;i<1;i++)
    vertexPositionAlpha[i].SetXYZ(-9999,-9999,-9999);
  TVector3 vertexPositionElectron[1];
  for (int i=0;i<1;i++)
    vertexPositionElectron[i].SetXYZ(-9999,-9999,-9999);
  TVector3 projectedVertexPosition[2];
  for (int i=0;i<2;i++)
    projectedVertexPosition[i].SetXYZ(0,-9999,-9999);
  TVector3 projectedVertexPositionAlpha[1];
  for (int i=0;i<1;i++)
    projectedVertexPositionAlpha[i].SetXYZ(0,-9999,-9999);
  TVector3 projectedVertexPositionElectron[1];
  for (int i=0;i<1;i++)
    projectedVertexPositionElectron[i].SetXYZ(0,-9999,-9999);
  TVector3 trackDirection[2];
  double angleBetweenTracks;
  bool sameSideOfFoil=false;
  double projectionDistanceXY=0;

  uint highEnergyIndex = 0;

  // Grab calibrated data bank
  // Calibrated data will only be present in reconstructed files,
  // so wrap in a try block
  try {
    const snemo::datamodel::calibrated_data& calData = workItem.get<snemo::datamodel::calibrated_data>("CD");

    int nCalorimeterHits=0;
    int nCalHitsOverHighLimit=0;
    int nCalHitsOverLowLimit=0;

    if (calData.has_calibrated_calorimeter_hits())
      {
        const snemo::datamodel::calibrated_data::calorimeter_hit_collection_type & calHits=calData.calibrated_calorimeter_hits();
        for (snemo::datamodel::calibrated_data::calorimeter_hit_collection_type::const_iterator   iHit = calHits.begin(); iHit != calHits.end(); ++iHit) {
          const snemo::datamodel::calibrated_calorimeter_hit & calHit = iHit->get();
          double energy=calHit.get_energy() ;
          totalCalorimeterEnergy += energy;

          if (timeDelay<0)//first hit
          {
            timeDelay=calHit.get_time();
          }
          else
          {
            timeDelay -=calHit.get_time(); // Get time between the first two hits: if there are more than two hits we will reject the event anyway
          }
          ++nCalorimeterHits;
          if (energy>=highEnergyLimit)++nCalHitsOverHighLimit;
          if (energy>=lowEnergyLimit)++nCalHitsOverLowLimit;

        }
      }
      caloHitCount=nCalHitsOverLowLimit;
      if (nCalorimeterHits==2 && nCalHitsOverHighLimit>=1 && nCalHitsOverLowLimit==2)
        {
          passesTwoCalorimeters=true;
        }
      if (nCalHitsOverHighLimit>=1 && nCalHitsOverLowLimit>=2)
      {
        passesTwoPlusCalos=true;
      }
    }
  catch (std::logic_error& e) {
    std::cerr << "failed to grab CD bank : " << e.what() << std::endl;
    return dpp::base_module::PROCESS_INVALID;
  }

  // Number of tracker clusters comes from the TCD databank
  // We want two clusters of three cells
  try {
    const snemo::datamodel::tracker_clustering_data& clusterData = workItem.get<snemo::datamodel::tracker_clustering_data>("TCD");
    if (clusterData.has_default_solution ()) // Looks as if there is a possibility of alternative solutions. Is it sufficient to use the default?
      {
        snemo::datamodel::tracker_clustering_solution solution = clusterData.get_default_solution () ;
        snemo::datamodel::tracker_clustering_solution::cluster_col_type clusters=solution.get_clusters();
        for (snemo::datamodel::tracker_clustering_solution::cluster_col_type::const_iterator iCluster = clusters.begin();  iCluster != clusters.end(); ++ iCluster)
        {
          const snemo::datamodel::tracker_cluster & cluster = iCluster->get();

          if (cluster.get_number_of_hits()>=minHitsInCluster) ++clusterCount;
            else ++smallClusterCount;
        }
      }
    if (clusterCount==2 )
      {
        passesTwoClusters=true;
      }
  }
  catch (std::logic_error& e) {
    std::cerr << "failed to grab TCD bank : " << e.what() << std::endl;
    return dpp::base_module::PROCESS_INVALID;
  }


  // Number of particle tracks PTD databank
  // We want two particle tracks to calculate 2e internal/external probability
  // If we have one track and a remote hit, we can calculate 1e1gamma probabilities

  try
  {
    const snemo::datamodel::particle_track_data& trackData = workItem.get<snemo::datamodel::particle_track_data>("PTD");
    if (trackData.has_particles ())
    {

      for (uint iParticle=0;iParticle<trackData.get_number_of_particles();++iParticle)
      {

        snemo::datamodel::particle_track track=trackData.get_particle(iParticle);
        switch (track.get_charge())
        {
          case snemo::datamodel::particle_track::NEUTRAL:
          {
            gammaCandidates.push_back(track);
            numberOfGammas++;
            double thisEnergy=0;
            // Store the gamma candidate energies
            for (unsigned int hit=0; hit<track.get_associated_calorimeter_hits().size();++hit)
            {

              const snemo::datamodel::calibrated_calorimeter_hit & calo_hit = track.get_associated_calorimeter_hits().at(hit).get();
              thisEnergy += calo_hit.get_energy();
            }
            gammaEnergies.push_back(thisEnergy);

            continue;
          }
          case snemo::datamodel::particle_track::POSITIVE:
          case snemo::datamodel::particle_track::NEGATIVE:
          case snemo::datamodel::particle_track::UNDEFINED:
          trackCount++;
          break;
          default:
          continue;
        }

        // Now we have only charged particles remaining there are a few things we can do:
        // Identify electron candidates
        // Identify alpha candidates
        // Get edgemost inner vertex, regardless of whether they have associated calorimeters etc

        // First the vertex:
        // Find the y coordinate for the innermost vertex that is nearest to
        // the x-calo wall (large +/- y value). We could use this to identify
        // Events so near the edge they can't make a 3-cell track
        double thisInnerVertex=0; // stores the y coordinate of the vertex closest to the source foil
        double closestX=9999;
        bool hasVertexOnFoil=false;
        if (track.has_vertices()) // There doesn't seem to be any time ordering to the vertices
        {
          for (unsigned int iVertex=0; iVertex<track.get_vertices().size();++iVertex)
          {
            const geomtools::blur_spot & vertex = track.get_vertices().at(iVertex).get();
            if (snemo::datamodel::particle_track::vertex_is_on_source_foil(vertex))
            {
              hasVertexOnFoil = true;
            }
            const geomtools::vector_3d & vertexTranslation = vertex.get_placement().get_translation();
            // Get details for the vertex nearest the source foil, which is at x = 0
            if (TMath::Abs(vertexTranslation.x()) < closestX) // this is nearer the foil
            {
              // So get its y position, which will tell us how near the xcalo wall it is
              // Note there might be another vertex nearer the wall (the far end of the track) but we don't care, we want to know where the foil vertex is
              thisInnerVertex=vertexTranslation.y();
              closestX=vertexTranslation.x();
            } // end for each vertex
          }
          // For the event, we are going to note the foil vertex that is nearest the edge of the detector
          if(TMath::Abs(thisInnerVertex) > TMath::Abs(edgemostVertex))
          edgemostVertex=thisInnerVertex;
          if (hasVertexOnFoil) verticesOnFoil++;
        } // End of scanning for the edgemost vertex

        // Electron candidates are tracks with associated calorimeter hits, is this one?
        if (track.has_associated_calorimeter_hits())
        {
          electronCandidates.push_back(track);
          double thisEnergy=0;
          // Store the electron candidate energies
          for (unsigned int hit=0; hit<track.get_associated_calorimeter_hits().size();++hit)
          {

            const snemo::datamodel::calibrated_calorimeter_hit & calo_hit = track.get_associated_calorimeter_hits().at(hit).get();
            thisEnergy += calo_hit.get_energy();
          }
          electronEnergies.push_back(thisEnergy);
        }
        if (track.has_trajectory())
        {
          const snemo::datamodel::tracker_trajectory & the_trajectory = track.get_trajectory();
          const snemo::datamodel::tracker_cluster & the_cluster = the_trajectory.get_cluster();

          // Alpha candidates are undefined charge particles associated with a delayed hit and no associated hit
          if (track.get_charge()==snemo::datamodel::particle_track::UNDEFINED && !track.has_associated_calorimeter_hits() && the_cluster.is_delayed()>0) // ###### add check for delayed hit
          {
            alphaCandidates.push_back(track);
            traj_cl_delayed_time.push_back(the_cluster.get_hit(0).get_delayed_time());
          }
        }

      } // end for each particle
    } // end if has particles

    if (electronCandidates.size()==2 && trackCount==2)
    {
      is2electron = true;
    }
    if (electronCandidates.size()==1 && numberOfGammas>=1 && trackCount==1)
    {
      is1engamma = true;
      if (numberOfGammas==1) is1e1gamma = true;
    }
    if (electronCandidates.size() ==1 && alphaCandidates.size() ==1)
    {
      is1e1alpha = true;
    }

    // Calculate values for the 1e1alpha topology
    // Want to iterate over the tracks in the electronCandidate and alphaCandidate vectors
    if (is1e1alpha)
    {
      for (uint iParticle=0;iParticle<(electronCandidates.size());++iParticle)
      {
        snemo::datamodel::particle_track track=electronCandidates.at(iParticle);
        if (track.has_trajectory())
        {
          const snemo::datamodel::base_trajectory_pattern & the_base_pattern = track.get_trajectory().get_pattern();
          if (the_base_pattern.get_pattern_id()=="line") {
            const geomtools::line_3d & the_shape = (const geomtools::line_3d&)the_base_pattern.get_shape();
            // Find the two ends of the track
            geomtools::vector_3d one_end=the_shape.get_first();
            geomtools::vector_3d the_other_end=the_shape.get_last();
            // which is which?
            geomtools::vector_3d outermost_end = ((TMath::Abs(one_end.x()) >= TMath::Abs(the_other_end.x())) ? one_end: the_other_end);
            geomtools::vector_3d direction = the_shape.get_direction_on_curve(the_shape.get_first()); // Only the first stores the direction for a line track
            int multiplier = (direction.x() * outermost_end.x() > 0)? 1: -1; // If the direction points the wrong way, reverse it
            trackDirection[iParticle].SetXYZ(direction.x() * multiplier, direction.y() * multiplier, direction.z() * multiplier);
            } //end line track
            else {
              const geomtools::helix_3d & the_shape = (const geomtools::helix_3d&)the_base_pattern.get_shape();
              // Find the two ends of the track
              geomtools::vector_3d one_end=the_shape.get_first();
              geomtools::vector_3d the_other_end=the_shape.get_last();
              // which is which?
              geomtools::vector_3d foilmost_end = ((TMath::Abs(one_end.x()) < TMath::Abs(the_other_end.x())) ? one_end: the_other_end);
              geomtools::vector_3d outermost_end = ((TMath::Abs(one_end.x()) >= TMath::Abs(the_other_end.x())) ? one_end: the_other_end);

              geomtools::vector_3d direction = the_shape.get_direction_on_curve(foilmost_end); // Not the same on a curve
              int multiplier = (direction.x() * outermost_end.x() > 0)? 1: -1; // If the direction points the wrong way, reverse it

              trackDirection[iParticle].SetXYZ(direction.x() * multiplier, direction.y() * multiplier, direction.z() * multiplier);
            }// end helix track
          }//end if has trajectory
        if (track.has_vertices()) // There doesn't seem to be any time ordering to the vertices
        {
          for (unsigned int iVertex=0; iVertex<track.get_vertices().size();++iVertex)
          {
            const geomtools::blur_spot & vertex = track.get_vertices().at(iVertex).get();
            const geomtools::vector_3d & vertexTranslation = vertex.get_placement().get_translation();
            // Get details for the vertex nearest the source foil, which is at x = 0
            if (TMath::Abs(vertexTranslation.x()) < TMath::Abs(vertexPositionElectron[iParticle].X())) // this is nearer the foil
            {
              vertexPositionElectron[iParticle].SetXYZ(vertexTranslation.x(),vertexTranslation.y(),vertexTranslation.z());
            }
          }
        }
        // Calculate the projected vertex separation
        double scale=vertexPositionElectron[iParticle].X()/trackDirection[iParticle].X();
        projectedVertexPositionElectron[iParticle]=vertexPositionElectron[iParticle] - scale*trackDirection[iParticle]; // The second term is the extension to the track to project it back with a straight line
      }

      for (uint iParticle=0;iParticle<(alphaCandidates.size());++iParticle)
      {
        snemo::datamodel::particle_track track=alphaCandidates.at(iParticle);
        if (track.has_trajectory())
        {
          const snemo::datamodel::base_trajectory_pattern & the_base_pattern = track.get_trajectory().get_pattern();
          if (the_base_pattern.get_pattern_id()=="line") {
            const geomtools::line_3d & the_shape = (const geomtools::line_3d&)the_base_pattern.get_shape();
            // Find the two ends of the track
            geomtools::vector_3d one_end=the_shape.get_first();
            geomtools::vector_3d the_other_end=the_shape.get_last();
            // which is which?
            geomtools::vector_3d outermost_end = ((TMath::Abs(one_end.x()) >= TMath::Abs(the_other_end.x())) ? one_end: the_other_end);
            geomtools::vector_3d direction = the_shape.get_direction_on_curve(the_shape.get_first()); // Only the first stores the direction for a line track
            int multiplier = (direction.x() * outermost_end.x() > 0)? 1: -1; // If the direction points the wrong way, reverse it
            trackDirection[iParticle].SetXYZ(direction.x() * multiplier, direction.y() * multiplier, direction.z() * multiplier);
            } //end line track
            else {
              const geomtools::helix_3d & the_shape = (const geomtools::helix_3d&)the_base_pattern.get_shape();
              // Find the two ends of the track
              geomtools::vector_3d one_end=the_shape.get_first();
              geomtools::vector_3d the_other_end=the_shape.get_last();
              // which is which?
              geomtools::vector_3d foilmost_end = ((TMath::Abs(one_end.x()) < TMath::Abs(the_other_end.x())) ? one_end: the_other_end);
              geomtools::vector_3d outermost_end = ((TMath::Abs(one_end.x()) >= TMath::Abs(the_other_end.x())) ? one_end: the_other_end);

              geomtools::vector_3d direction = the_shape.get_direction_on_curve(foilmost_end); // Not the same on a curve
              int multiplier = (direction.x() * outermost_end.x() > 0)? 1: -1; // If the direction points the wrong way, reverse it

              trackDirection[iParticle].SetXYZ(direction.x() * multiplier, direction.y() * multiplier, direction.z() * multiplier);
            }// end helix track
          }//end if has trajectory
        if (track.has_vertices()) // There doesn't seem to be any time ordering to the vertices
        {
          for (unsigned int iVertex=0; iVertex<track.get_vertices().size();++iVertex)
          {
            const geomtools::blur_spot & vertex = track.get_vertices().at(iVertex).get();
            const geomtools::vector_3d & vertexTranslation = vertex.get_placement().get_translation();
            // Get details for the vertex nearest the source foil, which is at x = 0
            if (TMath::Abs(vertexTranslation.x()) < TMath::Abs(vertexPositionAlpha[iParticle].X())) // this is nearer the foil
            {
              vertexPositionAlpha[iParticle].SetXYZ(vertexTranslation.x(),vertexTranslation.y(),vertexTranslation.z());
            }
          }
        }
        double scale=vertexPositionAlpha[iParticle].X()/trackDirection[iParticle].X();
        projectedVertexPositionAlpha[iParticle]=vertexPositionAlpha[iParticle] - scale*trackDirection[iParticle]; // The second term is the extension to the track to project it back with a straight line
      }
    }

    // For 2-electron and 1-e-n-gamma events, calculate some internal and external probablilities
    if (is2electron || is1engamma)
    {
      double calorimeterTime[2];
      double calorimeterTimeSigma[2];
      double trackLength[2];
      double calorimeterEnergy[2];
      double calorimeterEnergySigma[2];
      double beta[2];
      double projectedTrackLength[2];
      double trackLengthSigma[2];
      double totalTimeVariance[2];
      double projectedTimeVariance[2];
      int particleIndex[2];

      // Load electron information: there will be either 1 or 2 of these
      for (uint iParticle=0;iParticle<electronCandidates.size();++iParticle)
      {
        calorimeterTime[iParticle]=0;
        calorimeterTimeSigma[iParticle]=0;
        trackLength[iParticle]=0;
        calorimeterEnergy[iParticle]=0;
        calorimeterEnergySigma[iParticle]=0;
        double sigma2=0;
        snemo::datamodel::particle_track track=electronCandidates.at(iParticle);
        double earliest_time=9999999999;
        // Get the calorimeter hit times and energies from the array of associated hits
        for (unsigned int hit=0; hit<track.get_associated_calorimeter_hits().size();++hit)
        {
          // Maybe there are some little hits but we only care for the highest-energy, and it needs to be above the threshold
          const snemo::datamodel::calibrated_calorimeter_hit & calo_hit = track.get_associated_calorimeter_hits().at(hit).get();

          if (calo_hit.get_time() < earliest_time)
          { // if this is the earliest hit then set the calo time to that. Add the energies of all associated hits
            calorimeterTime[iParticle] = calo_hit.get_time();
            calorimeterTimeSigma[iParticle] = calo_hit.get_sigma_time();
          }
          calorimeterEnergy[iParticle] += calo_hit.get_energy();
          sigma2 += calo_hit.get_sigma_energy()*calo_hit.get_sigma_energy(); // Add in quadrature

        } // for each hit
        calorimeterEnergySigma[iParticle] = TMath::Sqrt(sigma2);

        // Calculate beta = speed as fraction of speed of light
        beta[iParticle] = TMath::Sqrt(calorimeterEnergy[iParticle] * (calorimeterEnergy[iParticle] + 2 * electronMass)) / (calorimeterEnergy[iParticle] +  electronMass);

        // Now get the two electrons' track lengths and some info about the track direction and vertex

        if (track.has_trajectory())
        {
          trackLength[iParticle]=track.get_trajectory().get_pattern().get_shape().get_length();
          trackLengthSigma[iParticle] = 0; // Uncertainty on track length is insignificant compared to energy and time resolution for electrons

          // Get track direction info at the innermost end of the track, moving towards the outermost end
          // This is harder than it sounds from the info available as we need to decide which end is which
          // and which direction it is moving

          const snemo::datamodel::base_trajectory_pattern & the_base_pattern = track.get_trajectory().get_pattern();
          if (the_base_pattern.get_pattern_id()=="line") {
            const geomtools::line_3d & the_shape = (const geomtools::line_3d&)the_base_pattern.get_shape();
            // Find the two ends of the track
            geomtools::vector_3d one_end=the_shape.get_first();
            geomtools::vector_3d the_other_end=the_shape.get_last();
            // which is which?
            geomtools::vector_3d outermost_end = ((TMath::Abs(one_end.x()) >= TMath::Abs(the_other_end.x())) ? one_end: the_other_end);
            geomtools::vector_3d direction = the_shape.get_direction_on_curve(the_shape.get_first()); // Only the first stores the direction for a line track
            int multiplier = (direction.x() * outermost_end.x() > 0)? 1: -1; // If the direction points the wrong way, reverse it
            trackDirection[iParticle].SetXYZ(direction.x() * multiplier, direction.y() * multiplier, direction.z() * multiplier);
          } //end line track
          else {
            const geomtools::helix_3d & the_shape = (const geomtools::helix_3d&)the_base_pattern.get_shape();
            // Find the two ends of the track
            geomtools::vector_3d one_end=the_shape.get_first();
            geomtools::vector_3d the_other_end=the_shape.get_last();
            // which is which?
            geomtools::vector_3d foilmost_end = ((TMath::Abs(one_end.x()) < TMath::Abs(the_other_end.x())) ? one_end: the_other_end);
            geomtools::vector_3d outermost_end = ((TMath::Abs(one_end.x()) >= TMath::Abs(the_other_end.x())) ? one_end: the_other_end);

            geomtools::vector_3d direction = the_shape.get_direction_on_curve(foilmost_end); // Not the same on a curve
            int multiplier = (direction.x() * outermost_end.x() > 0)? 1: -1; // If the direction points the wrong way, reverse it

            trackDirection[iParticle].SetXYZ(direction.x() * multiplier, direction.y() * multiplier, direction.z() * multiplier);
          }// end helix track
        }// end if has_trajectory

        double theoreticalTimeOfFlight=trackLength[iParticle]/ (beta[iParticle] * speedOfLight);

        // calculate total time variance for electron
        totalTimeVariance[iParticle] =
        pow(calorimeterTimeSigma[iParticle],2)
        + pow(calorimeterEnergySigma[iParticle],2)
        * pow((theoreticalTimeOfFlight*electronMass*electronMass),2)
        / pow( (calorimeterEnergy[iParticle] * (calorimeterEnergy[iParticle]+electronMass) * (calorimeterEnergy[iParticle]+ 2 * electronMass) ),2);

        double projTimeOfFlight=trackLength[iParticle]/ (beta[iParticle] * speedOfLight);
        projectedTimeVariance[iParticle] =
        pow(calorimeterTimeSigma[iParticle],2)
        + pow(calorimeterEnergySigma[iParticle],2)
        * pow((projTimeOfFlight*electronMass*electronMass),2)
        / pow( (calorimeterEnergy[iParticle] * (calorimeterEnergy[iParticle]+electronMass) * (calorimeterEnergy[iParticle]+ 2 * electronMass) ),2);


        // Now get some information about the vertices
        if (track.has_vertices()) // There doesn't seem to be any time ordering to the vertices
        {

          for (unsigned int iVertex=0; iVertex<track.get_vertices().size();++iVertex)
          {
            const geomtools::blur_spot & vertex = track.get_vertices().at(iVertex).get();
            const geomtools::vector_3d & vertexTranslation = vertex.get_placement().get_translation();
            // Get details for the vertex nearest the source foil, which is at x = 0
            if (TMath::Abs(vertexTranslation.x()) < TMath::Abs(vertexPosition[iParticle].X())) // this is nearer the foil
            {
              vertexPosition[iParticle].SetXYZ(vertexTranslation.x(),vertexTranslation.y(),vertexTranslation.z());
            }
          }
        } // end if has vertices

        // Calculate the projected vertex separation
        // Here's how we will do it: for each track, take the vertex nearest the foil
        // project it back onto the foil (x=0) using the direction of the direction at the first vertex
        // Then calculate the distance between the two projected vertices
        double scale=vertexPosition[iParticle].X()/trackDirection[iParticle].X();
        projectedVertexPosition[iParticle]=vertexPosition[iParticle] - scale*trackDirection[iParticle]; // The second term is the extension to the track to project it back with a straight line
        projectedTrackLength[iParticle]=trackLength[iParticle]+TMath::Abs(scale*(trackDirection[iParticle]).Mag()); // This gives a longer track as we add the extension
        // Get the larger of the 2 distances in the x-y plane between actual vertex and foil-projected vertex, to tell how much track was missed
        double thisProjectionDistance=(vertexPosition[iParticle]-projectedVertexPosition[iParticle]).Perp();
        if (thisProjectionDistance > projectionDistanceXY)projectionDistanceXY=thisProjectionDistance;
      } // end for each electron

      // Populate the electron energies
      if (is2electron)
      {
          highEnergyIndex=(calorimeterEnergy[0]>calorimeterEnergy[1]?0:1);
          higherElectronEnergy=calorimeterEnergy[highEnergyIndex];
          lowerElectronEnergy=calorimeterEnergy[1-highEnergyIndex];
          passesAssociatedCalorimeters=true;
      }


      // If it is a 1-e-n-gamma event, load the second array elements with the properties of the highest-energy gamma

      if (is1engamma)
      {
        // Second particle is a photon so it goes at the speed of light
        beta[1] = 1.;

        // Find the highest-energy gamma
        uint highEnergyIndex=0;
        double topEnergy;
        for (int i=0;i<gammaCandidates.size();i++)
        {
          snemo::datamodel::particle_track track = gammaCandidates.at(i);
          double thisParticleEnergy=0;
          // Sum the energies of all calorimeter hits for the particle
          for (unsigned int hit=0; hit<track.get_associated_calorimeter_hits().size();++hit)
          {
            // Maybe there are some little hits but we only care for the highest-energy, and it needs to be above the threshold
            const snemo::datamodel::calibrated_calorimeter_hit & calo_hit = track.get_associated_calorimeter_hits().at(hit).get();
            thisParticleEnergy += calo_hit.get_energy();
          }
          if (thisParticleEnergy>topEnergy)
          {
            highEnergyIndex=i;
            topEnergy=thisParticleEnergy;
          }
        }

        snemo::datamodel::particle_track gamma = gammaCandidates.at(highEnergyIndex);

        // Get the details of the highest-energy photon

        // temporary variables for the calculation
        double sigma2=0;
        double earliest_time=9999999999;
        geomtools::vector_3d loc (0,0,0);

        // Get total energy and earliest hit time
        for (unsigned int hit=0; hit<gamma.get_associated_calorimeter_hits().size();++hit)
        {
          // Maybe there are some little hits but we only care for the highest-energy, and it needs to be above the threshold
          const snemo::datamodel::calibrated_calorimeter_hit & calo_hit = gamma.get_associated_calorimeter_hits().at(hit).get();

          if (calo_hit.get_time() < earliest_time)
          { // if this is the earliest hit then set the calo time to that and get its vertex position
            calorimeterTime[1] = calo_hit.get_time();
            calorimeterTimeSigma[1] = calo_hit.get_sigma_time();

            // Get the vertex position
            const geomtools::mapping & the_mapping = geometry_manager_->get_mapping();
            // I got this from PTD2root but I don't understand what the two alternatives mean
            if (! the_mapping.validate_id(calo_hit.get_geom_id())) {
              std::vector<geomtools::geom_id> gids;
              the_mapping.compute_matching_geom_id(calo_hit.get_geom_id(), gids); // front calo block = last entry
              const geomtools::geom_info & info = the_mapping.get_geom_info(gids.back()); // in vector gids
              loc  = info.get_world_placement().get_translation();
            }
            else {
              const geomtools::geom_info & info = the_mapping.get_geom_info(calo_hit.get_geom_id());
              loc  = info.get_world_placement().get_translation();
            }

          }
          // Add the energies of all associated hits
          calorimeterEnergy[1] += calo_hit.get_energy();
          sigma2 += calo_hit.get_sigma_energy() * calo_hit.get_sigma_energy(); // Add energy sigmas in quadrature

        }
        calorimeterEnergySigma[1]=TMath::Sqrt(sigma2);

        // Calculate track length using the inner vertex of the electron track
        TVector3 gammaTrack (loc.x()-vertexPosition[0].X() ,loc.y()-vertexPosition[0].Y(),loc.z()-vertexPosition[0].Z());
        double multiplier = 1.0/gammaTrack.Mag(); // To get a unit vector
        trackDirection[1].SetXYZ(gammaTrack.x() * multiplier, gammaTrack.y() * multiplier, gammaTrack.z() * multiplier);
        trackLength[1]=gammaTrack.Mag();
        trackLengthSigma[1]=0.9; // Corresponds to 0.9 ns, justified in docdb 3799 page 10

        // Calculate projected track length using the foil-projected vertex of the electron track
        TVector3 projTrack(loc.x()-projectedVertexPosition[0].X() ,loc.y()-projectedVertexPosition[0].Y(),loc.z()-projectedVertexPosition[0].Z());
        projectedTrackLength[1]=projTrack.Mag();

        // Calculate total time variance and projected time variance for gamma
        // Sum the variances from the time and track length uncertainties (track length uncertainty is already converted to time units)
        totalTimeVariance[1] = calorimeterTimeSigma[1] * calorimeterTimeSigma[1] + trackLengthSigma[1] * trackLengthSigma[1];
        projectedTimeVariance[1] = totalTimeVariance[1] ; // Doesn't depend on track length (at least in our current approximation)

        higherElectronEnergy = calorimeterEnergy[0];
        lowerElectronEnergy=0;

      } // end if 1-e-n-gamma

      // Calculate internal and external probabilities
      CalculateProbabilities(internalProbability, externalProbability, &calorimeterEnergy[0],  &beta[0], &trackLength[0], &calorimeterTime[0], &totalTimeVariance[0] );
      // Try again with the track to the foil-projected vertex
      CalculateProbabilities(foilProjectedInternalProbability, foilProjectedExternalProbability,&calorimeterEnergy[0], &beta[0], &projectedTrackLength[0], &calorimeterTime[0], &projectedTimeVariance[0] );

    }// end if either 2e or 1e n gamma

  }// end try on PTD bank
  catch (std::logic_error& e) {
    std::cerr << "failed to grab PTD bank : " << e.what() << std::endl;
    return dpp::base_module::PROCESS_INVALID;
  } //end catch

  // From SD bank:
  // Get (true) energy of more energetic electron
  // Get (true) energy of less energetic electron
  try
    {
      const mctools::simulated_data& simData = workItem.get<mctools::simulated_data>("SD");
      if (simData.has_data())
      {
        mctools::simulated_data::primary_event_type primaryEvent=simData.get_primary_event ();
        for (int i=0;i<primaryEvent.get_number_of_particles();i++)// should be 2 particles for 0nubb
        {
          genbb::primary_particle trueParticle= primaryEvent.get_particle(i);
          double energy=trueParticle.get_kinetic_energy();
          totalTrueEnergy += energy;
          // Populate the two highest true energies
          if (energy > higherTrueEnergy)
          {
            lowerTrueEnergy=higherTrueEnergy;
            higherTrueEnergy=energy;
          }
          else if (energy > lowerTrueEnergy)
          {
            lowerTrueEnergy=energy;
          }
        }
      }
    } // end try for SD bank
  catch (std::logic_error& e) {
    //std::cerr << "failed to grab SD bank : " << e.what() << std::endl;
    //return dpp::base_module::PROCESS_ERROR;
    // This is OK, if it's data there will be no SD bank
  }     // end catch for SD bank

  passesTwoTracks = (trackCount==2);
  // Sort the electron energies, largest first
  std::sort (electronEnergies.begin(), electronEnergies.end());
  std::reverse (electronEnergies.begin(), electronEnergies.end());
  // Sort the electron energies, largest first
  std::sort (gammaEnergies.begin(), gammaEnergies.end());
  std::reverse (gammaEnergies.begin(), gammaEnergies.end());

  higherElectronEnergy=0;
  lowerElectronEnergy=0;
  if (electronCandidates.size()>0) higherElectronEnergy=electronEnergies.at(0);
  if (electronCandidates.size()>1) lowerElectronEnergy=electronEnergies.at(1);

  highestGammaEnergy=0;
  if (gammaCandidates.size()>0) highestGammaEnergy=gammaEnergies.at(0);

  // Cuts pass/fail
  sensitivity_.passes_two_calorimeters_ = passesTwoCalorimeters;
  sensitivity_.passes_two_plus_calos_ = passesTwoPlusCalos;
  sensitivity_.passes_two_clusters_ = passesTwoClusters;
  sensitivity_.passes_two_tracks_ = passesTwoTracks;
  sensitivity_.passes_associated_calorimeters_ = passesAssociatedCalorimeters;
  sensitivity_.number_of_electrons_=electronCandidates.size();
  sensitivity_.electron_energies_=electronEnergies;
  sensitivity_.gamma_energies_=gammaEnergies;


  // Reconstructed energies
  sensitivity_.lower_electron_energy_=lowerElectronEnergy;
  sensitivity_.higher_electron_energy_=higherElectronEnergy;
  sensitivity_.total_calorimeter_energy_ = totalCalorimeterEnergy;

  // Truth info, simulation only
  sensitivity_.true_highest_primary_energy_=higherTrueEnergy;
  sensitivity_.true_second_primary_energy_=lowerTrueEnergy;
  sensitivity_.true_total_energy_= totalTrueEnergy;
  sensitivity_.true_lower_electron_energy_=lowerTrueEnergy;
  sensitivity_.true_higher_electron_energy_=higherTrueEnergy;

  // "First" track is the higher energy one
  //uint highEnergyIndex =(calorimeterEnergy[0]>calorimeterEnergy[1] ? 0:1);
  uint lowEnergyIndex = 1-highEnergyIndex;

  // Vertices
  sensitivity_.vertices_on_foil_=verticesOnFoil;
  sensitivity_.first_vertices_on_foil_=firstVerticesOnFoil;
  sensitivity_.first_vertex_x_= vertexPosition[highEnergyIndex].X();
  sensitivity_.first_vertex_y_= vertexPosition[highEnergyIndex].Y();
  sensitivity_.first_vertex_z_= vertexPosition[highEnergyIndex].Z();
  sensitivity_.second_vertex_x_= vertexPosition[lowEnergyIndex].X();
  sensitivity_.second_vertex_y_= vertexPosition[lowEnergyIndex].Y();
  sensitivity_.second_vertex_z_= vertexPosition[lowEnergyIndex].Z();
  sensitivity_.vertex_separation_= (vertexPosition[0] - vertexPosition[1]).Mag();
  sensitivity_.first_proj_vertex_y_= projectedVertexPosition[highEnergyIndex].Y();
  sensitivity_.first_proj_vertex_z_= projectedVertexPosition[highEnergyIndex].Z();
  sensitivity_.second_proj_vertex_y_= projectedVertexPosition[lowEnergyIndex].Y();
  sensitivity_.second_proj_vertex_z_= projectedVertexPosition[lowEnergyIndex].Z();
  sensitivity_.foil_projection_separation_= (projectedVertexPosition[0] - projectedVertexPosition[1]).Mag();
  sensitivity_.projection_distance_xy_=projectionDistanceXY;

  // Vertex for other topologies
  if(is1e1alpha)
  {
    sensitivity_.vertex_separation_= (vertexPositionElectron[0] - vertexPositionAlpha[0]).Mag();
    sensitivity_.foil_projection_separation_= (projectedVertexPositionElectron[0] - projectedVertexPositionAlpha[0]).Mag();
    // First vertex is the electron
    sensitivity_.first_vertex_x_= vertexPositionElectron[0].X();
    sensitivity_.first_vertex_y_= vertexPositionElectron[0].Y();
    sensitivity_.first_vertex_z_= vertexPositionElectron[0].Z();
    // Second vertex is the alpha
    sensitivity_.second_vertex_x_= vertexPositionAlpha[0].X();
    sensitivity_.second_vertex_y_= vertexPositionAlpha[0].Y();
    sensitivity_.second_vertex_z_= vertexPositionAlpha[0].Z();
  }
  // Track direction
  sensitivity_.first_track_direction_x_= trackDirection[highEnergyIndex].X();
  sensitivity_.first_track_direction_y_= trackDirection[highEnergyIndex].Y();
  sensitivity_.first_track_direction_z_= trackDirection[highEnergyIndex].Z();
  sensitivity_.second_track_direction_x_= trackDirection[lowEnergyIndex].X();
  sensitivity_.second_track_direction_y_= trackDirection[lowEnergyIndex].Y();
  sensitivity_.second_track_direction_z_= trackDirection[lowEnergyIndex].Z();
  sensitivity_.same_side_of_foil_= ((trackDirection[0].X() * trackDirection[1].X()) > 0); // X components both positive or both negative
  sensitivity_.angle_between_tracks_= trackDirection[highEnergyIndex].Angle(trackDirection[lowEnergyIndex]);

  // Timing
  sensitivity_.time_delay_=TMath::Abs(timeDelay);
  sensitivity_.traj_cluster_delayed_time_= &traj_cl_delayed_time;
  sensitivity_.internal_probability_=internalProbability;
  sensitivity_.internal_chi_squared_=internalChiSquared;
  sensitivity_.external_chi_squared_=externalChiSquared;
  sensitivity_.external_probability_=externalProbability;
  sensitivity_.foil_projected_internal_probability_=foilProjectedInternalProbability;
  sensitivity_.foil_projected_external_probability_=foilProjectedExternalProbability;

  // Topology

  sensitivity_.topology_1engamma_=is1engamma;
  sensitivity_.topology_1e1gamma_=is1e1gamma;
  sensitivity_.topology_1e1alpha_=is1e1alpha;
  sensitivity_.topology_2e_=is2electron;


  // Debug information
  sensitivity_.calorimeter_hit_count_=caloHitCount;
  sensitivity_.small_cluster_count_=smallClusterCount;
  sensitivity_.cluster_count_=clusterCount;
  sensitivity_.highest_gamma_energy_=highestGammaEnergy;
  sensitivity_.edgemost_vertex_=edgemostVertex;
  sensitivity_.number_of_gammas_=numberOfGammas;
  sensitivity_.track_count_=trackCount;
  sensitivity_.associated_track_count_=electronCandidates.size();
  sensitivity_.alpha_count_=alphaCandidates.size();

  tree_->Fill();
  truth_.lower_electron_energy_=lowerTrueEnergy;
  truth_.higher_electron_energy_=higherTrueEnergy;
  truthtree_->Fill();
  // MUST return a status, see ref dpp::processing_status_flags_type
  return dpp::base_module::PROCESS_OK;
}

// Calculate probabilities for an internal (both particles from the foil) and external (calo 1 -> foil -> calo 2) topology
void SensitivityModule::CalculateProbabilities(double &internalProbability, double &externalProbability, double *calorimeterEnergies,  double *betas, double *trackLengths, double *calorimeterTimes, double *totalTimeVariances )
{
  double theoreticalTimeOfFlight[2];
  double internalEmissionTime[2];
  double internalChiSquared;
  double externalChiSquared;
  for (int count=0;count<2;count++)
  {
    //energies are in MeV
    theoreticalTimeOfFlight[count] = trackLengths[count]/ (betas[count] * speedOfLight);
    internalEmissionTime[count] = calorimeterTimes[count] - theoreticalTimeOfFlight[count];

  } // for each particle

  // Calculate internal probability: both particles emitted at the same time
  // so time between the calo hits should be Time of flight 1 - Time of flight 2

  internalChiSquared = pow((internalEmissionTime[0] - internalEmissionTime[1]) ,2) / (totalTimeVariances[0] + totalTimeVariances[1]) ;
  double integralForProbability=0;
  internalProbability=this->ProbabilityFromChiSquared(internalChiSquared);

  // Calculate external probability: one particle travels to foil then the other travels from foil
  // so time between the calo hits should be Time of flight  1 + Time of flight  2
  externalChiSquared=pow(( TMath::Abs(calorimeterTimes[0]-calorimeterTimes[1]) - (theoreticalTimeOfFlight[0]+theoreticalTimeOfFlight[1]) ),2)/(totalTimeVariances[0] + totalTimeVariances[1]) ;
  externalProbability=this->ProbabilityFromChiSquared(externalChiSquared);

}


// Convert a chi-squared value to a probability by integrating the chi square distribution up to that limit
double SensitivityModule::ProbabilityFromChiSquared(double chiSquared)
{
  // To get probability from a chi squared value, integrate distribution to our chisq limit
  // We have one degree of freedom
  TF1 *function_to_integrate = new TF1("Chi-square function", "pow(x,-0.5) * exp(-0.5 * x)", 0, chiSquared);
  double * params = 0;
  if (chiSquared>3000) chiSquared=3000; // The integral appears to not work properly at values bigger than this, eventually tending to 0 rather than root2pi and thus giving a misleading probability of 1 when it should be almost 0.
  double integral=function_to_integrate->Integral(0,chiSquared,1e-6);
  return (1. - 1./TMath::Sqrt(2.*TMath::Pi()) * integral);
}

//! [SensitivityModule::reset]
void SensitivityModule::reset() {
  hfile_->cd();
  tree_->Write();
  truthtree_->Write();
  hfile_->Close(); //
  std::cout << "In reset: finished conversion, file closed " << std::endl;

  // clean up
  delete hfile_;
  this->_set_initialized(false);
}
