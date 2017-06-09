//
//  GammaFinder.cpp
//
//  Created by Stefano Torre on 09/05/12.
//

// Nemo analysis modules and objects
#include "NemoMods/GammaFinder.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/NemorHeader.h"
#include "NemoObjects/GammaColl.h"
#include "NemoObjects/N3TrackColl.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/N3CalorimeterHitColl.h"

// Hereward modules and objects
#include "Hereward/SuperNemoData/EventHeader.h"
#include "Hereward/SuperNemoProcessing/Constants.h"

// STL5755871
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
GammaFinder::GammaFinder(const std::string theName, 
			       const std::string theDescription) :
  AppModule(theName, theDescription),
  recordHitAtFaceCenter(true),
  useLinearEnergyRes_(true),
  useSummersTimeRes_(true),
  useConstantTimeRes_(false) {
  RandomNumGen = new TRandom3(314159);
  debugLevel_ = 0;
}

GammaFinder::~GammaFinder() {
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult GammaFinder::beginJob(AppEvent *aJob) {  
  return AppResult::OK;
}

AppResult GammaFinder::beginRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult GammaFinder::event(AppEvent *anEvent) {
  // std::cout << "========================= GammaFinder::event(AppEvent* anEvent) - begin"
  // 	    << std::endl;

  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator eventHeader_ci(anEvent, cName);    
  if (!eventHeader_ci.is_valid()) {
    std::cout << "Error Accessing the EventHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 
  EventHeader_ch eventHeader(eventHeader_ci);
  
  mcFlag_ = eventHeader->mcFlag();

  CalibCaloHitColl_ch caloHits;
  if (!CalibCaloHitColl::find(anEvent, caloHits)) {
    // std::cout 
      // << "-- GammaFinder - Calibrated calorimeter hits not found"
      // << std::endl;
    return AppResult::OK;
  }

  if (caloHits->contents().size() == 0) {
    if (debugLevel_ > 0)
      std::cout	
        << "-- GammaFinder - No entries in CalibCaloHitColl"
        << std::endl;
    return AppResult::OK;
  }
    
  N3TrackColl_ch theTrackColl;
  if (!N3TrackColl::find(anEvent, theTrackColl)) {        
    std::cout << "-- GammaFinder - Tracks not found" << std::endl;
    return AppResult::OK;        
  }
    
  N3GeigerHitColl_ch theGgColl;
  if (!N3GeigerHitColl::find(anEvent, theGgColl)) {
    std::cout << "-- GammaFinder - Geiger hits not found" << std::endl;
    return AppResult::OK;
  }

  N3CalorimeterHitColl_ch n3Calohits;
  if (!N3CalorimeterHitColl::find(anEvent, n3Calohits)) {
    std::cout << "-- GammaFinder - N3 Calorimeter hits not found" << std::endl;
    return AppResult::OK;
  }

  // make the list of ids of blocks that have been hit by a track
  std::vector<int> blocksWithTrack;
  for (N3TrackColl::const_iterator trackIt = theTrackColl->contents().begin();
       trackIt != theTrackColl->contents().end();
       ++trackIt) {
    if ((*trackIt).indexOfScintillator() < 0) continue;
    blocksWithTrack.push_back((*trackIt).indexOfScintillator());
  }

  GammaColl *gColl = new GammaColl();
  // Loop over all calibrated calorimter hits in the event and create the Gamma objects
  for (CalibCaloHitColl::const_iterator hitIt = caloHits->contents().begin();
       hitIt != caloHits->contents().end();
       ++hitIt) {
    
    // first check that the block is not hit by a track
    if (find(blocksWithTrack.begin(), blocksWithTrack.end(), 
	     (*hitIt).hitId()) 
	!= blocksWithTrack.end()) {
      continue;
    }

    Gamma gCand;
    gCand.setRawHitId((*hitIt).hitId());
    
    // quick loop to get the position of the gamma hit...
    int calibID_= -1;
    for ( int calib_i = 0; calib_i < caloHits->contents().size(); calib_i++ ) {
      if ( gCand.rawHitId() == caloHits->contents().at(calib_i).hitId() ){calibID_= calib_i;}
    }  
    gCand.setCalibHitId(calibID_);
    
    gCand.setMeasTime((*hitIt).hitTime());
    gCand.setDMeasTime((*hitIt).gammaTimeError());

    // JEM 09/07/13. Find block type to apply correct smearing and right path length errors
    int blockType = -1;

    int iobt = n3Calohits->contents().at(gCand.rawHitId()).iobtFlag();
    int FCLL = n3Calohits->contents().at(gCand.rawHitId()).fcll();
//    int iobt = n3Calohits->contents().at(gCand.hitId()).iobtFlag();
//    int FCLL = n3Calohits->contents().at(gCand.hitId()).fcll();
    if(iobt == 0){
      //IN
      gCand.setBlockType(0);
      blockType = 0;
    } else if (iobt == 1){
      if(FCLL == 0 || FCLL == 2){
	//EE
        gCand.setBlockType(1);
	blockType = 1;
      } else if(FCLL == 1){
	//EC
        gCand.setBlockType(2);
	blockType = 2;
      }
    } else {
      if(FCLL == 0){
	//L1
        gCand.setBlockType(3);
	blockType = 3;
      } else if(FCLL == 1){
	//L2	
        gCand.setBlockType(4);
	blockType = 4;
      } else if(FCLL == 2){
	//L3
        gCand.setBlockType(5);
	blockType = 5;
      } else {
	//L4
        gCand.setBlockType(6);	
	blockType = 6;
      }
    }

    // JEM 09/07/13. If required, apply extra smearing to energy resolution in MC to better 
    // describe the data as seen in docDB 2812. 
    if(useLinearEnergyRes_ && eventHeader->mcFlag()) applyLinearEnergyRes(*hitIt, gCand);
    else {
      gCand.setEnergy((*hitIt).energyDeposit());
      gCand.setDEnergy((*hitIt).fwhm() * sqrt(gCand.energy()) / 2.3548);
    }
     
    // store block dimensions for track length error calculation
    double width, height, thickness;
    switch(blockType) {
    case 0:
      // IN
      width = 15.42;
      height = 15.25; 
      thickness = 10.5; 
      break;
    case 1:
      // EE blocks
      width = 21.75; 
      height = 19.95;
      thickness = 11.12; 
      break;
    case 2:
      // EC blocks
      width = 21.75; 
      height = 19.95;
      thickness = 9.9;
      break;
    case 3:
      //L1
      height = 12.63;
      width = 12.61; 
      thickness = 10.0;
      break;
    case 4:
      //L2
      height = 12.6;
      width = 14.64; 
      thickness = 10.0;
      break;
    case 5:
      //L3
      height = 12.55;
      width = 17.43; 
      thickness = 10.0;
      break;
    case 6:
      //L4
      height = 12.5;
      width = 19.46; 
      thickness = 10.0;
      break;
    }// block type

    gCand.setThickness(thickness);
    gCand.setWidth(width);
    gCand.setHeight(height);
 
    double depth;
    if ( recordHitAtFaceCenter ) depth = 0.; 
    else depth = (eventHeader->mcFlag()) ? 10.9 : 10. ; // values from ROOTANA

    // calculate impact point on the surface of the block
    double phi = (*hitIt).blockCenter().phi();

    CLHEP::Hep3Vector delta;
    switch(iobt) {
    case 0:
      delta = CLHEP::Hep3Vector(-depth * cos(phi), -depth*sin(phi), 0);
      break;
    case 1:
      delta = CLHEP::Hep3Vector( depth * cos(phi),  depth*sin(phi), 0);
      break;
    case 2:
      delta = CLHEP::Hep3Vector( 0, 0, -depth);
      break;
    case 3:
      delta = CLHEP::Hep3Vector( 0, 0, depth);
      break;
    }

    if ( recordHitAtFaceCenter ) {
      gCand.setHitPosition((*hitIt).blockCenter()); // sets the position to be the face of block  
      double error2D = 1.61*sqrt(gCand.blockHeight() * gCand.blockWidth() / 12.);

      // Use the fitted TOF parameters. Details in future TOF note. For now see DocDB 3023 for optimization procedure, 
      // but note that final results have changed since then.
      // S.D.B. 29/4/14
      applyFittedTOFParameters(*hitIt, gCand); //recommended

      // JEM 09/07/13. If required, apply extra smearing to time resolution in MC to better 
      // describe the data.  This has a constant time resolution rather than the 
      // default 1/sqrt(E) dependence.
      //
      // Not recommended for use as accompanying TOF parameters are questionable.
      // This is over-write values set in "applyFittedTOFParameters()"
      if( useConstantTimeRes_ ) applyConstantTimeRes(*hitIt, gCand);

      gCand.setDPathLength(sqrt( pow(error2D/(physics::c/10.),2) + pow(gCand.dPathLength(),2) )); // Geometric error due to size of face + optimized error
      gCand.setGeomError(error2D/(physics::c/10.));
   } else { 
     // sets the hit position to be at the PMT (approximately)
     gCand.setHitPosition((*hitIt).blockCenter() + delta);     
     double deltag = (eventHeader->mcFlag()) ? 8.5 : 13; // cm 
     gCand.setScintToPMTTime(0.); // no need for this if you go straight from vertex to PMT face
     gCand.setDPathLength(deltag / physics::c * 10.);
     gCand.setGeomError(0.);
   } 
    
    gColl->add(gCand);
  }

  GammaColl_ch handle(gColl);
  if ((anEvent->append(handle)).is_null()) {
    std::cout 
      << " ERROR - GammaFinder - error loading collection of gammas "
      << std::endl;
    return AppResult::ERROR;
  }

  // std::cout << "========================= GammaFinder::event(AppEvent* anEvent) - end"
  // 	    << std::endl;
  
  return AppResult::OK;
}

AppResult GammaFinder::endRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult GammaFinder::endJob(AppEvent *aJob) {
  return AppResult::OK;
}

void GammaFinder::applyConstantTimeRes(CalibCaloHit hit, Gamma &gamma) {
  double TauSC_i;
  double thScintTime;
  double dThScintTime;
  int blockType = gamma.blockType();
  if     (blockType == 0){//IN
    TauSC_i = 8.644;
    thScintTime = mcFlag_ ? 0.259 : 0.093;
    dThScintTime = mcFlag_ ? 0.01 : 0.0;
  } 
  else if(blockType == 1){//EE
    TauSC_i = 10.112;
    thScintTime = mcFlag_ ? 0.325 : 0.174;
    dThScintTime = mcFlag_ ? 0.01 : 0.185;    
  }
  else if(blockType == 2){//EC
    TauSC_i = 9.800;
    thScintTime = mcFlag_ ? 0.344 : 0.16;
    dThScintTime = mcFlag_ ? 0.01 : 0.2908;
  } 
  else if(blockType == 3){ //L1
    TauSC_i = 8.084;
    thScintTime = mcFlag_ ? 0.351 : 0.070;
    dThScintTime = mcFlag_ ? 0.0 : 0.0;
  } 
  else if(blockType == 4){//L2
    TauSC_i = 8.866;
    thScintTime = mcFlag_ ? 0.342 : 0.138;
    dThScintTime = mcFlag_ ? 0.025 : 0.0;
  } 
  else if(blockType == 5){//L3
    TauSC_i = 9.385;
    thScintTime = mcFlag_ ? 0.359 : 0.149;
    dThScintTime = mcFlag_ ? 0.06 : 0.0;
  } 
  else if(blockType == 6){//L4
    TauSC_i = 10.834;
    thScintTime = mcFlag_ ? 0.342 : 0.112;
    dThScintTime = mcFlag_ ? 0.0 : 0.0;
  }

  gamma.setScintToPMTTime(thScintTime); 
  gamma.setDPathLength(dThScintTime); // to be added in quadrature with the geometric error

  double energy = hit.energyDeposit();
  double fwhm = hit.fwhm();

  double NPE_Default     = energy/pow(fwhm/2.3548,2);
  double sigma_t_Default = sqrt((4.3*4.3+(1.0/2.3548)*(1.0/2.3548))/NPE_Default*1.0025);

  double NPE_New         = 1.0/pow(fwhm/2.3548,2);
  double sigma_t_New     = sqrt((TauSC_i*TauSC_i+(1.0/2.3548)*(1.0/2.3548))/NPE_New*1.0025);

  if(sigma_t_New/sigma_t_Default > 1){
    if(mcFlag_){
      // For MC, smear times and save new error
      double sigma_t_extra = sigma_t_Default*sqrt(pow(sigma_t_New/sigma_t_Default,2)-1);
      gamma.setMeasTime(RandomNumGen->Gaus(hit.hitTime(),sigma_t_extra));
      gamma.setDMeasTime(sigma_t_New);
    } else {
      // For Data, leave time but thScintTime error. Keep separate calibrations errors from NemoCalibration.
      gamma.setMeasTime(hit.hitTime());
      double gammaTimeError2 = (4.1*4.1 + (1.0/2.3548)*(1.0/2.3548))/ (NPE_Default * 1.0025);
      double calibrationUncertainties2 = pow(hit.gammaTimeError(),2) - gammaTimeError2;
      gamma.setDMeasTime(sqrt(pow(sigma_t_New,2)+calibrationUncertainties2));
    }
  } else {
    gamma.setMeasTime(hit.hitTime());
    gamma.setDMeasTime(hit.gammaTimeError());
  }   
}

void GammaFinder::applyFittedTOFParameters(CalibCaloHit hit, Gamma &gamma) {
  int blockType = gamma.blockType();

  double energy = hit.energyDeposit();
  // S.Blot 5/1/14 
  // the amount of time spent in scintillator and associated error are functions of energy and angle of incidence.
  // Currently too difficult to implement angular dependence, so just energy is taken into account.
  
  double thScintTime;
  double dThScintTime;
  double extraSmearing;
  if (blockType == 0) { //IN
    thScintTime  = (mcFlag_) ? 0.3066 - 0.06131*energy : 0.2252 - (energy*0.09173); // 
    dThScintTime = (mcFlag_) ?  0.1745 +0.124*energy :  0.2636 +0.0682*energy; // 
    extraSmearing = (mcFlag_) ? 0.1637 + 0.139*energy :  0.; // 
  } else if(blockType == 1) { //EE
    thScintTime  = (mcFlag_) ?  0.3394 - 0.0112*energy : 0.2764 - (0.07035*energy); // 
    dThScintTime = (mcFlag_) ? 0.3412 :  0.4222;
    extraSmearing = (mcFlag_) ? 0.2597 + 0.156*energy :  0.; // 
 } else if(blockType == 2) { //EC
    thScintTime  = (mcFlag_) ?  0.3622  - 0.0374*energy : 0.2894 - (0.09488*energy); // 
    dThScintTime = (mcFlag_) ?  0.1997 + 0.2009*energy : 0.2812 + 0.1408*energy; // 
    extraSmearing = (mcFlag_) ?  0.2283 + 0.1697*energy :  0.; // 
  } else if(blockType == 3) { //L1
    thScintTime  = (mcFlag_) ?  0.3078 : 0.2266 - (0.08984*energy); // 
    dThScintTime = (mcFlag_) ?  0.2114 :0.2842; // 
    extraSmearing = (mcFlag_) ? 0. + 0.2087*energy :  0.; // 
  } else if(blockType == 4) { //L2
    thScintTime  = (mcFlag_) ? 0.3368 - 0.05073*energy : 0.2337 - (0.04809*energy); // 
    dThScintTime = (mcFlag_) ?  0.2665 :  0.3151; // 
    extraSmearing = (mcFlag_) ? 0.1913 + 0.1113*energy :  0.; // 
  } else if(blockType == 5) { //L3 
    thScintTime  = (mcFlag_) ? 0.3294 - 0.041*energy  :0.1816/sqrt(energy) ; // 
    dThScintTime = (mcFlag_) ?  0.3606 :0.417; // 
    extraSmearing = (mcFlag_) ? 0.2121 + 0.1755*energy :  0.; // 
  } else if(blockType == 6) { //L4
    thScintTime  = (mcFlag_) ?  0.3217 - 0.04749*energy : 0.1378/sqrt(energy); // 
    dThScintTime = (mcFlag_) ?  0.4588: 0.4858; // 
    extraSmearing = (mcFlag_) ? 0.3246 +0.1305*energy :  0.; // 
  }      
    
  //Now, because the timing resolution doesn't seem to be large
  // enough for the MC (seen if you just plot the pull numerator)
  // we need to add from extra smearing to the times. We do this
  // with tScint rather than the measured times because I like it that way.
  // Also we don't have to mess with the measured time errors this way, 
  // which were optimized with  electron calibration data. 

  //Note this only effects the MC. Data smearing = 0.
  thScintTime = RandomNumGen->Gaus(thScintTime,extraSmearing);


  gamma.setScintToPMTTime(thScintTime); // 2D path length error will be added on in quadriture to this as well
  gamma.setDPathLength(dThScintTime); // to be added in quadrature with the geometric error
   
}

void GammaFinder::applyLinearEnergyRes(CalibCaloHit hit, Gamma &gamma) {
  int blockType = gamma.blockType();
  double k_i;

  if     (blockType == 0){k_i = 1.435;}
  else if(blockType == 1){k_i = 1.640;}
  else if(blockType == 2){k_i = 1.713;}
  else if(blockType == 3){k_i = 1.485;}
  else if(blockType == 4){k_i = 1.558;}
  else if(blockType == 5){k_i = 1.430;}
  else if(blockType == 6){k_i = 1.467;}

  double energy = hit.energyDeposit();
  double fwhm = hit.fwhm();

  if((k_i*k_i*energy - 1) > 0){
    double sigma = sqrt(energy)*fwhm/2.3548 * sqrt(k_i*k_i*energy - 1);
    gamma.setEnergy(RandomNumGen->Gaus(energy, sigma));
    gamma.setDEnergy(k_i*energy*fwhm/2.3548);
  } else {
    gamma.setEnergy(energy);
    gamma.setDEnergy(sqrt(energy)*fwhm/2.3548);
  }

}




//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------

