//
//  Se2b2nCuts.cpp
//
//  Created by James Mott on 16/10/12
//  

// Module declaration
#include "JEM_Analysis/Se2b2nCuts.h"

// Data Structures
#include "NemoObjects/ElectronColl.h"
#include "NemoObjects/AlphaColl.h"
#include "NemoObjects/GammaClusterColl.h"
#include "NemoObjects/N3TrackSegmentColl.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/N3GeigerHitColl.h"

// Nemo Modules
#include "NemoMods/RunStatusController.h"
#include "NemoUtils/ScintillatorBlocksMapping.h"

// Hereward modules
#include "Hereward/SuperNemoData/TrueVertexColl.h"
#include "Hereward/SuperNemoData/TrueParticleColl.h"
#include "Hereward/SuperNemoData/EventHeader.h"
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"

// STL
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iomanip>

// ROOT
#include "TFile.h"
#include "TMath.h"

//------------------------------------------------------------
// Constructor and Destructor
//------------------------------------------------------------
Se2b2nCuts::Se2b2nCuts(const std::string theName,
                               const std::string theDescription) :
AppModule(theName, theDescription) {
  execType_ = App_module;
  sectorInfo_ = new SectorData();
  cosCorrection_ = new AngularCorrection();
  radonweighter_ = new RadonWeight();
  HotSpotChecker_ = new HotSpots();
  SFoilSide_ = new SFoilSide();
}

Se2b2nCuts::~Se2b2nCuts() {
  delete sectorInfo_;
  delete cosCorrection_;
  delete radonweighter_;
  delete HotSpotChecker_;
  delete SFoilSide_;
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult Se2b2nCuts::beginJob(AppEvent* aJob) {

  RootOutputManager* nTupleManager = RootOutputManager::instance();

  // Create branches for storing data for accepted events
  nTupleManager->addTree(name());
  nTupleManager->addBranch(name(), "b_run", &run_, "run/I");    
  nTupleManager->addBranch(name(), "b_event", &event_, "event/I");    
  nTupleManager->addBranch(name(), "b_energy", &energy_, "energy[2]/D");
  nTupleManager->addBranch(name(), "b_trackLength", &trackLength_, "trackLength[2]/D");
  nTupleManager->addBranch(name(), "b_trackSign", &trackSign_, "trackSign[2]/D");
  nTupleManager->addBranch(name(), "b_nNACaloHits", &nNACaloHits_, "nNACaloHits/I");
  nTupleManager->addBranch(name(), "b_gammaEnergy", &gammaEnergy_, "gammaEnergy[nNACaloHits]/D");
  nTupleManager->addBranch(name(), "b_nClusters", &nClusters_, "nClusters/I");
  nTupleManager->addBranch(name(), "b_clusterEnergy", &clusterEnergy_, "clusterEnergy[nClusters]/D");
  nTupleManager->addBranch(name(), "b_totGammaEnergy", &totGammaEnergy_, "totGammaEnergy/D");
  nTupleManager->addBranch(name(), "b_probInt", &probInt_, "probInt/D");
  nTupleManager->addBranch(name(), "b_probExt", &probExt_, "probExt/D");
  nTupleManager->addBranch(name(), "b_cosTheta", &cosTheta_, "cosTheta/D");
  nTupleManager->addBranch(name(), "b_cosThetaWeight", &cosThetaWeight_, "cosThetaWeight/D");
  nTupleManager->addBranch(name(), "b_vertexR", &vertexR_, "vertexR/D");
  nTupleManager->addBranch(name(), "b_vertexZ", &vertexZ_, "vertexZ/D");
  nTupleManager->addBranch(name(), "b_vertexSector", &vertexSector_, "vertexSector/D");
  nTupleManager->addBranch(name(), "b_vertexDXY", &vertexDXY_, "vertexDXY/D");
  nTupleManager->addBranch(name(), "b_vertexDZ", &vertexDZ_, "vertexDZ/D");
  nTupleManager->addBranch(name(), "b_vertexLocation", &vertexLocation_, "vertexLocation/I");
  nTupleManager->addBranch(name(), "b_radonWeight", &radonWeight_, "radonWeight/D");
  nTupleManager->addBranch(name(), "b_bi210Weight", &bi210Weight_, "bi210Weight/D");
  nTupleManager->addBranch(name(), "b_foilSide", &foilSide_, "foilSide/I");
  nTupleManager->addBranch(name(), "b_goodRun", &goodRun_, "goodRun/O");
  nTupleManager->addBranch(name(), "b_scintLocation", &scintLocation_, "scintLocation[2]/I");
  nTupleManager->addBranch(name(), "b_firstGgHitLayer", &firstGgHitLayer_, "firstGgHitLayer[2]/I");
  nTupleManager->addBranch(name(), "b_lastGgHitLayer", &lastGgHitLayer_, "lastGgHitLayer[2]/I");
  nTupleManager->addBranch(name(), "b_eventTime", &eventTime_, "eventTime/D");
  nTupleManager->addBranch(name(), "b_trueVertexR", &trueVertexR_, "trueVertexR/D");
  nTupleManager->addBranch(name(), "b_trueVertexZ", &trueVertexZ_, "trueVertexZ/D");
  nTupleManager->addBranch(name(), "b_trueVertexSector", &trueVertexSector_, "trueVertexSector/D");
  nTupleManager->addBranch(name(), "b_iobt", &iobt_, "iobt[2]/I");

  // Initialise counters that will keep track of number of events that pass each cut
  TotalNumEvents_    = 0; 
  GoodorStandardRun_ = 0; 
  TwoTracks_         = 0;
  AssociatedTracks_  = 0;
  DifferentScints_   = 0;
  IsolatedCalos_     = 0;
  FrontofBlock_      = 0;
  NoClosePetals_     = 0;
  ElectronGoodPMT_   = 0;
  ElectronLD_        = 0;
  ElectronLDCorr_    = 0;
  ElectronLDCorrErr_ = 0;
  ElectronHS_        = 0;
  GammasGoodPMT_     = 0;
  GammasLD_          = 0;
  GammasLDCorr_      = 0;
  GammasLDCorrErr_   = 0;
  GammasHS_          = 0;
  EachScint300keV_   = 0;
  GammaEnergy_       = 0;
  TwoIntersectFoil_  = 0;
  SeleniumAngle_     = 0;
  ZinFoil_           = 0;
  ZNotZero_          = 0;
  NotInHotSpot_      = 0;
  dXYLessThan2_      = 0;
  dZLessThan4_       = 0;
  TrackLengthMin20cm_= 0;
  TrackLengthMax50cm_= 0;
  TrackLengthSum80cm_= 0;
  TracksFirstLayer_  = 0;
  TracksLastLayer_   = 0;
  NegativeTracks_    = 0;
  OneNACloseHit_     = 0;
  SameSideNAHits_    = 0;
  SameSideNAFarHits_ = 0;
  SameSideLayer0_    = 0;
  NoAlphaCandidates_ = 0;
  IntProb4Percent_   = 0;
  ExtProb1Percent_   = 0;

  dataFlag = false;

  return AppResult::OK;    
}

AppResult Se2b2nCuts::beginRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult Se2b2nCuts::event(AppEvent* anEvent) {

  // Get all the data from the event and put it in appropriate collections
   
  // 1) Get EventHeader
  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator runRecord(anEvent, cName);    
  EventHeader_ch eventHeader(runRecord);
  if (!runRecord.is_valid()) {
    std::cout << "-- Se2b2nCuts - Error Accessing the RunHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 

  // 2) Get Electron collection
  ElectronColl_ch theElectronColl;
  ElectronColl::ElectronList electronList;
  if (ElectronColl::find(anEvent, theElectronColl)) {        
    electronList = theElectronColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - Electrons not found" << std::endl;
    return AppResult::OK;
  }

  // 3) Get Alpha collection
  AlphaColl_ch theAlphaColl;
  AlphaColl::AlphaList alphaList;
  if (AlphaColl::find(anEvent, theAlphaColl)) {        
    alphaList = theAlphaColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - Alphas not found" << std::endl;
    return AppResult::OK;
  }

  // 4) Get GammaCluster collection
  GammaClusterColl_ch theGammaClusterColl;
  GammaClusterColl::ClusterList gammaClusterList;
  if (GammaClusterColl::find(anEvent, theGammaClusterColl)) {        
    gammaClusterList = theGammaClusterColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - Gamma Clusters not found" << std::endl;
    return AppResult::OK;
  }

  // 5) Get Local Track collection
  N3TrackSegmentColl_ch theTrackColl;
  N3TrackSegmentColl::N3TrackSegmentList trackList;
  if (N3TrackSegmentColl::find(anEvent, theTrackColl)) {        
    trackList = theTrackColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - Tracks not found" << std::endl;
    return AppResult::OK;        
  }
        
  // 6) Get Calibrated Calorimeter hit collection
  CalibCaloHitColl_ch theCaloHitColl;
  CalibCaloHitColl::CalibCaloHitList caloHitList;
  if (CalibCaloHitColl::find(anEvent, theCaloHitColl)) {
    caloHitList = theCaloHitColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - Calibrated calorimeter hits not found" << std::endl;
    return AppResult::OK;
  }

  // 7) Get Raw Calorimeter hit collection
  N3CalorimeterHitColl_ch theRawCaloHitColl;
  N3CalorimeterHitColl::N3CalorimeterHitList rawCaloHitList;
  if (N3CalorimeterHitColl::find(anEvent, theRawCaloHitColl)) {
    rawCaloHitList = theRawCaloHitColl->contents();
  } else {
    std::cout  << "-- Se2b2nCuts - Raw Calorimeter hits not found"  << std::endl;
    return AppResult::OK;
  }

  // 8) Get Raw Geiger hit collection
  N3GeigerHitColl_ch theRawGgHitColl;
  N3GeigerHitColl::N3GeigerHitList rawGgHitList;
  if (N3GeigerHitColl::find(anEvent, theRawGgHitColl)){
    rawGgHitList = theRawGgHitColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - Raw Geiger hits not found" << std::endl;
    return AppResult::OK;
  }

  // 9) Get true vertex collection
  TrueVertexColl_ch theTrueVertexColl;
  TrueVertexColl::TrueVertexList trueVertexList;
  if (TrueVertexColl::find(anEvent, theTrueVertexColl)){
    trueVertexList = theTrueVertexColl->contents();
  } else {
    std::cout << "-- Se2b2nCuts - True Vertex info not found" << std::endl;
    return AppResult::OK;
  }

  // ================================================================================================
  // GENERAL CUTS - TWO TRACKS AND TWO GOOD QUALITY HITS
  // ================================================================================================

  // Output counter to screen to keep tabs on how far program's got
  if(TotalNumEvents_ % 50000 == 0){std::cout << "Processing event " << TotalNumEvents_ << std::endl;}

  // Get Event and Run Numbers
  run_            = eventHeader->runNumber();
  event_          = eventHeader->eventNumber();
  TotalNumEvents_++;
  if(!eventHeader->mcFlag()){ dataFlag = true; }

  // Make sure event is in good or standard run.
  if (!RunStatusController::instance()->currentRunIsAccepted()) {
    return AppResult::OK;
  }
  GoodorStandardRun_++;

  // Assign flag for good run in case we change run list
  goodRun_ = true;
  if (RunStatusController::instance()->runStatus() != 1) {goodRun_ = false;}

  // Cut events without exactly two tracks
  if (trackList.size() != 2){return AppResult::OK;}
  TwoTracks_++;

  // Cut events where the tracks aren't both reconstructed from the foil
  bool trackIntersectFoil[2];
  for(int i = 0; i < 2; i++){ 
    trackIntersectFoil[i] = (trackList.at(i).intersectionOnFoil().mag2() > 1e-4) or (trackList.at(i).intersectionOnFoil(true).mag2() > 1e-4);
  }
  if(!trackIntersectFoil[0] or !trackIntersectFoil[1]) return AppResult::OK;
  TwoIntersectFoil_++;

  // Define vertex as midpoint of two intersections
  CLHEP::Hep3Vector trackVertex[2];
  for(int i = 0; i < 2; i++){ 
    if(trackList.at(i).intersectionOnFoil(true).mag2() > 1e-4) trackVertex[i] = trackList.at(i).intersectionOnFoil(true);
    else                                                       trackVertex[i] = trackList.at(i).intersectionOnFoil();
  }    
  CLHEP::Hep3Vector vertex  = (trackVertex[0] + trackVertex[1]) / 2.0;

  // Cut events if they're not in selenium part of source foil
  SourceType source = sectorInfo_->sourceOfVertex(vertex);
  if (source != SourceType::SeOld && source != SourceType::SeNew){return AppResult::OK;}
  SeleniumAngle_++;

  // Cut unassociated tracks or ones that are associated to noisy scintillators
  if(trackList.at(0).indexOfScintillator() < 0 || 
     rawCaloHitList.at(trackList.at(0).indexOfScintillator()).isNoisy() || 
     trackList.at(1).indexOfScintillator() < 0 || 
     rawCaloHitList.at(trackList.at(1).indexOfScintillator()).isNoisy()){
    return AppResult::OK;
  }
  AssociatedTracks_++;

  // Get hold of electrons and tracks and put them in arrays to use later
  Electron electrons[2];
  N3TrackSegment eTracks[2];
  if (electronList.at(0).trackId() == 0) {
    electrons[0] = electronList.at(0);
    electrons[1] = electronList.at(1);
  } else {
    electrons[1] = electronList.at(0);
    electrons[0] = electronList.at(1);
  }
  eTracks[0] = trackList[electrons[0].trackId()];
  eTracks[1] = trackList[electrons[1].trackId()];

  // Cut events with same scintillator hits
  if (electrons[0].hitId() == electrons[1].hitId()){return AppResult::OK;}
  DifferentScints_++;

  // Cut events where the calorimeter hits are not isolated and close scints aren't noisy
  int caloHitIds[2];
  caloHitIds[0] = electrons[0].hitId();
  caloHitIds[1] = electrons[1].hitId();

  int rawCaloHitIds[2];
  rawCaloHitIds[0] = caloHitList.at(electrons[0].hitId()).hitId();
  rawCaloHitIds[1] = caloHitList.at(electrons[1].hitId()).hitId();

  for(int j = 0; j < rawCaloHitList.size(); j++){
    if(j != rawCaloHitIds[0]){
      int comparison = rawCaloHitList.at(rawCaloHitIds[0]).checkNeighbour(rawCaloHitList.at(j));
      if (comparison != 0  && !rawCaloHitList.at(j).isNoisy()){return AppResult::OK;}
    }
    if(j != rawCaloHitIds[1]){
      int comparison = rawCaloHitList.at(rawCaloHitIds[1]).checkNeighbour(rawCaloHitList.at(j));
      if (comparison != 0 && !rawCaloHitList.at(j).isNoisy()){return AppResult::OK;}
    }
  }
  IsolatedCalos_++;

  // Get hold of energy of each electron and store
  energy_[0] = electrons[0].energy();
  energy_[1] = electrons[1].energy();

  // Cut events where energy of either scintillator is less than 300 keV
  if (energy_[0] <= 0.3 or energy_[1] <= 0.3){return AppResult::OK;}
  EachScint300keV_++;

  // ================================================================================================
  // PROBABILITY CUTS - INTERNAL > 0.01; EXTERNAL < 0.01
  // ================================================================================================

  // Internal Probability
  double numerInt = pow( (electrons[0].measTime() - electrons[1].measTime()) - (electrons[0].thTof() - electrons[1].thTof()) , 2);
  double denomInt = pow(electrons[0].dMeasTime(),2) + pow(electrons[0].dThTof(),2) + pow(electrons[1].dMeasTime(),2) + pow(electrons[1].dThTof(),2);
  double chiSqInt = numerInt / denomInt;
  probInt_ = TMath::Prob(chiSqInt, 1);

  // External Probability

  // 1st Hypothesis - assume that electrons[0] hits first and then crosses depositing energy given in electrons[1]
  double TofExt0    = (electrons[0].pathLength()+electrons[1].pathLength())/(electrons[1].beta()*physics::c/10);  
  double TofExt0Err = (TofExt0 / electrons[1].beta())*electrons[1].dBeta();

  // 2nd Hypothesis - assume that electrons[1] is the crossing electron this time
  double TofExt1    = (electrons[0].pathLength()+electrons[1].pathLength())/(electrons[0].beta()*physics::c/10);  
  double TofExt1Err = (TofExt1 / electrons[0].beta())*electrons[0].dBeta();

  // Calculate Chi-Squared & external probability for each hypothesis 
  double numerExt0 = pow( electrons[1].measTime() - electrons[0].measTime() - TofExt0 , 2);
  double denomExt0 = pow(electrons[0].dMeasTime(), 2) + pow(electrons[1].dMeasTime(), 2) + pow(TofExt0Err, 2);
  double chiSqExt0 = numerExt0 / denomExt0;
  double probExt0  = TMath::Prob(chiSqExt0,1);

  double numerExt1 = pow( electrons[0].measTime() - electrons[1].measTime() - TofExt1 , 2);
  double denomExt1 = pow(electrons[0].dMeasTime(), 2) + pow(electrons[1].dMeasTime(), 2) + pow(TofExt1Err, 2);
  double chiSqExt1 = numerExt1 / denomExt1;
  double probExt1  = TMath::Prob(chiSqExt1,1);

  // Take largest of two probabilities as the external probability
  double chiSqExt;
  if(probExt0 > probExt1){probExt_ = probExt0;}
  else {probExt_ = probExt1;}

  // Cut events with internal probability less than 0.04
  if(probInt_ < 0.04){return AppResult::OK;}
  IntProb4Percent_++;

  // Cut events with external probability greater than 0.01
  if(probExt_ > 0.1){return AppResult::OK;}
  ExtProb1Percent_++;

  // ================================================================================================
  // ELECTRON QUALITY CUTS
  // ================================================================================================

  // Cut events where the impact region is on the side of the blocks
  if (electrons[0].impactRegion() == 66 or electrons[1].impactRegion() == 66) {return AppResult::OK;}
  FrontofBlock_++;

  // Cut events where an electron hits one of inner layers of petals
  if(rawCaloHitList.at(rawCaloHitIds[0]).iobtFlag() > 1){
    if(rawCaloHitList.at(rawCaloHitIds[0]).fcll() == 1 || rawCaloHitList.at(rawCaloHitIds[0]).fcll() == 2){
      return AppResult::OK;
    } 
  }
  if(rawCaloHitList.at(rawCaloHitIds[1]).iobtFlag() > 1){
    if(rawCaloHitList.at(rawCaloHitIds[1]).fcll() == 1 || rawCaloHitList.at(rawCaloHitIds[1]).fcll() == 2){
      return AppResult::OK;
    } 
  }
  NoClosePetals_++;

  // Good PMT Status
  if ( ! caloHitList.at(caloHitIds[0]).goodFlag() or ! caloHitList.at(caloHitIds[1]).goodFlag()) {return AppResult::OK;}
  ElectronGoodPMT_++;
  
  // LD Flag == 0
  if ( caloHitList.at(caloHitIds[0]).ldFlag() > 0 or caloHitList.at(caloHitIds[1]).ldFlag() > 0) {return AppResult::OK;}
  ElectronLD_++;

  // LD Correction != 0  
  if ( caloHitList.at(caloHitIds[0]).ldCorr() == 0 or caloHitList.at(caloHitIds[1]).ldCorr() == 0){return AppResult::OK;}
  ElectronLDCorr_++;

  // LD Correction Err != 0  
  if ( caloHitList.at(caloHitIds[0]).ldCorrErr() == 0 or caloHitList.at(caloHitIds[1]).ldCorrErr() == 0){return AppResult::OK;}
  ElectronLDCorrErr_++;

  // HS Flag == 0  
  if ( caloHitList.at(caloHitIds[0]).hsFlag() > 0 or caloHitList.at(caloHitIds[1]).hsFlag() > 0 ){return AppResult::OK;}
  ElectronHS_++;

  // ================================================================================================
  // GAMMA QUALITY CUTS
  // ================================================================================================

  // Good PMT Status
  for(int i = 0; i < gammaClusterList.size(); i++){
    if ( ! gammaClusterList.at(i).goodPMTStatuses() ){return AppResult::OK;}
  }
  GammasGoodPMT_++;

  // LD Flag == 0
  for(int i = 0; i < gammaClusterList.size(); i++){
    if ( !gammaClusterList.at(i).goodLDFlags() ) {return AppResult::OK;}
  }
  GammasLD_++;

  // LD Correction !=0
  for(int i = 0; i < gammaClusterList.size(); i++){
    if ( !gammaClusterList.at(i).hasLDCorrs() ) {return AppResult::OK;}
  }
  GammasLDCorr_++;

  // LD Correction Error != 0
  for(int i = 0; i < gammaClusterList.size(); i++){
    if ( !gammaClusterList.at(i).hasLDCorrErrs() ) {return AppResult::OK;}
  }
  GammasLDCorrErr_++;

  // HS Flag != 0 and if single hit HS != 10
  for(int i = 0; i < gammaClusterList.size(); i++){    
    if( !gammaClusterList.at(i).goodHSFlags() ) {return AppResult::OK;}
  }
  GammasHS_++;

  // ================================================================================================
  // ENERGY CUTS - 300 keV EACH AND GAMMAS LESS THAN 250 keV
  // ================================================================================================

  // Cut events with an unassociated PMT > 200 keV
  nClusters_ = gammaClusterList.size();
  nNACaloHits_ = 0;
  double gammaEnergy = 0;
  for(int i = 0; i < gammaClusterList.size(); i++){
    gammaEnergy += gammaClusterList.at(i).energy();
    clusterEnergy_[i] = gammaClusterList.at(i).energy();
    for(int j = 0; j < gammaClusterList.at(i).cluster().size(); j++){
      gammaEnergy_[nNACaloHits_] = gammaClusterList.at(i).cluster().at(j).energy();
      nNACaloHits_++;
    }
  }
  totGammaEnergy_ = gammaEnergy;
  for(int i = 0; i < nNACaloHits_; i++){
    if(gammaEnergy_[i] > 0.2){return AppResult::OK;}
  }
  GammaEnergy_++;

  // ================================================================================================
  // VERTEX CUTS
  // ================================================================================================

  // Vertex Location (0 - SeOld, 1 - SeNew, 2 - SeNewStrip)
  vertexLocation_ = -1;
  if (source == SourceType::SeOld){vertexLocation_ = 0;}
  else if (source == SourceType::SeNew){
    if(sectorInfo_->sectorNumber(vertex) <= 8.0){ vertexLocation_ = 1;}
    else{vertexLocation_ = 2;}
  }

  // Cut events where the averaged Z of vertex isn't in the foil (+/- 120cm)
  if(fabs(vertex.z()) > 120){return AppResult::OK;}
  ZinFoil_++;

  // Cut events where the vertex Z is 0
  if(vertex.z() == 0){return AppResult::OK;}
  ZNotZero_++;

  // Cut events if it comes from a hotspot as found in the hotspot search.
  if(HotSpotChecker_->InHotSpot(vertex)){return AppResult::OK;}
  NotInHotSpot_++;

  // Cut events where the difference in vertices is greater than 2cm in the XY-plane
  CLHEP::Hep3Vector vertex0 = trackList.at(0).intersectionOnFoil();
  CLHEP::Hep3Vector vertex1 = trackList.at(1).intersectionOnFoil();
  double d_XY = sqrt( pow(vertex0.x() - vertex1.x(), 2) + pow(vertex0.y() - vertex1.y(), 2)); 
  if(d_XY > 10){return AppResult::OK;}
  dXYLessThan2_++;

  // Cut events where the difference in vertices is greater than 4cm in the Z-plane
  double d_Z = fabs(vertex0.z() - vertex1.z());
  if(d_Z > 10){return AppResult::OK;}
  dZLessThan4_++;

  // Get vertex info and store
  vertexR_ = TMath::Sqrt(vertex.x()*vertex.x() +  vertex.y()*vertex.y()); 
  vertexZ_ = vertex.z();
  vertexSector_ = sectorInfo_->sectorNumber(vertex); 
  vertexDXY_ = d_XY;
  vertexDZ_ = d_Z;

  // Store true vertex information
  if(eventHeader->mcFlag()){
    CLHEP::Hep3Vector trueVertex = trueVertexList.at(0).position();
    trueVertexR_ = TMath::Sqrt(trueVertex.x()*trueVertex.x() +  trueVertex.y()*trueVertex.y()); 
    trueVertexZ_ = trueVertex.z();
    trueVertexSector_ = sectorInfo_->sectorNumber(trueVertex); 
  } else {
    trueVertexR_ = 0;
    trueVertexZ_ = 0;
    trueVertexSector_ = -1;
  }

  // ================================================================================================
  // TRACKING CUTS - HITS IN FIRST & LAST TWO LAYERS, GOOD LENGTHS
  // ================================================================================================

  // Get hold of track length of each electron and store
  trackLength_[0]  = electrons[0].pathLength();
  trackLength_[1]  = electrons[1].pathLength();

  // Cut events where shortest track is less than 20 cm
  if (trackLength_[0] < trackLength_[1]){
    if(trackLength_[0] <= 20) return AppResult::OK;
  } else {
    if(trackLength_[1] <= 20) return AppResult::OK;
  }
  TrackLengthMin20cm_++;

  // Cut events where longest track is less than 50 cm
  if (trackLength_[0] > trackLength_[1]){
    if(trackLength_[0] <= 50) return AppResult::OK;
  } else {
    if(trackLength_[1] <= 50) return AppResult::OK;
  }
  TrackLengthMax50cm_++;

  // Cut events where sum of tracklengths is less than 80 cm
  if (trackLength_[0] + trackLength_[1] <= 80) {return AppResult::OK;}
  TrackLengthSum80cm_++;

  // Cut events where tracks don't start in layer 0 or layer 1
  int firstGgHit0 = electrons[0].firstGeigerHit();
  int firstGgHit1 = electrons[1].firstGeigerHit();
  firstGgHitLayer_[0] = rawGgHitList.at(firstGgHit0).layer();
  firstGgHitLayer_[1] = rawGgHitList.at(firstGgHit1).layer();
  if(firstGgHitLayer_[0] > 1 or firstGgHitLayer_[1] > 1){return AppResult::OK;}
  TracksFirstLayer_++;

  // Work out how many Gg layers track has missed before scintillator

  // Scintillator locations (In/Out/Petals & petal layer(1-4) from inner to outer).
  for(int i = 0; i < 2; i++){
    scintLocation_[i] = -1;
    if(rawCaloHitList.at(rawCaloHitIds[i]).iobtFlag() == 0){scintLocation_[i] = 0;}
    else if(rawCaloHitList.at(rawCaloHitIds[i]).iobtFlag() == 1){scintLocation_[i] = 1;}
    else if(rawCaloHitList.at(rawCaloHitIds[i]).iobtFlag() == 2){
      scintLocation_[i] = (rawCaloHitList.at(rawCaloHitIds[i]).fcll()+1)*10 + 2;
    }
    else if(rawCaloHitList.at(rawCaloHitIds[i]).iobtFlag() == 3){
      scintLocation_[i] = (rawCaloHitList.at(rawCaloHitIds[i]).fcll()+1)*10 + 3;
    }
    iobt_[i] = rawCaloHitList.at(rawCaloHitIds[i]).iobtFlag();
  }

  // Get last Gg layer
  int lastGgHit0 = eTracks[0].geigerHitList()->at(eTracks[0].geigerHitList()->size()-1);
  int lastGgHit1 = eTracks[1].geigerHitList()->at(eTracks[1].geigerHitList()->size()-1);
  lastGgHitLayer_[0] = rawGgHitList.at(lastGgHit0).layer();
  lastGgHitLayer_[1] = rawGgHitList.at(lastGgHit1).layer();

  // Then how many layers it's missed
  Int_t Scint_Last_Gg_Dist[2];
  for(int i = 0; i < 2; i++){
    if(scintLocation_[i] == 0 or scintLocation_[i] == 1)   Scint_Last_Gg_Dist[i] = 8 - lastGgHitLayer_[i];
    if(scintLocation_[i] == 12 or scintLocation_[i] == 13) Scint_Last_Gg_Dist[i] = 5 - lastGgHitLayer_[i];
    if(scintLocation_[i] == 22 or scintLocation_[i] == 23) Scint_Last_Gg_Dist[i] = 3 - lastGgHitLayer_[i];
    if(scintLocation_[i] == 32 or scintLocation_[i] == 33) Scint_Last_Gg_Dist[i] = 3 - lastGgHitLayer_[i];
    if(scintLocation_[i] == 42 or scintLocation_[i] == 43) Scint_Last_Gg_Dist[i] = 5 - lastGgHitLayer_[i];
  }

  // Cut if it's missed more than 1 Gg layer
  if(Scint_Last_Gg_Dist[0] > 1 or Scint_Last_Gg_Dist[1] > 1){return AppResult::OK;}
  TracksLastLayer_++;

  // Store sign of tracks in case we want to cut on this at analysis level
  trackSign_[0] = eTracks[0].sign();
  trackSign_[1] = eTracks[1].sign();

  // Cut events with positive tracks
  if(trackSign_[0] > 0 || trackSign_[1] > 0){return AppResult::OK;}
  NegativeTracks_++;

  // ================================================================================================
  // NA PROMPT HIT CUTS
  // ================================================================================================

  // Make vector containing all the rawGgHistList IDs of prompt unassociated hits
  std::vector<int> NAPromptHits;
  for(int i = 0; i < rawGgHitList.size(); i++){
    bool used = false;
    for(int j = 0; j < eTracks[0].geigerHitList()->size(); j++){
      if(eTracks[0].geigerHitList()->at(j) == i){
	used = true;
	break;
      }
    }
    if(used == true){continue;}
    for(int j = 0; j < eTracks[1].geigerHitList()->size(); j++){
      if(eTracks[1].geigerHitList()->at(j) == i){
	used = true;
	break;
      }
    }
    if(used == true){continue;}
    else{ 
      if(rawGgHitList.at(i).isPrompt()){NAPromptHits.push_back(i);}
    }
  }

  // Calculate distance of NA prompt hits from event vertex in XY-plane and assign close/far at 15cm
  int nCloseNAPromptHits = 0;
  int nFarNAPromptHits = 0;
  for(int i = 0; i < NAPromptHits.size(); i++){
    double anodeX = rawGgHitList.at(NAPromptHits.at(i)).anodePosition().x();
    double anodeY = rawGgHitList.at(NAPromptHits.at(i)).anodePosition().y();
    double dist = sqrt( pow(vertex.x() - anodeX, 2) + pow(vertex.y() - anodeY, 2));
    if(dist < 15){nCloseNAPromptHits++;}
    else{nFarNAPromptHits++;}
  }

  // Cut events where there are more than 1 prompt unassociated hits within 15cm of vertex in XY plane.
  if(nCloseNAPromptHits > 1){return AppResult::OK;}
  OneNACloseHit_++;

  // If tracks are on the same side then demand no unassociated hits within 15cm
  if(rawGgHitList.at(firstGgHit0).side() == rawGgHitList.at(firstGgHit1).side()){
    if(nCloseNAPromptHits > 0){return AppResult::OK;}
  }
  SameSideNAHits_++;

  // If tracks are on the same side then demand less than 3 unassociated hits anywhere
  if(rawGgHitList.at(firstGgHit0).side() == rawGgHitList.at(firstGgHit1).side()){
    if(nFarNAPromptHits > 2){return AppResult::OK;}
  }
  SameSideNAFarHits_++;

  // "Victor's Cut": if tracks are on same side, cut events where 1st hits are both in layer 1
  if(rawGgHitList.at(firstGgHit0).side() == rawGgHitList.at(firstGgHit1).side()){
    if(rawGgHitList.at(firstGgHit0).layer() == 1 and rawGgHitList.at(firstGgHit1).layer() == 1){
      return AppResult::OK;
    }
  }
  SameSideLayer0_++;

  // ================================================================================================
  // CUT ON ALPHA CANDIDATES
  // ================================================================================================
  
  // No alpha candidates
  if(alphaList.size() > 0){return AppResult::OK;}
  NoAlphaCandidates_++;

  // ================================================================================================
  // FINALLY USE NEMOUTILS TO GET ANGULAR CORRECTION & RADON MAP WEIGHTS, THEN SAVE ROOT FILE
  // ================================================================================================

  // Calculate cosine between two electrons & get reweighting factor
  CLHEP::Hep3Vector dirCosines[2];
  dirCosines[0] = eTracks[0].directionCosine();
  dirCosines[1] = eTracks[1].directionCosine();
  cosTheta_ = dirCosines[0].cosTheta(dirCosines[1]);
  cosThetaWeight_ = cosCorrection_->CosWeight(cosTheta_);

  // Get radon and bi210 weighting factor for samples on wires
  if(eventHeader->mcFlag()){
    radonWeight_ = radonweighter_->getRadonWeight(trueVertexList.at(0).position());
    bi210Weight_ = radonweighter_->getBi210Weight(trueVertexList.at(0).position());
    foilSide_    = SFoilSide_->getSFoilSide(trueVertexList.at(0).position());
  } else {
    radonWeight_ = 0;
    bi210Weight_ = 0;
    foilSide_    = -1;
  }

  // Find time of middle of run since date of run 1869 (15th Feb 2003) - used to weight decaying isotopes
  TTimeStamp startTime(2003,02,15,00,00,00);
  TTimeStamp runStartTime = RunStatusController::instance()->runStart();
  eventTime_ = runStartTime.GetSec() + (RunStatusController::instance()->runLength())/2. - startTime.GetSec();

  // Save everything in branch and close App
  RootOutputManager::instance()->capture(name());

  return AppResult::OK;
}


AppResult Se2b2nCuts::endRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult Se2b2nCuts::endJob(AppEvent* aJob) {

  long totalRunTime_       = RunStatusController::instance()->totalRunTime();
  long totalAccRunTime_    = RunStatusController::instance()->totalAccRunTime();
  long totalTriggered_     = RunStatusController::instance()->totalAssignedEvents();
  long totalAccTriggered_  = RunStatusController::instance()->totalAccAssignedEvents();
  double totalDeadTime_    = RunStatusController::instance()->totalDeadTime();
  double totalAccDeadTime_ = RunStatusController::instance()->totalAccDeadTime();

  long TotMCEvents = RunStatusController::instance()->maxGeneratedEvents();
  // Round TotMCEvents to nearest 1000 so it usually gets it right
  TotMCEvents = (long)(1000.0*floor(((double)TotMCEvents)/1000.0+0.5));

  long AccMCEvents_ = (long)floor(TotMCEvents*(((double)totalAccTriggered_)/totalTriggered_) + 0.5);

  int totalAccRunTimeP1     = RunStatusController::instance()->totalAccRunTime("P1");
  int totalAccRunTimeP2     = RunStatusController::instance()->totalAccRunTime("P2");
  double totalAccDeadTimeP1 = RunStatusController::instance()->totalAccDeadTime("P1");
  double totalAccDeadTimeP2 = RunStatusController::instance()->totalAccDeadTime("P2");
  double meanActivityP1     = RunStatusController::instance()->meanActivity("P1");
  double meanActivityP2     = RunStatusController::instance()->meanActivity("P2");

  // If data then make TotMCEvents and AccMCEvents the same as TotalNumEvents to calculate % rather than efficiency
  if(dataFlag){
    TotMCEvents     = 0;
    totalTriggered_ = 0;
    totalAccTriggered_ = 0;
    AccMCEvents_    = TotalNumEvents_;
  }

  // Write file with the numbers of events that passed each cut
  std::ofstream outfile("JobSummary.txt");

  if (outfile.is_open()) {
  outfile << "======================================================================================" << std::endl;
  outfile << "                     Se2b2nCuts End of Job Run Time information                     " << std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << "Processed Data:                                                                       " << std::endl;
  outfile << "Total Run Time           =  " << totalRunTime_                                          << std::endl;
  outfile << "Accepted Run Time        =  " << totalAccRunTime_                                       << std::endl;
  outfile << "Percentage Accepted      =  " << std::setprecision(4) << std::fixed << (100.0*totalAccRunTime_)/totalRunTime_ << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << "Assigned Events:                                                                      " << std::endl;
  outfile << "Total Assigned Events    =  " << totalTriggered_                                        << std::endl;
  outfile << "Accepted Assigned Events =  " << totalAccTriggered_                                     << std::endl;
  outfile << "Percentage Accepted      =  " << (100.0*totalAccTriggered_)/totalTriggered_             << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << "Dead Time Info - Processed Data:                                                      " << std::endl;
  outfile << "Total Dead Time          =  " << totalDeadTime_                                         << std::endl;
  outfile << "Accepted Dead Time       =  " << totalAccDeadTime_                                      << std::endl;
  outfile << "Percentage Accepted      =  " << std::setprecision(4) << std::fixed << (100.0*totalAccDeadTime_)/totalDeadTime_ << std::endl;
  outfile << "Half-life Corr. Factor   =  " << std::setprecision(4) << std::fixed << (totalAccRunTime_-totalAccDeadTime_)/totalAccRunTime_ << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile << "                      Se2b2nCuts End of Job Event Cuts Summary                      " << std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left << "Criterion"
          << std::setw(12) << "    Events"
	  << std::setw(12) << "  Efficiency" << std::endl
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Total MC events generated"
	  << std::setw(12) << std::right << TotMCEvents
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Pass trigger"
	  << std::setw(12) << std::right << totalTriggered_
	  << std::setw(12) << std::right << std::setprecision(3) << std::fixed << (100.0*totalTriggered_)/TotMCEvents
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Reconstructed"
	  << std::setw(12) << std::right << TotalNumEvents_
	  << std::setw(12) << std::right << std::setprecision(3) << std::fixed << (100.0*TotalNumEvents_)/TotMCEvents << std::endl
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Generated events scaled for accepted time"
	  << std::setw(12) << std::right << AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Pass trigger and in accepted run"
	  << std::setw(12) << std::right << totalAccTriggered_ 
	  << std::setw(12) << std::right << (100.0*totalAccTriggered_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Reconstructed and in accepted run"
	  << std::setw(12) << std::right << GoodorStandardRun_ 
	  << std::setw(12) << std::right << (100.0*GoodorStandardRun_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Two tracks in the event"
	  <<std::setw(12) << std::right << TwoTracks_ 
	  << std::setw(12) << std::right << (100.0*TwoTracks_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Both tracks intersect foil"
	  << std::setw(12) << std::right << TwoIntersectFoil_ 
	  << std::setw(12) << std::right << (100.0*TwoIntersectFoil_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Vertex Sector Num is in Selenium"
	  << std::setw(12) << std::right << SeleniumAngle_ 
	  << std::setw(12) << std::right << (100.0*SeleniumAngle_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Both tracks associated with scintillator"
	  << std::setw(12) << std::right << AssociatedTracks_ 
	  << std::setw(12) << std::right << (100.0*AssociatedTracks_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Tracks have different scintillators"
	  << std::setw(12) << std::right << DifferentScints_ 
	  << std::setw(12) << std::right << (100.0*DifferentScints_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Isolated Calorimeter Hits"
	  << std::setw(12) << std::right << IsolatedCalos_ 
	  << std::setw(12) << std::right << (100.0*IsolatedCalos_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Both Energies > 300keV"
	  << std::setw(12) << std::right << EachScint300keV_ 
	  << std::setw(12) << std::right << (100.0*EachScint300keV_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Internal Probability > 0.04"
	  << std::setw(12) << std::right << IntProb4Percent_ 
	  << std::setw(12) << std::right << (100.0*IntProb4Percent_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "External Probability < 0.1"
	  << std::setw(12) << std::right << ExtProb1Percent_ 
	  << std::setw(12) << std::right << (100.0*ExtProb1Percent_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electrons enter front of block"
	  << std::setw(12) << std::right << FrontofBlock_ 
	  << std::setw(12) << std::right << (100.0*FrontofBlock_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electrons don't hit closest petal layer"
	  << std::setw(12) << std::right << NoClosePetals_ 
	  << std::setw(12) << std::right << (100.0*NoClosePetals_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electron PMTs have good status"
	  << std::setw(12) << std::right << ElectronGoodPMT_ 
	  << std::setw(12) << std::right << (100.0*ElectronGoodPMT_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electron PMTs have LD Flag 0"
	  << std::setw(12) << std::right << ElectronLD_ 
	  << std::setw(12) << std::right << (100.0*ElectronLD_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electron PMTs have LD Correction !=0"
	  << std::setw(12) << std::right << ElectronLDCorr_ 
	  << std::setw(12) << std::right << (100.0*ElectronLDCorr_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electron PMTs have LD Correction Error != 0"
	  << std::setw(12) << std::right << ElectronLDCorrErr_ 
	  << std::setw(12) << std::right << (100.0*ElectronLDCorrErr_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Electron PMTs have HS Flag 0"
	  << std::setw(12) << std::right << ElectronHS_ 
	  << std::setw(12) << std::right << (100.0*ElectronHS_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Gamma PMTs have good status"
	  << std::setw(12) << std::right << GammasGoodPMT_ 
	  << std::setw(12) << std::right << (100.0*GammasGoodPMT_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Gamma PMTs have LD Flag 0"
	  << std::setw(12) << std::right << GammasLD_ 
	  << std::setw(12) << std::right << (100.0*GammasLD_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Gamma PMTs have LD Correction !=0"
	  << std::setw(12) << std::right << GammasLDCorr_ 
	  << std::setw(12) << std::right << (100.0*GammasLDCorr_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Gamma PMTs have LD Correction Error != 0"
	  << std::setw(12) << std::right << GammasLDCorrErr_ 
	  << std::setw(12) << std::right << (100.0*GammasLDCorrErr_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Gamma PMTs have HS Flag 0 or 10 (Single Hits 0 only)"
	  << std::setw(12) << std::right << GammasHS_ 
	  << std::setw(12) << std::right << (100.0*GammasHS_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "No other PMTs > 200 keV"
	  << std::setw(12) << std::right << GammaEnergy_ 
	  << std::setw(12) << std::right << (100.0*GammaEnergy_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Vertex within +/- 120cm in Z"
	  << std::setw(12) << std::right << ZinFoil_
	  << std::setw(12) << std::right << (100.0*ZinFoil_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Vertex not at Z=0"
	  << std::setw(12) << std::right << ZNotZero_
	  << std::setw(12) << std::right << (100.0*ZNotZero_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Vertex is not in a hot spot"
	  << std::setw(12) << std::right << NotInHotSpot_
	  << std::setw(12) << std::right << (100.0*NotInHotSpot_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Two track vertices less than 2 cm apart in XY plane"
	  << std::setw(12) << std::right << dXYLessThan2_ 
	  << std::setw(12) << std::right << (100.0*dXYLessThan2_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Two track vertices less than 4 cm apart in Z direction "
	  << std::setw(12) << std::right << dZLessThan4_ 
	  << std::setw(12) << std::right << (100.0*dZLessThan4_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Shorter Track > 20cm"
	  << std::setw(12) << std::right << TrackLengthMin20cm_ 
	  << std::setw(12) << std::right << (100.0*TrackLengthMin20cm_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Longer Track > 50cm"
	  << std::setw(12) << std::right << TrackLengthMax50cm_ 
	  << std::setw(12) << std::right << (100.0*TrackLengthMax50cm_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Sum of lengths of 2 tracks > 80cm"
	  << std::setw(12) << std::right << TrackLengthSum80cm_ 
	  << std::setw(12) << std::right << (100.0*TrackLengthSum80cm_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "First geiger hit in layer 0 or 1"
	  << std::setw(12) << std::right << TracksFirstLayer_  
	  << std::setw(12) << std::right << (100.0*TracksFirstLayer_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Only one missed Gg layer before scintillator"
	  << std::setw(12) << std::right << TracksLastLayer_  
	  << std::setw(12) << std::right << (100.0*TracksLastLayer_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Negative Tracks Only"
	  << std::setw(12) << std::right << NegativeTracks_ 
	  << std::setw(12) << std::right << (100.0*NegativeTracks_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Max 1 prompt unassociated hit within 15cm of vertex in XY"
	  << std::setw(12) << std::right << OneNACloseHit_ 
	  << std::setw(12) << std::right << (100.0*OneNACloseHit_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "If same side, no prompt unassociated hits within 15cm"
	  << std::setw(12) << std::right << SameSideNAHits_ 
	  << std::setw(12) << std::right << (100.0*SameSideNAHits_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "If same side, max 2 prompt unassociated hits anywhere"
	  << std::setw(12) << std::right << SameSideNAFarHits_ 
	  << std::setw(12) << std::right << (100.0*SameSideNAFarHits_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "If same side tracks, at least one hit in layer 0"
	  << std::setw(12) << std::right << SameSideLayer0_ 
	  << std::setw(12) << std::right << (100.0*SameSideLayer0_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "No alpha candidates near to vertex"
	  << std::setw(12) << std::right << NoAlphaCandidates_ 
	  << std::setw(12) << std::right << (100.0*NoAlphaCandidates_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile << "                     Se2b2nCuts End of Job Radon information                          " << std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << "Phase 1:                                                                              " << std::endl;
  outfile << "Accepted Run Time        =  " << totalAccRunTimeP1                                      << std::endl;
  outfile << "Accepted Dead Time       =  " << totalAccDeadTimeP1                                     << std::endl;
  outfile << "Mean Activity (mBq)      =  " << meanActivityP1                                         << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << "Phase 2:                                                                              " << std::endl;
  outfile << "Accepted Run Time        =  " << totalAccRunTimeP2                                      << std::endl;
  outfile << "Accepted Dead Time       =  " << totalAccDeadTimeP2                                     << std::endl;
  outfile << "Mean Activity (mBq)      =  " << meanActivityP2                                         << std::endl;
  outfile <<                                                                                             std::endl;
  outfile << std::endl;
  outfile << "====================================================================================" << std::endl;
  } else {
    std::cout << "Se2b2nCuts::endJob : could not write the report" << std::endl;
    return  AppResult::ERROR;
  }

  return AppResult::OK;
}
