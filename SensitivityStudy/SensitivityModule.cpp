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
void SensitivityModule::initialize(const datatools::properties& /*myConfig*/,
                          datatools::service_manager& /*flServices*/,
                          dpp::module_handle_dict_type& /*moduleDict*/) {

 // Use the method of PTD2ROOT to create a root file with just the branches we need for the sensitivity analysis

  hfile_ = new TFile("sensitivity.root","RECREATE","Output file of Simulation data");
  hfile_->cd();
  tree_ = new TTree("Sensitivity","Sensitivity");
  tree_->SetDirectory(hfile_);
  tree_->Branch("sensitivity.total_calorimeter_energy",&sensitivity_.total_calorimeter_energy_);
  tree_->Branch("sensitivity.passes_two_calorimeters",&sensitivity_.passes_two_calorimeters_);
  tree_->Branch("sensitivity.passes_two_clusters",&sensitivity_.passes_two_clusters_);
  tree_->Branch("sensitivity.passes_two_tracks",&sensitivity_.passes_two_tracks_);
  tree_->Branch("sensitivity.passes_associated_calorimeters",&sensitivity_.passes_associated_calorimeters_);
  tree_->Branch("sensitivity.number_of_electrons",&sensitivity_.number_of_electrons_);
  tree_->Branch("sensitivity.higher_electron_energy",&sensitivity_.higher_electron_energy_);
  tree_->Branch("sensitivity.lower_electron_energy",&sensitivity_.lower_electron_energy_);
  
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
  tree_->Branch("sensitivity.vertex_separation",&sensitivity_.vertex_separation_);
  tree_->Branch("sensitivity.foil_projection_separation",&sensitivity_.foil_projection_separation_);
  tree_->Branch("sensitivity.projection_distance_xy",&sensitivity_.projection_distance_xy_);

  
  tree_->Branch("sensitivity.vertices_on_foil",&sensitivity_.vertices_on_foil_);
  tree_->Branch("sensitivity.first_vertices_on_foil",&sensitivity_.first_vertices_on_foil_); // Obsolete, kept for legacy in case it is used anywhere
  tree_->Branch("sensitivity.angle_between_tracks",&sensitivity_.angle_between_tracks_);
  tree_->Branch("sensitivity.same_side_of_foil",&sensitivity_.same_side_of_foil_);
  tree_->Branch("sensitivity.first_track_momentum_x",&sensitivity_.first_track_momentum_x_);
  tree_->Branch("sensitivity.first_track_momentum_y",&sensitivity_.first_track_momentum_y_);
  tree_->Branch("sensitivity.first_track_momentum_z",&sensitivity_.first_track_momentum_z_);
  tree_->Branch("sensitivity.second_track_momentum_x",&sensitivity_.second_track_momentum_x_);
  tree_->Branch("sensitivity.second_track_momentum_y",&sensitivity_.second_track_momentum_y_);
  tree_->Branch("sensitivity.second_track_momentum_z",&sensitivity_.second_track_momentum_z_);
  
  tree_->Branch("sensitivity.time_delay",&sensitivity_.time_delay_);
  tree_->Branch("sensitivity.internal_probability",&sensitivity_.internal_probability_);
  tree_->Branch("sensitivity.internal_chi_squared",&sensitivity_.internal_chi_squared_);
  tree_->Branch("sensitivity.external_probability",&sensitivity_.external_probability_);
  tree_->Branch("sensitivity.external_chi_squared",&sensitivity_.external_chi_squared_);
  tree_->Branch("sensitivity.foil_projected_internal_probability",&sensitivity_.foil_projected_internal_probability_);
  tree_->Branch("sensitivity.foil_projected_external_probability",&sensitivity_.foil_projected_external_probability_);

  
  tree_->Branch("sensitivity.calorimeter_hit_count",&sensitivity_.calorimeter_hit_count_);
  tree_->Branch("sensitivity.cluster_count",&sensitivity_.cluster_count_);
  tree_->Branch("sensitivity.small_cluster_count",&sensitivity_.small_cluster_count_);
  tree_->Branch("sensitivity.third_calo_energy",&sensitivity_.third_calo_energy_);
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
  bool passesTwoClusters=false;
  bool passesTwoTracks=false;
  bool passesAssociatedCalorimeters=false;
  uint numberOfElectrons=0;
  double totalCalorimeterEnergy=0;
  double higherElectronEnergy=0;
  double lowerElectronEnergy=0;
  int verticesOnFoil=0;
  int firstVerticesOnFoil=0;
  double timeDelay=-1;
  double internalProbability=-1;
  double internalChiSquared=-1;
  double externalChiSquared=-1;
  double externalProbability=-1;
  double foilProjectedExternalProbability=-1;
  double foilProjectedInternalProbability=-1;
  double higherTrueEnergy=0;
  double lowerTrueEnergy=0;
  double totalTrueEnergy=0;
  double clusterCount=0;
  double smallClusterCount=0;
  double caloHitCount=0;
  double thirdCaloEnergy=0;
  double edgemostVertex=0;
  
  // Set to a value outside the detector
  TVector3 vertexPosition[2];
  for (int i=0;i<2;i++)
    vertexPosition[i].SetXYZ(-9999,-9999,-9999);
  TVector3 projectedVertexPosition[2];
  for (int i=0;i<2;i++)
    projectedVertexPosition[i].SetXYZ(0,-9999,-9999);
  TVector3 trackMomentum[2];
  double angleBetweenTracks;
  bool sameSideOfFoil=false;
  double projectionDistanceXY=0;
  
  // Grab calibrated data bank
  // Calibrated data will only be present in simulation output files,
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
          // Populate the two highest calorimeter energies
          if (energy > higherElectronEnergy)
          {
            thirdCaloEnergy=lowerElectronEnergy;
            lowerElectronEnergy=higherElectronEnergy;
            higherElectronEnergy=energy;
          }
          else if (energy > lowerElectronEnergy)
          {
            thirdCaloEnergy=lowerElectronEnergy;
            lowerElectronEnergy=energy;
          }
          else if (energy > thirdCaloEnergy)
          {
            thirdCaloEnergy=energy;
          }
        }
      }
      caloHitCount=nCalHitsOverLowLimit;
      if (nCalorimeterHits==2 && nCalHitsOverHighLimit>=1 && nCalHitsOverLowLimit==2)
        {
          passesTwoCalorimeters=true;
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
  // We want two particle tracks
  try
    {
      const snemo::datamodel::particle_track_data& trackData = workItem.get<snemo::datamodel::particle_track_data>("PTD");
      
      // Even if there is only one track, let's get its vertex, as we might be able to use that to recover events with one track that are at the edge of the detector
      if (trackData.has_particles ())
      {
        for (uint iParticle=0;iParticle<trackData.get_number_of_particles();++iParticle)
        {
          double thisInnerVertex=0; // stores the y coordinate of the vertex closest to the source foil
          double closestX=9999;
          bool hasVertexOnFoil=false;
          snemo::datamodel::particle_track track=trackData.get_particle(iParticle);
          // Find the vertex nearest the foil for the track.
          
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
              }
            }
          }
          // For the event, we are going to note the foil vertex that is nearest the track
          if(TMath::Abs(thisInnerVertex) > TMath::Abs(edgemostVertex))
            edgemostVertex=thisInnerVertex;
          if (hasVertexOnFoil) verticesOnFoil++;
        }
      }
      
      // Other than that, we need 2 tracks for the further processing
      if (trackData.has_particles () && trackData.get_number_of_particles()==2 )
      {
        passesTwoTracks=true;

        // Attempt to match tracks to calorimeter hits.
        // They each need one hit, they need to be over threshold and they need to be different
        if (passesTwoCalorimeters)
        {
          int associatedCalorimeters=0;
	      	  
          // If there are two tracks and 2 calorimeter hits, we can calculate internal and external probabilities
          double calorimeterTime[2];
          double calorimeterTimeSigma[2];
          double trackLength[2];
          double calorimeterEnergy[2];
          double calorimeterEnergySigma[2];
          for (uint iParticle=0;iParticle<2;++iParticle)
          {
            calorimeterTime[iParticle]=0;
            calorimeterTimeSigma[iParticle]=0;
            calorimeterEnergy[iParticle]=0;
            calorimeterEnergySigma[iParticle]=0;
            trackLength[iParticle]=0;
            bool hasVertexOnFoil=false;
            snemo::datamodel::particle_track track=trackData.get_particle(iParticle);
            if (track.has_trajectory()) {
              trackLength[iParticle]=track.get_trajectory().get_pattern().get_shape().get_length();
              
              // Get track direction info

              const snemo::datamodel::base_trajectory_pattern & the_base_pattern = track.get_trajectory().get_pattern();
                if (the_base_pattern.get_pattern_id()=="line") {
                  const geomtools::line_3d & the_shape = (const geomtools::line_3d&)the_base_pattern.get_shape();
                  geomtools::vector_3d direction = the_shape.get_direction_on_curve(the_shape.get_first());
                  trackMomentum[iParticle].SetXYZ(direction.x(),direction.y(),direction.z());
                }
                else {
                  const geomtools::helix_3d & the_shape = (const geomtools::helix_3d&)the_base_pattern.get_shape();
                  geomtools::vector_3d direction = the_shape.get_direction_on_curve(the_shape.get_first());
                  trackMomentum[iParticle].SetXYZ(direction.x(),direction.y(),direction.z());                }
            }
            if (track.has_associated_calorimeter_hits())
            {
              double max_calo_energy=0;
              for (unsigned int hit=0; hit<track.get_associated_calorimeter_hits().size();++hit) {
                // Maybe there are some little hits but there should only be 1 significant one, that is one above the threhold of 50 keV. We only care for the highest-energy
                const snemo::datamodel::calibrated_calorimeter_hit & calo_hit = track.get_associated_calorimeter_hits().at(hit).get();
                if (calo_hit.get_energy() > max_calo_energy)
                {
                  max_calo_energy = calo_hit.get_energy();
                  calorimeterTime[iParticle] += calo_hit.get_time();
                  calorimeterTimeSigma[iParticle] += calo_hit.get_sigma_time();
                  calorimeterEnergy[iParticle] += calo_hit.get_energy();
                  calorimeterEnergySigma[iParticle] += calo_hit.get_sigma_energy();
                }
                if (max_calo_energy>lowEnergyLimit)
                  ++associatedCalorimeters; // So it's only associated if it has one of high enough energy, and that is the one it is associated to
              }
            }
            // Until we have the Particle ID bank, we just have the charge to identify an electron from a positron
            if (track.get_charge()==snemo::datamodel::particle_track::NEGATIVE) ++numberOfElectrons;

            // Check if it has a vertex on the foil
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
            }
          }

        // Two good tracks, get the combined info about the set
	      if (associatedCalorimeters==2)
        {
          double projectedTrackLength[2];
          // Calculate the projected vertex separation
          // Here's how we will do it: for each track, take the vertex nearest the foil
          // project it back onto the foil (x=0) using the direction of the momentum at the first vertex
          // Then calculate the distance between the two projected vertices
          for (int i=0;i<2;i++)
          {
            double scale=vertexPosition[i].X()/trackMomentum[i].X();
            projectedVertexPosition[i]=vertexPosition[i] - scale*trackMomentum[i]; // The second term is the extension to the track to project it back with a straight line
            projectedTrackLength[i]=trackLength[i]+TMath::Abs(scale*(trackMomentum[i]).Mag()); // This gives a longer track as we add the extension
            // Get the larger of the 2 distances in the x-y plane between actual vertex and foil-projected vertex, to tell how much track was missed
            double thisProjectionDistance=(vertexPosition[i]-projectedVertexPosition[i]).Perp();
            if (thisProjectionDistance > projectionDistanceXY)projectionDistanceXY=thisProjectionDistance;
          }
          // Internal and external probabilities
          if (!(calorimeterTime[0]==calorimeterTime[1] && calorimeterEnergy[0] ==  calorimeterEnergy[1] &&  calorimeterEnergySigma[0] ==  calorimeterEnergySigma[1]) && (calorimeterEnergy[0]>lowEnergyLimit &&  calorimeterEnergy[1]>lowEnergyLimit) && (calorimeterEnergy[0]>highEnergyLimit || calorimeterEnergy[1]>highEnergyLimit)) // They are 2 different hits and both over the low energy limit and one of them over the high energy limit... we are good to go, each track has its own legit calorimeter hit.
            passesAssociatedCalorimeters=true;
          // As we have tracks with associated calorimeters, we should have enough information to calculate the internal and external probabilities
          bool okToCalculate=true;
          for (int count=0;count<2;count++)
          { // Check we have good calorimeter and track length info
            if(calorimeterTime[count] == 0
               || calorimeterTimeSigma[count]== 0
               || calorimeterEnergy[count] == 0
               || calorimeterEnergySigma[count] == 0
               || trackLength[count] == 0)
              okToCalculate=false;
          }
          if (okToCalculate)
          {
            CalculateProbabilities(internalProbability, externalProbability,&calorimeterEnergy[0], &calorimeterEnergySigma[0], &trackLength[0], &calorimeterTime[0], &calorimeterTimeSigma[0]);
            // Try again with the track to the foil-projected vertex
            CalculateProbabilities(foilProjectedInternalProbability, foilProjectedExternalProbability,&calorimeterEnergy[0], &calorimeterEnergySigma[0], &projectedTrackLength[0], &calorimeterTime[0], &calorimeterTimeSigma[0]);
          } // if we are OK to calculate
        }
      }
    }
  }
  catch (std::logic_error& e) {
    std::cerr << "failed to grab PTD bank : " << e.what() << std::endl;
    return dpp::base_module::PROCESS_INVALID;
  }

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
    }
  catch (std::logic_error& e) {
    //std::cerr << "failed to grab SD bank : " << e.what() << std::endl;
    //return dpp::base_module::PROCESS_ERROR;
    // This is OK, if it's data there will be no SD bank
  }    
  
  // Cuts pass/fail
  sensitivity_.passes_two_calorimeters_ = passesTwoCalorimeters;
  sensitivity_.passes_two_clusters_ = passesTwoClusters;
  sensitivity_.passes_two_tracks_ = passesTwoTracks;
  sensitivity_.passes_associated_calorimeters_ = passesAssociatedCalorimeters;
  sensitivity_.number_of_electrons_=numberOfElectrons;
  
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
  
  // Vertices
  sensitivity_.vertices_on_foil_=verticesOnFoil;
  sensitivity_.first_vertices_on_foil_=firstVerticesOnFoil;
  sensitivity_.first_vertex_x_= vertexPosition[0].X();
  sensitivity_.first_vertex_y_= vertexPosition[0].Y();
  sensitivity_.first_vertex_z_= vertexPosition[0].Z();
  sensitivity_.second_vertex_x_= vertexPosition[1].X();
  sensitivity_.second_vertex_y_= vertexPosition[1].Y();
  sensitivity_.second_vertex_z_= vertexPosition[1].Z();
  sensitivity_.vertex_separation_= (vertexPosition[0] - vertexPosition[1]).Mag();
  sensitivity_.first_projected_vertex_y_= projectedVertexPosition[0].Y();
  sensitivity_.first_projected_vertex_z_= projectedVertexPosition[0].Z();
  sensitivity_.second_projected_vertex_y_= projectedVertexPosition[1].Y();
  sensitivity_.second_projected_vertex_z_= projectedVertexPosition[1].Z();
  sensitivity_.foil_projection_separation_= (projectedVertexPosition[0] - projectedVertexPosition[1]).Mag();
  sensitivity_.projection_distance_xy_=projectionDistanceXY;
  
  // Track direction
  sensitivity_.first_track_momentum_x_= trackMomentum[0].X();
  sensitivity_.first_track_momentum_y_= trackMomentum[0].Y();
  sensitivity_.first_track_momentum_z_= trackMomentum[0].Z();
  sensitivity_.second_track_momentum_x_= trackMomentum[1].X();
  sensitivity_.second_track_momentum_y_= trackMomentum[1].Y();
  sensitivity_.second_track_momentum_z_= trackMomentum[1].Z();
  sensitivity_.same_side_of_foil_= ((trackMomentum[0].X() * trackMomentum[1].X()) > 0); // X components both positive or both negative
  sensitivity_.angle_between_tracks_= trackMomentum[0].Angle(trackMomentum[1]);
  
  // Timing
  sensitivity_.time_delay_=TMath::Abs(timeDelay);
  sensitivity_.internal_probability_=internalProbability;
  sensitivity_.internal_chi_squared_=internalChiSquared;
  sensitivity_.external_chi_squared_=externalChiSquared;
  sensitivity_.external_probability_=externalProbability;
  sensitivity_.foil_projected_internal_probability_=foilProjectedInternalProbability;
  sensitivity_.foil_projected_external_probability_=foilProjectedExternalProbability;
  
  // Debug information
  sensitivity_.calorimeter_hit_count_=caloHitCount;
  sensitivity_.small_cluster_count_=smallClusterCount;
  sensitivity_.cluster_count_=clusterCount;
  sensitivity_.third_calo_energy_=thirdCaloEnergy;
  sensitivity_.edgemost_vertex_=edgemostVertex;
   
  tree_->Fill();
  truth_.lower_electron_energy_=lowerTrueEnergy;
  truth_.higher_electron_energy_=higherTrueEnergy;
  truthtree_->Fill();
  // MUST return a status, see ref dpp::processing_status_flags_type
  return dpp::base_module::PROCESS_OK;
}


void SensitivityModule::CalculateProbabilities(double &internalProbability, double &externalProbability, double *calorimeterEnergies, double *calorimeterEnergySigmas, double *trackLengths, double *calorimeterTimes, double *calorimeterTimeSigmas)
{
  double beta[2]; // Speed in units of light speed
  double theoreticalTimeOfFlight[2];
  double internalEmissionTime[2];
  double internalVariance[2];
  double internalChiSquared;
  double externalChiSquared;
  for (int count=0;count<2;count++)
  {
    //energies are in MeV
    beta[count] = TMath::Sqrt(calorimeterEnergies[count] * (calorimeterEnergies[count] + 2 * electronMass)) / (calorimeterEnergies[count] +  electronMass);
    theoreticalTimeOfFlight[count] = trackLengths[count]/ (beta[count] * speedOfLight);
    internalEmissionTime[count] = calorimeterTimes[count] - theoreticalTimeOfFlight[count];
    internalVariance[count] =
    pow(calorimeterTimeSigmas[count],2)
    + pow(calorimeterEnergySigmas[count],2)
    * pow((theoreticalTimeOfFlight[count]*electronMass*electronMass),2)
    / pow( (calorimeterEnergies[count] * (calorimeterEnergies[count]+electronMass) * (calorimeterEnergies[count]+ 2 * electronMass) ),2);
  } // for each particle
  
  // Calculate internal probability
  internalChiSquared = pow((internalEmissionTime[0] - internalEmissionTime[1]) ,2) / (internalVariance[0] + internalVariance[1]) ;
  double integralForProbability=0;
  internalProbability=this->ProbabilityFromChiSquared(internalChiSquared);
  
  // Calculate external probability
  externalChiSquared=pow(( TMath::Abs(calorimeterTimes[0]-calorimeterTimes[1]) - (theoreticalTimeOfFlight[0]+theoreticalTimeOfFlight[1]) ),2)/(internalVariance[0] + internalVariance[1]) ;
  externalProbability=this->ProbabilityFromChiSquared(externalChiSquared);
} // if we are OK to calculate

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
