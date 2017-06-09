//
//  TrueVertexLocation.cpp
//
//  Created by James Mott on 12/01/17
//  

// Module declaration
#include "JEM_Analysis/TrueVertexLocation.h"

// Nemo Modules
#include "NemoMods/RunStatusController.h"

// Hereward modules
#include "Hereward/SuperNemoData/TrueVertexColl.h"
#include "Hereward/SuperNemoData/TrueParticleColl.h"
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
TrueVertexLocation::TrueVertexLocation(const std::string theName,
                               const std::string theDescription) :
AppModule(theName, theDescription) {
  execType_ = App_module;
  sectorInfo_ = new SectorData();
}

TrueVertexLocation::~TrueVertexLocation() {
  delete sectorInfo_;
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult TrueVertexLocation::beginJob(AppEvent* aJob) {

  RootOutputManager* nTupleManager = RootOutputManager::instance();

  // Create branches for storing data for accepted events
  nTupleManager->addTree(name());
  nTupleManager->addBranch(name(), "b_trueVertexR", &trueVertexR_, "trueVertexR/D");
  nTupleManager->addBranch(name(), "b_trueVertexZ", &trueVertexZ_, "trueVertexZ/D");
  nTupleManager->addBranch(name(), "b_trueVertexSector", &trueVertexSector_, "trueVertexSector/D");
  nTupleManager->addBranch(name(), "b_trueVertexLocation", &trueVertexLocation_, "trueVertexLocation/I");

  // Initialise counters that will keep track of number of events that pass each cut
  TotalNumEvents_    = 0; 

  return AppResult::OK;    
}

AppResult TrueVertexLocation::beginRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult TrueVertexLocation::event(AppEvent* anEvent) {

  // Get true vertex collection
  TrueVertexColl_ch theTrueVertexColl;
  TrueVertexColl::TrueVertexList trueVertexList;
  if (TrueVertexColl::find(anEvent, theTrueVertexColl)){
    trueVertexList = theTrueVertexColl->contents();
  } else {
    std::cout << "-- TrueVertexLocation - True Vertex info not found" << std::endl;
    return AppResult::OK;
  }

  // Output counter to screen to keep tabs on how far program's got
  if(TotalNumEvents_ % 50000 == 0){std::cout << "Processing event " << TotalNumEvents_ << std::endl;}
  TotalNumEvents_++;

  // Store true vertex information
  CLHEP::Hep3Vector trueVertex = trueVertexList.at(0).position();
  trueVertexR_ = TMath::Sqrt(trueVertex.x()*trueVertex.x() +  trueVertex.y()*trueVertex.y()); 
  trueVertexZ_ = trueVertex.z();
  trueVertexSector_ = sectorInfo_->sectorNumber(trueVertex); 

  // Vertex Location (0 - SeOld, 1 - SeNew)
  SourceType source = sectorInfo_->sourceOfVertex(trueVertex);
  if (source == SourceType::SeOld)      trueVertexLocation_ = 0;
  else if (source == SourceType::SeNew) trueVertexLocation_ = 1;
  else                                  trueVertexLocation_ = -1;

  // Save everything in branch and close App
  RootOutputManager::instance()->capture(name());

  return AppResult::OK;
}


AppResult TrueVertexLocation::endRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult TrueVertexLocation::endJob(AppEvent* aJob) {

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

  // Write file with the numbers of events that passed each cut
  std::ofstream outfile("JobSummary.txt");

  if (outfile.is_open()) {
  outfile << "======================================================================================" << std::endl;
  outfile << "                     TrueVertexLocation End of Job Run Time information                     " << std::endl;
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
  outfile << "                      TrueVertexLocation End of Job Event Cuts Summary                      " << std::endl;
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
  outfile << std::endl;
  outfile << "======================================================================================" << std::endl;
  outfile << "                     TrueVertexLocation End of Job Radon information                          " << std::endl;
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
    std::cout << "TrueVertexLocation::endJob : could not write the report" << std::endl;
    return  AppResult::ERROR;
  }

  return AppResult::OK;
}
