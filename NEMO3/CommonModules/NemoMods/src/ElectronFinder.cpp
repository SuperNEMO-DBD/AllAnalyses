//
//  ElectronFinder.cpp
//
//  Created by Stefano Torre on 09/05/12.
//

// Nemo analysis modules and objects
#include "NemoMods/ElectronFinder.h"
#include "NemoObjects/NemorHeader.h"
#include "NemoObjects/N3TrackColl.h"
#include "NemoObjects/N3TrackSegmentColl.h"
#include "NemoObjects/N3GeigerHitColl.h"

// Hereward modules and objects
#include "Hereward/SuperNemoData/EventHeader.h"
#include "Hereward/SuperNemoProcessing/Constants.h"
#include "Hereward/DataProcPipeline/AbsEnv.h"

// STL
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
ElectronFinder::ElectronFinder(const std::string theName, 
			       const std::string theDescription) :
  AppModule(theName, theDescription), useLocalFit_(false), debugLevel_(0), useElectronScintToPMTTime_(false) {
}

ElectronFinder::~ElectronFinder() {
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult ElectronFinder::beginJob(AppEvent *aJob) {
  return AppResult::OK;
}

AppResult ElectronFinder::beginRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult ElectronFinder::createElectronFromGlobalFit(AppEvent* anEvent) {

  CalibCaloHitColl_ch caloHits;
  if (!CalibCaloHitColl::find(anEvent, caloHits)) {
    if (debugLevel_ > 0) {
      std::cout 
        << "-- ElectronFinder - Calibrate calorimeter hits not found"
        << std::endl;
    }
    return AppResult::OK;
  }

  if (caloHits->contents().size() == 0) {
    if (debugLevel_ > 0 )
      std::cout	
        << "-- ElectronFinder - No entries in CalibCaloHitColl"
        << std::endl;
    return AppResult::OK;
  }
    
  N3TrackColl_ch theTrackColl;
  if (!N3TrackColl::find(anEvent, theTrackColl)) {        
    if (debugLevel_ > 0) 
      std::cout << "-- ElectronFinder - Tracks not found" << std::endl;
    return AppResult::OK;        
  }
    
  N3GeigerHitColl_ch theGgColl;
  if (!N3GeigerHitColl::find(anEvent, theGgColl)) {
    if (debugLevel_ > 0)
      std::cout << "-- ElectronFinder - Geiger hits not found" << std::endl;
    return AppResult::OK;
  }
  
  // N3CalorimeterHitColl_ch theGgColl;
  // if (!N3CalorimeterHitColl::find(anEvent, theGgColl)) {
  //   std::cout << "-- ElectronFinder - Calorimeter hits not found" << std::endl;
  //   return AppResult::OK;
  // }
  
  ElectronColl *eColl = new ElectronColl();

  // Loop over all tracks it the event and create the Electron objects
  int trackId = 0;
  for (unsigned int trackId = 0; trackId < theTrackColl->contents().size();
       ++trackId) {
    N3Track trk = theTrackColl->contents().at(trackId);
    
    if (trk.corruptedGeiger()) {
      if (debugLevel_ > 0) 
        std::cout << "WARNING - ElectronFinder::event - (Run, Event) = ("
                  << AbsEnv::instance()->runNumber() << ", " << AbsEnv::instance()->trigNumber() 
                  << ")\nWARNING track "
                  << trackId << " has corrupted list of geiger hits - discarded"
                  << std::endl;
      continue;
    }

    if (trk.corruptedCalo()) {
      if (debugLevel_ > 0)
        std::cout << "WARNING - ElectronFinder::event - (Run, Event) = ("
                  << AbsEnv::instance()->runNumber() << ", " << AbsEnv::instance()->trigNumber() 
                  << ")\nWARNING track "
                  << trackId << " has corrupted link to calorimeter hit - discarded"
                  << std::endl;
      continue;
    }

    if (trk.indexOfScintillator() < 0) {
      // the track is not associated to any scintillator therefore we 
      // skip it
      continue;
    }

   //  CalibCaloHit caloHi  = caloHits->contents().at(trk.indexOfScintillator());
   //  if (!caloHit.goodFlag()) {
   //    continue;
   //  }
      
    Electron eCand;

    int calibratedId = 0;
    CalibCaloHitColl::const_iterator calohit = caloHits->contents().begin();
    bool found = false;
   
    while(calohit != caloHits->contents().end() and !found) {
      // look for the calibrated calorimeter hit associated to the raw hit
      found = (calohit->hitId() == trk.indexOfScintillator());
      if (found) {
        eCand.setHitId(calibratedId);
      } else {
        ++calibratedId;
        ++calohit;
      }
    }
    
    if (!found) {
      if (debugLevel_ > 1)
        std::cout << "WARNING - ElectronFinder::event - (Run, Event) = ("
                  << AbsEnv::instance()->runNumber() << ", " 
                  << AbsEnv::instance()->trigNumber() 
                  << ")\nWARNING track "
                  << trackId << " was associated with Calorimeter Hit Id = " 
                  << trk.indexOfScintillator()
                  << " - corresponding Calibrated Hit not found "
                  << std::endl;
    } else {
  
      // references to other collections
      eCand.setTrackId(trackId);
      eCand.setFirstGeigerHit(trk.geigerHitList()->at(0));
  
      // these two properties are usefull in filtering candidates, so we promote them
      // to members of the Electron rather than keeping them in the track object
      eCand.setIntersectTheFoil(trk.intersectionOnFoil().mag2() > 1e-4);
      eCand.setImpactRegion(trk.impactRegion());
      
      if (eCand.intersectTheFoil()) {
        eCand.setVertex(trk.intersectionOnFoil());
      } else {
        // use the position of the first anode as x,y coordinate of the vertex and the
        // z of the first geiger hit as z of the vertex
        N3GeigerHit ggHit = theGgColl->contents().at(eCand.firstGeigerHit());
        CLHEP::Hep3Vector vertex(ggHit.anodePosition().x(),
               ggHit.anodePosition().y(),
               ggHit.z());
        eCand.setVertex(vertex);
      }
      
      // beta of the electron
  
      eCand.setEnergy(calohit->energyDeposit());
      eCand.setDEnergy(calohit->fwhm() * sqrt(eCand.energy()) / 2.3548);
          
      double pathLength = 
        trk.distanceAlongTrack(eCand.vertex(),
             trk.intersectionOnCalo());
      eCand.setPathLength(pathLength);
      
      eCand.setMeasTime(calohit->hitTime());
      eCand.setDMeasTime(calohit->electronTimeError());
  
      eCand.setEnergyLoss(calculateEnergyLoss(eCand, *calohit));
  
      // Calculate extra time from scintillator impact to PMT - JEM 04/12/13
  
      // First get block thickness based on types
      double blockThickness;
  
      if(calohit->iobt() == 0){
        blockThickness = 10.5;     //IN
      } else if (calohit->iobt() == 1){
        if(calohit->fcll() == 0 || calohit->fcll() == 2){
          blockThickness = 11.12;  //EE
        } else if(calohit->fcll() == 1){
          blockThickness = 9.9;    //EC
        }
      } else {
        if(calohit->fcll() == 0){
          blockThickness = 10.0;   //L1
        } else if(calohit->fcll() == 1){
          blockThickness = 10.0;   //L2
        } else if(calohit->fcll() == 2){
          blockThickness = 10.0;   //L3
        } else {
          blockThickness = 10.0;   //L4
        }
      }
  
      // Calculate extra distance to back of block from centre of front face
      double phi = calohit->blockCenter().phi();
      CLHEP::Hep3Vector delta;
  
      switch(calohit->iobt()) {
      case 0:
        delta = CLHEP::Hep3Vector(-blockThickness*cos(phi), -blockThickness*sin(phi), 0);
        break;
      case 1:
        delta = CLHEP::Hep3Vector( blockThickness*cos(phi),  blockThickness*sin(phi), 0);
        break;
      case 2:
        delta = CLHEP::Hep3Vector( 0, 0, -blockThickness);
        break;
      case 3:
        delta = CLHEP::Hep3Vector( 0, 0, blockThickness);
        break;
      }
  
      // Calculate distance from hit position (on front face) to centre of back of block and then add light guide
      // DANGER!!!  You shouldn't actually USE this quantity unless you are making a dedicated study. 
      // All Gamma-related quantities (path length, TOF parameters, etc) have been optimized WITHOUT using this
      // extra time taken into consideration.
      double scintToPMTDist = (trk.intersectionOnCalo() - (calohit->blockCenter() + delta)).mag() + 6.;

      if ( useElectronScintToPMTTime_ ) {
        eCand.setScintToPMTTime(1.5*scintToPMTDist/(physics::c/10)); //index of refraction, n = 1.5 for scintillator
      } else {
        eCand.setScintToPMTTime(0.); // Just in case you try to use it when you shouldn't be! 
      }
  
      eColl->add(eCand);
    }
  }

  ElectronColl_ch handle(eColl);
  if ((anEvent->append(handle)).is_null()) {
    std::cout 
      << " ERROR - ElectronFinder - error loading collection of electrons "
      << std::endl;
    return AppResult::ERROR;
  }
}

AppResult ElectronFinder::createElectronFromLocalFit(AppEvent* anEvent) {

  CalibCaloHitColl_ch caloHits;
  if (!CalibCaloHitColl::find(anEvent, caloHits)) {
    if (debugLevel_ > 0)
      std::cout 
        << "-- ElectronFinder - Calibrate calorimeter hits not found"
        << std::endl;
    return AppResult::OK;
  }

  if (caloHits->contents().size() == 0) {
    if (debugLevel_ > 0)
      std::cout	
        << "-- ElectronFinder - No entries in CalibCaloHitColl"
        << std::endl;
    return AppResult::OK;
  }
    
  N3TrackSegmentColl_ch trackSegments;
  if (!N3TrackSegmentColl::find(anEvent, trackSegments)) {        
    if (debugLevel_ > 0)  
      std::cout << "-- ElectronFinder - Tracks not found" << std::endl;
    return AppResult::OK;        
  }
    
  N3GeigerHitColl_ch theGgColl;
  if (!N3GeigerHitColl::find(anEvent, theGgColl)) {
    if (debugLevel_ > 0)
      std::cout << "-- ElectronFinder - Geiger hits not found" << std::endl;
    return AppResult::OK;
  }

  ElectronColl *eColl = new ElectronColl();

  // Loop over all tracks it the event and create the Electron objects
  int trackId = 0;
  for (unsigned int trackId = 0; trackId < trackSegments->contents().size();
       ++trackId) {
    N3TrackSegment trk = trackSegments->contents().at(trackId);
    
    if (trk.indexOfScintillator() < 0) {
      // the track is not associated to any scintillator therefore we 
      // skip it
      continue;
    }

    Electron eCand;

    int calibratedId = 0;
    CalibCaloHitColl::const_iterator calohit = caloHits->contents().begin();
    bool found = false;
   
    while(calohit != caloHits->contents().end() and !found) {
      // look for the calibrated calorimeter hit associated to the raw hit
      found = (calohit->hitId() == trk.indexOfScintillator());
      if (found) {
        eCand.setHitId(calibratedId);
      } else {
        ++calibratedId;
        ++calohit;
      }
    }
    
    if (!found) {
      if (debugLevel_ > 0)
        std::cout << "WARNING - ElectronFinder::event - (Run, Event) = ("
                  << AbsEnv::instance()->runNumber() << ", " 
                  << AbsEnv::instance()->trigNumber() 
                  << ")\nWARNING track "
                  << trackId << " was associated with Calorimeter Hit Id = " << trk.indexOfScintillator()
                  << " - corresponding Calibrated Hit not found "
                  << std::endl;
    } else {

      // references to other collections
      eCand.setTrackId(trackId);
      //    eCand.setHitId(trk.indexOfScintillator());
      eCand.setFirstGeigerHit(trk.geigerHitList()->at(0));

      // these two properties are usefull in filtering candidates, so we promote them
      // to members of the Electron rather than keeping them in the track object
      
      eCand.setIntersectTheFoil((trk.intersectionOnFoil().mag2() > 1e-4) || 
  			      (trk.intersectionOnFoil(true).mag2() > 1e-4));
      eCand.setImpactRegion(trk.impactRegion());
      
      if (eCand.intersectTheFoil()) {
        if (trk.intersectionOnFoil(true).mag2() > 1e-4) {
          // set the vertex as the result of the local fit	
          eCand.setVertex(trk.intersectionOnFoil(true));
        }	else {
          // set the vertex as the result of the global fit
          eCand.setVertex(trk.intersectionOnFoil());
        }
      } else {
        // use the position of the first anode as x,y coordinate of the vertex and the
        // z of the first geiger hit as z of the vertex
        N3GeigerHit ggHit = theGgColl->contents().at(eCand.firstGeigerHit());
        CLHEP::Hep3Vector vertex(ggHit.anodePosition().x(),
                                 ggHit.anodePosition().y(),
                                 ggHit.z());
        eCand.setVertex(vertex);
      }
      
      // beta of the electron
      //CalibCaloHit calohit = caloHits->contents().at(eCand.hitId());
      eCand.setEnergy(calohit->energyDeposit());
      eCand.setDEnergy(calohit->fwhm() * sqrt(eCand.energy()) / 2.3548);
          
      CLHEP::Hep3Vector caloImpactPoint;
      if (trk.intersectionOnScint(true).mag() > 0) {
        caloImpactPoint = trk.intersectionOnScint(true);
      } else {
        caloImpactPoint = trk.intersectionOnScint();
      }
      eCand.setCaloIP(caloImpactPoint);

      double pathLength = trk.distanceAlongTrack(eCand.vertex(), caloImpactPoint);
      eCand.setPathLength(pathLength);
      
      eCand.setMeasTime(calohit->hitTime());
      eCand.setDMeasTime(calohit->electronTimeError());

      eCand.setEnergyLoss(calculateEnergyLoss(eCand, *calohit));

      // Calculate extra time from scintillator impact to PMT - JEM 04/12/13

      // First get block thickness based on types
      double blockThickness;

      if(calohit->iobt() == 0){
        blockThickness = 10.5;     //IN
      } else if (calohit->iobt() == 1){
        if(calohit->fcll() == 0 || calohit->fcll() == 2){
          blockThickness = 11.12;  //EE
        } else if(calohit->fcll() == 1){
          blockThickness = 9.9;    //EC
        }
      } else {
        if(calohit->fcll() == 0){
          blockThickness = 10.0;   //L1
        } else if(calohit->fcll() == 1){
          blockThickness = 10.0;   //L2
        } else if(calohit->fcll() == 2){
          blockThickness = 10.0;   //L3
        } else {
          blockThickness = 10.0;   //L4
        }
      }

      // Calculate extra distance to back of block from centre of front face
      double phi = calohit->blockCenter().phi();
      CLHEP::Hep3Vector delta;

      switch(calohit->iobt()) {
      case 0:
        delta = CLHEP::Hep3Vector(-blockThickness*cos(phi), -blockThickness*sin(phi), 0);
        break;
      case 1:
        delta = CLHEP::Hep3Vector( blockThickness*cos(phi),  blockThickness*sin(phi), 0);
        break;
      case 2:
        delta = CLHEP::Hep3Vector( 0, 0, -blockThickness);
        break;
      case 3:
        delta = CLHEP::Hep3Vector( 0, 0, blockThickness);
        break;
      }

      // Calculate distance from hit position (on front face) to centre of back of block and then add light guide
      double scintToPMTDist = (trk.intersectionOnScint(true) - (calohit->blockCenter() + delta)).mag() + 6.;
      eCand.setScintToPMTTime(scintToPMTDist/(physics::c/10));

      eColl->add(eCand);
    }
  }
  ElectronColl_ch handle(eColl);
  if ((anEvent->append(handle)).is_null()) {
    std::cout 
      << " ERROR - ElectronFinder - error loading collection of electrons "
      << std::endl;
    return AppResult::ERROR;
  }
}

AppResult ElectronFinder::event(AppEvent *anEvent) {
  if (useLocalFit_) {
    return createElectronFromLocalFit(anEvent);
  } else {
    return createElectronFromGlobalFit(anEvent);
  }
}

AppResult ElectronFinder::endRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult ElectronFinder::endJob(AppEvent *aJob) {
  return AppResult::OK;
}

//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------

double ElectronFinder::calculateEnergyLoss(Electron e, CalibCaloHit hit) {
  // This code has been copied from the implementation in NAT++
  // N3AnaBase/src/tof_tools.cc
  // Original code from Filipova's was implemented in nemoa.car in
  // FUNCTION TK_ENERGY

  double deltaE = 0.;
  double trackLength = e.pathLength();
  double energy = e.energy()*1000;  // Convert Energy to keV for formula (JEM 23/12/12)
  
  if ( hit.iobt() <= 1 )
    {
      const double c  = 0.475;
      const double h1 = 0.145e-5;
      const double h2 = 6490.;
      const double a1 = 5630.;
      const double a2 = 134.;
      const double a3 = 0.404;
	
      deltaE = c*trackLength + ( a1 - a3 * ( trackLength - a2 ) * ( trackLength - a2 ) ) / energy
	+ ( h1 * energy ) * ( h1 * energy ) / ( 1. + energy / h2 );
    }
	
  if ( hit.iobt() >= 2 )
    {
      if (trackLength < 40.) trackLength = 40;
	
      const double c = 0.326;
      const double h1 = 0.2e-5;
      const double h2 = 4660.;
      const double a1 = 1800.;
      const double a2 = 27.;
      const double c0 = 15.8;
	
      deltaE = c0 + c*trackLength + ( a1 + a2*trackLength ) / energy
	+ ( h1 * energy ) * ( h1 * energy ) / ( 1. + energy / h2 );
    }
	
  return deltaE/1000.0;  // Change back to MeV (JEM 23/12/12)
}
