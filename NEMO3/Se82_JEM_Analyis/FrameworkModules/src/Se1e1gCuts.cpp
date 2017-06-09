//
//  Se1e1gCuts.cpp
//
//  Created by James Mott on 15/11/12
//  

// Module declaration
#include "JEM_Analysis/Se1e1gCuts.h"

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
Se1e1gCuts::Se1e1gCuts(const std::string theName,
                               const std::string theDescription) :
AppModule(theName, theDescription) {
  execType_ = App_module;
  sectorInfo_ = new SectorData();
  radonweighter_ = new RadonWeight();
  HotSpotChecker_ = new HotSpots();
  SFoilSide_ = new SFoilSide();
}

Se1e1gCuts::~Se1e1gCuts() {
  delete sectorInfo_;
  delete radonweighter_;
  delete HotSpotChecker_;
  delete SFoilSide_;
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult Se1e1gCuts::beginJob(AppEvent* aJob) {

  RootOutputManager* nTupleManager = RootOutputManager::instance();

  // Make histograms to fill during cutting to check that everything is sensible
  hElectronEnergy_    = nTupleManager->addHistogram(name(), "hElectronEnergy_", 100, 0, 4);
  hGammaEnergy_       = nTupleManager->addHistogram(name(), "hGammaEnergy_"   , 100, 0, 4);

  hNumLowEGammas_     = nTupleManager->addHistogram(name(), "hNumLowEGammas_"    ,  10, -0.5, 9.5);
  hTotGammaLowEnergy_ = nTupleManager->addHistogram(name(), "hTotGammaLowEnergy_", 100, 0, 1.0);

  hTrackLength_       = nTupleManager->addHistogram(name(), "hTrackLength_", 200, 0, 1200);

  hVertexPosition_    = nTupleManager->addHistogram(name(), "hVertexPosition_", 100, 0, 20, 300, -150, 150);
  hVertexR_           = nTupleManager->addHistogram(name(), "hVertexR_"       , 100, 0, 160);
  hVertexZ_           = nTupleManager->addHistogram(name(), "hVertexZ_"       , 100, -1010,1010);
  hVertexXY_          = nTupleManager->addHistogram(name(), "hVertexXY_"      , 500, -250, 250, 500, -250, 250);

  hProbInt_           = nTupleManager->addHistogram(name(), "hProbInt_"       , 100,0,1);
  hProbExt_           = nTupleManager->addHistogram(name(), "hProbExt_"       , 100,0,1);

  // Create branches for storing data for accepted events
  nTupleManager->addTree(name());
  nTupleManager->addBranch(name(), "b_run", &run_, "run/I");    
  nTupleManager->addBranch(name(), "b_electronEnergy", &electronEnergy_, "electronEnergy/D");
  nTupleManager->addBranch(name(), "b_trackLength", &trackLength_, "trackLength/D");
  nTupleManager->addBranch(name(), "b_trackSign", &trackSign_, "trackSign/D");
  nTupleManager->addBranch(name(), "b_vertexR", &vertexR_, "vertexR/D");
  nTupleManager->addBranch(name(), "b_vertexZ", &vertexZ_, "vertexZ/D");
  nTupleManager->addBranch(name(), "b_vertexSector", &vertexSector_, "vertexSector/D");
  nTupleManager->addBranch(name(), "b_vertexLocation", &vertexLocation_, "vertexLocation/I");
  nTupleManager->addBranch(name(), "b_scintLocation", &scintLocation_, "scintLocation/I");
  nTupleManager->addBranch(name(), "b_radonWeight", &radonWeight_, "radonWeight/D");
  nTupleManager->addBranch(name(), "b_bi210Weight", &bi210Weight_, "bi210Weight/D");
  nTupleManager->addBranch(name(), "b_foilSide", &foilSide_, "foilSide/I");
  nTupleManager->addBranch(name(), "b_gammaEnergy", &gammaEnergy_, "gammaEnergy/D");
  nTupleManager->addBranch(name(), "b_cosTheta", &cosTheta_, "cosTheta/D");
  nTupleManager->addBranch(name(), "b_probInt", &probInt_, "probInt/D");
  nTupleManager->addBranch(name(), "b_probExt", &probExt_, "probExt/D");
  nTupleManager->addBranch(name(), "b_nLowEGammas", &nLowEGammas_, "nLowEGammas/I");
  nTupleManager->addBranch(name(), "b_gammaLowEnergy", &gammaLowEnergy_, "gammaLowEnergy[9]/D");
  nTupleManager->addBranch(name(), "b_goodRun", &goodRun_, "goodRun/O");
  nTupleManager->addBranch(name(), "b_eventTime", &eventTime_, "eventTime/D");
  nTupleManager->addBranch(name(), "b_trueVertexR", &trueVertexR_, "trueVertexR/D");
  nTupleManager->addBranch(name(), "b_trueVertexZ", &trueVertexZ_, "trueVertexZ/D");
  nTupleManager->addBranch(name(), "b_trueVertexSector", &trueVertexSector_, "trueVertexSector/D");

  // Initialise counters that will keep track of number of events that pass each cut
  TotalNumEvents_    = 0; 
  GoodRunStatus_     = 0; 
  OneTrack_          = 0;
  AssociatedTrack_   = 0;
  OneGamma_          = 0;
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
  Electron300keV_    = 0;
  Gamma300keV_       = 0;
  GammaEnergy_       = 0;
  TrackLayer0or1_    = 0;
  TrackLastLayer_    = 0;
  IntersectsFoil_    = 0;
  TrackLength20cm_   = 0;
  SeleniumAngle_     = 0;
  ZinFoil_           = 0;
  ZNotZero_          = 0;
  NotInHotSpot_      = 0;
  OneNACloseHit_     = 0;
  TwoNAFarHits_      = 0;
  NoDelayedHit_      = 0;
  NoDelayedCluster_  = 0;
  IntProb4Percent_   = 0;
  ExtProb1Percent_   = 0;

  dataFlag = false;

  return AppResult::OK;    
}

AppResult Se1e1gCuts::beginRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult Se1e1gCuts::event(AppEvent* anEvent) {

  // Get all the data from the event and put it in appropriate collections
   
  // 1) Get EventHeader
  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator runRecord(anEvent, cName);    
  EventHeader_ch eventHeader(runRecord);
  if (!runRecord.is_valid()) {
    std::cout << "-- Se1e1gCuts - Error Accessing the RunHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 

  // 2) Get Electron collection
  ElectronColl_ch theElectronColl;
  ElectronColl::ElectronList electronList;
  if (ElectronColl::find(anEvent, theElectronColl)) {        
    electronList = theElectronColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - Electrons not found" << std::endl;
    return AppResult::OK;
  }

  // 3) Get Alpha collection
  AlphaColl_ch theAlphaColl;
  AlphaColl::AlphaList alphaList;
  if (AlphaColl::find(anEvent, theAlphaColl)) {        
    alphaList = theAlphaColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - Alphas not found" << std::endl;
    return AppResult::OK;
  }

  // 4) Get GammaCluster collection
  GammaClusterColl_ch theGammaClusterColl;
  GammaClusterColl::ClusterList gammaClusterList;
  if (GammaClusterColl::find(anEvent, theGammaClusterColl)) {        
    gammaClusterList = theGammaClusterColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - Gamma Clusters not found" << std::endl;
    return AppResult::OK;
  }

  // 5) Get Local Track collection
  N3TrackSegmentColl_ch theTrackColl;
  N3TrackSegmentColl::N3TrackSegmentList trackList;
  if (N3TrackSegmentColl::find(anEvent, theTrackColl)) {        
    trackList = theTrackColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - Tracks not found" << std::endl;
    return AppResult::OK;        
  }
        
  // 6) Get Calibrated Calorimeter hit collection
  CalibCaloHitColl_ch theCaloHitColl;
  CalibCaloHitColl::CalibCaloHitList caloHitList;
  if (CalibCaloHitColl::find(anEvent, theCaloHitColl)) {
    caloHitList = theCaloHitColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - Calibrated calorimeter hits not found" << std::endl;
    return AppResult::OK;
  }

  // 7) Get Raw Calorimeter hit collection
  N3CalorimeterHitColl_ch theRawCaloHitColl;
  N3CalorimeterHitColl::N3CalorimeterHitList rawCaloHitList;
  if (N3CalorimeterHitColl::find(anEvent, theRawCaloHitColl)) {
    rawCaloHitList = theRawCaloHitColl->contents();
  } else {
    std::cout  << "-- Se1e1gCuts - Raw Calorimeter hits not found"  << std::endl;
    return AppResult::OK;
  }

  // 8) Get Raw Geiger hit collection
  N3GeigerHitColl_ch theRawGgHitColl;
  N3GeigerHitColl::N3GeigerHitList rawGgHitList;
  if (N3GeigerHitColl::find(anEvent, theRawGgHitColl)){
    rawGgHitList = theRawGgHitColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - Raw Geiger hits not found" << std::endl;
    return AppResult::OK;
  }

  // 9) Get true vertex collection
  TrueVertexColl_ch theTrueVertexColl;
  TrueVertexColl::TrueVertexList trueVertexList;
  if (TrueVertexColl::find(anEvent, theTrueVertexColl)){
    trueVertexList = theTrueVertexColl->contents();
  } else {
    std::cout << "-- Se1e1gCuts - True Vertex info not found" << std::endl;
    return AppResult::OK;
  }

  // ================================================================================================
  // GENERAL CUTS - ONE TRACKS AND AT LEAST ONE GOOD QUALITY HITS
  // ================================================================================================

  // Output counter to screen to keep tabs on how far program's got
  if(TotalNumEvents_ % 50000 == 0){std::cout << "Processing event " << TotalNumEvents_ << std::endl;}

  // Get Event and Run Numbers
  run_            = eventHeader->runNumber();
  TotalNumEvents_++;
  if(!eventHeader->mcFlag()){ dataFlag = true; }

  // Make sure event is in good or standard run.
  if (!RunStatusController::instance()->currentRunIsAccepted()) {
    return AppResult::OK;
  }
  GoodRunStatus_++;

  // Flag good run events in case we want to use this run list instead later.
  goodRun_ = true;
  if (RunStatusController::instance()->runStatus() != 1) {goodRun_ = false;}

  // Cut events without exactly one track
  if (trackList.size() != 1){return AppResult::OK;}
  OneTrack_++;

  // Cut unassociated tracks or ones that are associated to noisy scintillators
  if(trackList.at(0).indexOfScintillator() < 0 || 
     rawCaloHitList.at(trackList.at(0).indexOfScintillator()).isNoisy()){
    return AppResult::OK;
  }
  AssociatedTrack_++;

  // Cut events without exactly one gamma above 300 keV
  int num300keVGammas = 0;
  int gammaID = -1;
  for(int i = 0; i < gammaClusterList.size(); i++){
    if(gammaClusterList.at(i).energy() >= 0.3){
      num300keVGammas++;
      gammaID = i;
    }
  }
  if(num300keVGammas != 1){return AppResult::OK;}
  OneGamma_++;

  // Get hold of electron, track and gamma and store them to use later
  Electron electron = electronList.at(0);
  N3TrackSegment eTrack = trackList[electron.trackId()];
  GammaCluster gamma = gammaClusterList.at(gammaID);

  // Cut events where the electron hit isn't isolated and close scints aren't noisy
  int caloHitIds[1];
  caloHitIds[0] = electron.hitId();
  int rawCaloHitIds[1];
  rawCaloHitIds[0] = caloHitList.at(electron.hitId()).hitId();

  for(int j = 0; j < rawCaloHitList.size(); j++){
    if(j != rawCaloHitIds[0]){
      int comparison = rawCaloHitList.at(rawCaloHitIds[0]).checkNeighbour(rawCaloHitList.at(j));
      if (comparison != 0  && !rawCaloHitList.at(j).isNoisy()){return AppResult::OK;}
    }
  }
  IsolatedCalos_++;

  // ================================================================================================
  // ELECTRON QUALITY CUTS
  // ================================================================================================

  // Cut events where the impact region is on the side of the blocks
  if (electron.impactRegion() == 66) {return AppResult::OK;}
  FrontofBlock_++;

  // Store electron scintillator location (In/Out/Petals & petal layer(1-4) from inner to outer).
  if(rawCaloHitList.at(rawCaloHitIds[0]).iobtFlag() == 0){scintLocation_ = 0;}
  else if(rawCaloHitList.at(rawCaloHitIds[0]).iobtFlag() == 1){scintLocation_ = 1;}
  else if(rawCaloHitList.at(rawCaloHitIds[0]).iobtFlag() == 2){
    scintLocation_ = (rawCaloHitList.at(rawCaloHitIds[0]).fcll()+1)*10 + 2;
  }
  else if(rawCaloHitList.at(rawCaloHitIds[0]).iobtFlag() == 3){
    scintLocation_ = (rawCaloHitList.at(rawCaloHitIds[0]).fcll()+1)*10 + 3;
  }

  // Cut events where electron hits one of inner layers of petals
  if(rawCaloHitList.at(rawCaloHitIds[0]).iobtFlag() > 1){
    if(rawCaloHitList.at(rawCaloHitIds[0]).fcll() == 1 || rawCaloHitList.at(rawCaloHitIds[0]).fcll() == 2){
      return AppResult::OK;
    } 
  }
  NoClosePetals_++;

  // Good PMT Status
  if ( ! caloHitList.at(caloHitIds[0]).goodFlag() ) {return AppResult::OK;}
  ElectronGoodPMT_++;
  
  // LD Flag == 0
  if ( caloHitList.at(caloHitIds[0]).ldFlag() > 0 ) {return AppResult::OK;}
  ElectronLD_++;

  // LD Correction != 0  
  if ( caloHitList.at(caloHitIds[0]).ldCorr() == 0 ){return AppResult::OK;}
  ElectronLDCorr_++;

  // LD Correction Err != 0  
  if ( caloHitList.at(caloHitIds[0]).ldCorrErr() == 0 ){return AppResult::OK;}
  ElectronLDCorrErr_++;

  // HS Flag == 0  
  if ( caloHitList.at(caloHitIds[0]).hsFlag() > 0 ){return AppResult::OK;}
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
  // ENERGY CUTS - 300 keV electron, 300 keV gamma and total gamma energy < 250 keV
  // ================================================================================================

  // Get hold of energy of electron and gamma
  electronEnergy_ = electron.energy();
  hElectronEnergy_    -> Fill(electronEnergy_);
  gammaEnergy_ = gamma.energy();
  hGammaEnergy_ ->Fill(gammaEnergy_);

  // Cut events where energy of either scintillator is less than 300 keV
  if (electronEnergy_ <= 0.3){return AppResult::OK;}
  Electron300keV_++;
  if (gammaEnergy_ <= 0.3){return AppResult::OK;}
  Gamma300keV_++;

  // Fill Histograms for number of gammas and total energy before cut
  nLowEGammas_ = gammaClusterList.size() - 1;
  hNumLowEGammas_ ->Fill(nLowEGammas_);
  double totGammaLowEnergy = 0;
  for(int i = 0; i < gammaClusterList.size(); i++){
    if(i != gammaID){
      totGammaLowEnergy += gammaClusterList.at(i).energy();
    }
  }
  hTotGammaLowEnergy_ ->Fill(totGammaLowEnergy);

  // Cut events where any PMT has energy > 200 keV
  for(int i = 0; i < gammaClusterList.size(); i++){
    if(i != gammaID){
      for(int j = 0; j < gammaClusterList.at(i).cluster().size(); j++){
        if(gammaClusterList.at(i).cluster().at(j).energy() > 0.2){return AppResult::OK;}
      }
    }
  }
  GammaEnergy_++;

  // Cut events where there's more than 10 gammas or can't store array easily
  if(nLowEGammas_ > 9){return AppResult::OK;}
  for(int i = 0; i < 9; i++){gammaLowEnergy_[i] = 0;}
  for(int i = 0; i < gammaClusterList.size(); i++){
    if(i != gammaID){
      gammaLowEnergy_[i] = gammaClusterList.at(i).energy();
    }
  }

  // ================================================================================================
  // TRACKING CUTS - HITS IN FIRST & LAST TWO LAYERS, INTERSECTING FOIL, GOOD LENGTH
  // ================================================================================================

  // Cut events where track doesn't start in layer 0 or layer 1
  int firstGgHit = electron.firstGeigerHit();
  if(rawGgHitList.at(firstGgHit).layer() > 1){return AppResult::OK;}
  TrackLayer0or1_++;

  // Get last Gg layer
  int lastGgHit = eTrack.geigerHitList()->at(eTrack.geigerHitList()->size()-1);
  int lastGgHitLayer = rawGgHitList.at(lastGgHit).layer();

  // Then how many layers were missed before scintillator
  int Scint_Last_Gg_Dist;
  if(scintLocation_ == 0  or scintLocation_ == 1)  Scint_Last_Gg_Dist = 8 - lastGgHitLayer;
  if(scintLocation_ == 12 or scintLocation_ == 13) Scint_Last_Gg_Dist = 5 - lastGgHitLayer;
  if(scintLocation_ == 22 or scintLocation_ == 23) Scint_Last_Gg_Dist = 3 - lastGgHitLayer;
  if(scintLocation_ == 32 or scintLocation_ == 33) Scint_Last_Gg_Dist = 3 - lastGgHitLayer;
  if(scintLocation_ == 42 or scintLocation_ == 43) Scint_Last_Gg_Dist = 5 - lastGgHitLayer;

  // Cut if it's missed more than 1 Gg layer
  if(Scint_Last_Gg_Dist > 1){return AppResult::OK;}
  TrackLastLayer_++;

  // Cut events where the electron isn't reconstructed from the foil
  if(!electron.intersectTheFoil()){return AppResult::OK;}
  IntersectsFoil_++;

  // Get hold of track length of each electron and store
  trackLength_  = electron.pathLength();
  hTrackLength_-> Fill(trackLength_);

  // Cut events where track length is less than 20 cm
  if (trackLength_ <= 20) {return AppResult::OK;}
  TrackLength20cm_++;

  // Store sign of tracks in case we want to cut on this at analysis level
  trackSign_ = eTrack.sign();

  // Cut events with positive tracks
  if(trackSign_ > 0){ return AppResult::OK;}
  NegativeTracks_++;

  // ================================================================================================
  // VERTEX CUTS - ANGLE IN SE FOIL, +/- 120 cm IN Z. VERTICES LESS THAN 2 cm IN XY AND 4 cm IN Z
  // ================================================================================================

  // Define vertex as intersection of electron and foil
  CLHEP::Hep3Vector vertex = electron.vertex();

  // Calculate vertex locations to use to cut
  vertexR_ = TMath::Sqrt(vertex.x()*vertex.x() +  vertex.y()*vertex.y()); 
  vertexZ_ = vertex.z(); 
  if(vertex.x() >= 0){vertexSector_ = (20.0/TMath::TwoPi())*TMath::ASin(vertex.y()/vertexR_);}
  else if(vertex.x() < 0){vertexSector_ = (20.0/TMath::TwoPi())*(TMath::Pi() - TMath::ASin( vertex.y()/vertexR_));}
  if(vertexSector_ < 0){vertexSector_ += 20.0;}
  
  // Cut events if they're not in selenium part of source foil
  SourceType source = sectorInfo_->sourceOfVertex(vertex);
  if (source != SourceType::SeNew && source != SourceType::SeOld){return AppResult::OK;}
  SeleniumAngle_++;

  // Vertex Location (0 - SeOld, 1 - SeNew, 2 - SeNewStrip)
  vertexLocation_ = -1;
  if (source == SourceType::SeOld){vertexLocation_ = 0;}
  else if (source == SourceType::SeNew){
    if(sectorInfo_->sectorNumber(vertex) <= 8.0){ vertexLocation_ = 1;}
    else{vertexLocation_ = 2;}
  }

  // Fill Vertex Histograms to check reconstructed events come from right place
  hVertexR_        -> Fill(vertexR_);
  hVertexZ_        -> Fill(vertexZ_);
  hVertexPosition_ -> Fill(vertexSector_,vertexZ_);
  hVertexXY_       -> Fill( vertex.x(), vertex.y());

  // Cut events where the Z of vertex isn't in the foil (+/- 120cm)
  if(fabs(vertex.z()) > 120){return AppResult::OK;}
  ZinFoil_++;

  // Cut events where the vertex Z is 0
  if(vertex.z() == 0){return AppResult::OK;}
  ZNotZero_++;

  // Cut events if it comes from a hotspot as found in the hotspot search.
  if(HotSpotChecker_->InHotSpot(vertex)){return AppResult::OK;}
  NotInHotSpot_++;

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
  // NA PROMPT HITS CUTS
  // ================================================================================================

  // Make vector containing all the rawGgHistList IDs of prompt unassociated hits
  std::vector<int> NAPromptHits;
  for(int i = 0; i < rawGgHitList.size(); i++){
    bool used = false;
    for(int j = 0; j < eTrack.geigerHitList()->size(); j++){
      if(eTrack.geigerHitList()->at(j) == i){
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

  // Cut events where there are more than one prompt unassociated hits within 15cm of vertex in XY plane.
  if(nCloseNAPromptHits > 1){return AppResult::OK;}
  OneNACloseHit_++;

  // Cut events where there are more than two prompt unassociated hits anywhere.
  if(nFarNAPromptHits > 2){return AppResult::OK;}
  TwoNAFarHits_++;

  // ================================================================================================
  // DELAYED HITS CUTS - ALPHAS, NA PROMPT HITS ETC
  // ================================================================================================

  // Remove events with single delayed geiger hit close to the vertex (alphas)
  for(int i = 0; i < alphaList.size(); i++){
    if(alphaList.at(i).nDelayedHits() == 1){
      return AppResult::OK;
    }
  }
  NoDelayedHit_++;
      
  // Remove events with group of delayed geiger hits close to the vertex (alphas)
  for(int i = 0; i < alphaList.size(); i++){
    if(alphaList.at(i).nDelayedHits() > 1){
      return AppResult::OK;
    }
  }
  NoDelayedCluster_++;

  // ================================================================================================
  // PROBABILITY CUTS - INTERNAL > 0.04; EXTERNAL < 0.01
  // ================================================================================================

  // Need to start by defining gamma hit position for time of flight calculations - use first hit
  Gamma gamma1st = gamma.earliestHit();
  CLHEP::Hep3Vector gamma1stImpact = gamma1st.hitPosition();
  double gamma1stLength = sqrt(pow(gamma1stImpact.x()-vertex.x(),2)+pow(gamma1stImpact.y()-vertex.y(),2)+pow(gamma1stImpact.z()-vertex.z(),2));

  // Calculate Internal Probability
  double numerInt = pow( (electron.measTime()-electron.thTof()) - (gamma1st.measTime()-gamma1stLength/(physics::c/10.0)-gamma1st.scintToPMTTime()) , 2);
  double denomInt = pow(electron.dMeasTime(),2) + pow(electron.dThTof(),2) + pow(gamma1st.dMeasTime(),2) + pow(gamma1st.dPathLength(),2);
  double chiSqInt = numerInt / denomInt;
  probInt_ = TMath::Prob(chiSqInt, 1);
  hProbInt_ -> Fill(probInt_);

  // External Probability Hypotheses - assume electron and gammaHit are a crossing particle interacting in foil.
  double numerExt = pow(fabs(gamma1st.measTime() - electron.measTime()) - (electron.thTof()+gamma1stLength/(physics::c/10)+gamma1st.scintToPMTTime()), 2);
  double denomExt = pow(electron.dMeasTime(), 2) + pow(gamma1st.dMeasTime(), 2) + pow(electron.dThTof(), 2) + pow(gamma1st.dPathLength(),2);
  double chiSqExt = numerExt / denomExt;
  probExt_  = TMath::Prob(chiSqExt,1);
  hProbExt_ -> Fill(probExt_);

  // Cut events with internal probability less than 0.04
  if(probInt_ < 0.04){return AppResult::OK;}
  IntProb4Percent_++;

  // Cut events with external probability greater than 0.01
  if(probExt_ > 0.01){return AppResult::OK;}
  ExtProb1Percent_++;

  // ================================================================================================
  // FINALLY CALCULATE COSINE, USE NEMOUTILS TO GET RADON MAP WEIGHTS, THEN SAVE ROOT FILE
  // ================================================================================================

  // Calculate cosine between electron and gamma
  CLHEP::Hep3Vector gammaImpact = gamma.hitPosition();
  double gammaLength = sqrt(pow(gammaImpact.x()-vertex.x(),2)+pow(gammaImpact.y()-vertex.y(),2)+pow(gammaImpact.z()-vertex.z(),2));
  CLHEP::Hep3Vector electronDirCosine = eTrack.directionCosine();
  gammaLength = sqrt(pow(gammaImpact.x()-vertex.x(),2)+pow(gammaImpact.y()-vertex.y(),2)+pow(gammaImpact.z()-vertex.z(),2));
  CLHEP::Hep3Vector gammaDirCosine((gammaImpact.x()-vertex.x())/gammaLength,(gammaImpact.y()-vertex.y())/gammaLength,(gammaImpact.z()-vertex.z())/gammaLength);
  cosTheta_ = electronDirCosine.cosTheta(gammaDirCosine);

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

  // Save everything in branch and close App
  RootOutputManager::instance()->capture(name());

  // Find time of middle of run since date of run 1869 (15th Feb 2003) - used to weight decaying isotopes
  TTimeStamp startTime(2003,02,15,00,00,00);
  TTimeStamp runStartTime = RunStatusController::instance()->runStart();
  eventTime_ = runStartTime.GetSec() + (RunStatusController::instance()->runLength())/2. - startTime.GetSec();

  return AppResult::OK;
}


AppResult Se1e1gCuts::endRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult Se1e1gCuts::endJob(AppEvent* aJob) {

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
  outfile << "                     Se1e1gCuts End of Job Run Time information                     " << std::endl;
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
  outfile << "                      Se1e1gCuts End of Job Event Cuts Summary                      " << std::endl;
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
	  << std::setw(12) << std::right << GoodRunStatus_ 
	  << std::setw(12) << std::right << (100.0*GoodRunStatus_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "One track in the event"
	  <<std::setw(12) << std::right << OneTrack_ 
	  << std::setw(12) << std::right << (100.0*OneTrack_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Track associated with scintillator"
	  << std::setw(12) << std::right << AssociatedTrack_ 
	  << std::setw(12) << std::right << (100.0*AssociatedTrack_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Only one gamma above 300 keV"
	  << std::setw(12) << std::right << OneGamma_ 
	  << std::setw(12) << std::right << (100.0*OneGamma_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Isolated Calorimeter Hits for both electron and gamma"
	  << std::setw(12) << std::right << IsolatedCalos_ 
	  << std::setw(12) << std::right << (100.0*IsolatedCalos_)/AccMCEvents_
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
  outfile << std::setw(60) << std::left  << "Electron scintillator energy > 300 keV"
	  << std::setw(12) << std::right << Electron300keV_ 
	  << std::setw(12) << std::right << (100.0*Electron300keV_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Gamma scintillator energy > 300 keV"
	  << std::setw(12) << std::right << Gamma300keV_ 
	  << std::setw(12) << std::right << (100.0*Gamma300keV_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "No other PMTs > 200 keV"
	  << std::setw(12) << std::right << GammaEnergy_ 
	  << std::setw(12) << std::right << (100.0*GammaEnergy_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "First geiger hit in layer 0 or 1"
	  << std::setw(12) << std::right << TrackLayer0or1_  
	  << std::setw(12) << std::right << (100.0*TrackLayer0or1_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "No more than one GG layer missed before scint"
	  << std::setw(12) << std::right << TrackLastLayer_  
	  << std::setw(12) << std::right << (100.0*TrackLastLayer_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Track intersects foil"
	  << std::setw(12) << std::right << IntersectsFoil_ 
	  << std::setw(12) << std::right << (100.0*IntersectsFoil_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Track length > 20cm"
	  << std::setw(12) << std::right << TrackLength20cm_ 
	  << std::setw(12) << std::right << (100.0*TrackLength20cm_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Negative Tracks Only"
	  << std::setw(12) << std::right << NegativeTracks_ 
	  << std::setw(12) << std::right << (100.0*NegativeTracks_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Vertex is in selenium angle"
	  << std::setw(12) << std::right << SeleniumAngle_ 
	  << std::setw(12) << std::right << (100.0*SeleniumAngle_)/AccMCEvents_
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
  outfile << std::setw(60) << std::left  << "Max 1 prompt unassociated hit within 15cm of vertex in XY"
	  << std::setw(12) << std::right << OneNACloseHit_ 
	  << std::setw(12) << std::right << (100.0*OneNACloseHit_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Max 2 prompt unassociated hits anywhere"
	  << std::setw(12) << std::right << TwoNAFarHits_ 
	  << std::setw(12) << std::right << (100.0*TwoNAFarHits_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "No delayed single hit (>100us; <25cm in XY; <30cm in Z)"
	  << std::setw(12) << std::right << NoDelayedHit_ 
	  << std::setw(12) << std::right << (100.0*NoDelayedHit_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "No delayed hit cluster (>20us; <25cm in XY; <30cm in Z)"
	  << std::setw(12) << std::right << NoDelayedCluster_ 
	  << std::setw(12) << std::right << (100.0*NoDelayedCluster_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "Internal Probability > 0.04"
	  << std::setw(12) << std::right << IntProb4Percent_ 
	  << std::setw(12) << std::right << (100.0*IntProb4Percent_)/AccMCEvents_
	  <<                                                                                             std::endl;
  outfile << std::setw(60) << std::left  << "External Probability < 0.01"
	  << std::setw(12) << std::right << ExtProb1Percent_ 
	  << std::setw(12) << std::right << (100.0*ExtProb1Percent_)/AccMCEvents_
	  <<                                                                                             std::endl;

  outfile << std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile << "                     Se1e1gCuts End of Job Radon information                     " << std::endl;
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
    std::cout << "Se1e1gCuts::endJob : could not write the report" << std::endl;
    return  AppResult::ERROR;
  }

  return AppResult::OK;
}
