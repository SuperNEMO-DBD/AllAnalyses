//
//  RunStatusController.cpp
//
//  Created by Stefano Torre on 23/01/12.
//

#include <iostream>
#include "NemoMods/RunStatusController.h"
#include "Hereward/SuperNemoData/EventHeader.h"
#include "NemoObjects/NemorHeader.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <exception>
#include <unistd.h>
#include <math.h>

RunStatusController* RunStatusController::runControl_ = 0;

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
RunStatusController::RunStatusController(const std::string theName, 
                                         const std::string theDescription) :
  AppModule(theName, theDescription),
  useListFromFile_(false),
  currentRunIsAccepted_(false),
  useN3Db_(true),
  loadBetaBetaRunSummary_(false),
  isConnected_(false),
  currentRun_(-1),
  lastRun_(-1),
  useRecoRunList_(false),
  recoRunListFileName_("RecoRunList.lst"),
  port_(3306), 
  serverName_("db1.hep.ucl.ac.uk"), 
  dbName_("NEMO"),
  userName_("nemo"),
  password_("betabeta"),
  correctBadDeadTimes_(false) {

  runControl_              = this;
  runListFileName_         = "customRunList.rlist";
  
  // 09/10/2012 - ST
  runTable_                = new RunSummaryTable();
  assignedEventsFileName_  = "RecoAssignedEvents.txt";
  useAssignedEventsFile_   = false;
  maxConnectinAttempts_    = 10;
  //

  if (useN3Db_) {
    n3db_ = N3DbInterfaceModule::instance();
  } else {
    db_ = NemoDataBaseManager::instance();
  }

  // building up the dictionary of run statuses
  // the code here below rewrites the definitions that can be foudn in 
  // Bool_t ana10::RunList(int runnumber, Int_t &timerun)    
  RunStatusClassCondition aCondition;
    
  // GOOD_RUN = Status 1
  aCondition.statusId = GOOD_RUN;
  aCondition.includedStates.push_back(1);
  addRunStatusCondition(aCondition);
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();
  // OK_RUN = Possibly good runs, exclude statuses 1,2,5,4,1000,6,100000,
  // 10000,20000,100000000,1000000000
  aCondition.statusId = OK_RUN;
  aCondition.excludedStates.push_back(0);
  aCondition.excludedStates.push_back(1);
  aCondition.excludedStates.push_back(2);
  aCondition.excludedStates.push_back(5);
  aCondition.excludedStates.push_back(6);
  aCondition.excludedStates.push_back(100000);
  aCondition.excludedStates.push_back(4);
  aCondition.excludedStates.push_back(1000);
  aCondition.excludedStates.push_back(10000);
  aCondition.excludedStates.push_back(20000);
  aCondition.excludedStates.push_back(100000000);
  aCondition.excludedStates.push_back(1000000000);
  addRunStatusCondition(aCondition);
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();
  // NOAIR_RUN = Ventillation off (status 6 & 100000)
  aCondition.statusId = NOAIR_RUN;
  aCondition.includedStates.push_back(6);
  aCondition.includedStates.push_back(100000);
  aCondition.includedStates.push_back(300000);
  addRunStatusCondition(aCondition);
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();
  // AFTER_EC_RUN = After absolute calibration (4 & 1000)
  aCondition.statusId = AFTER_EC_RUN;
  aCondition.includedStates.push_back(4);
  aCondition.includedStates.push_back(1000);
  addRunStatusCondition(aCondition);
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();
  // HV_RUN = Runs with HV problems, statuses 5, 10000, 20000, 100000000, 
  // 1000000000
  aCondition.statusId = HV_RUN;
  aCondition.includedStates.push_back(5);
  aCondition.includedStates.push_back(10000);
  aCondition.includedStates.push_back(20000);
  aCondition.includedStates.push_back(100000000);
  aCondition.includedStates.push_back(1000000000);
  addRunStatusCondition(aCondition);
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();
  // STANDARD_RUN = runs from starndard runlist, decided at Feb'07 Orsay 
  // analysis meeting. See meeting minutes.
  aCondition.statusId = STANDARD_RUN;
  aCondition.excludedStates.push_back(0);
  aCondition.excludedStates.push_back(100);
  aCondition.excludedStates.push_back(100000000);
  aCondition.excludedStates.push_back(1000000000);
  aCondition.excludedStates.push_back(3);
  aCondition.excludedStates.push_back(7);
  aCondition.excludedStates.push_back(8);
  aCondition.excludedStates.push_back(100000);
  aCondition.excludedStates.push_back(200000);
  aCondition.excludedStates.push_back(300000);
  aCondition.excludedStates.push_back(6);
  aCondition.excludedStates.push_back(2000000);
  aCondition.excludedStates.push_back(3000000);
  addRunStatusCondition(aCondition);
    
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();    
  // runs for bb0nu analysis
  aCondition.statusId = BB0NU_RUN;
  aCondition.includedStates.push_back(1);
  aCondition.includedStates.push_back(2);
  aCondition.includedStates.push_back(10);
  aCondition.includedStates.push_back(200002);
  aCondition.includedStates.push_back(200010);
  aCondition.includedStates.push_back(200001);
  addRunStatusCondition(aCondition);
    
  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();    
  // ALL_BUT_BAD_RUN = all except statuses 0, 6, 7, 100000
  aCondition.statusId = ALL_BUT_BAD_RUN;
  aCondition.excludedStates.push_back(0);
  aCondition.excludedStates.push_back(6);
  aCondition.excludedStates.push_back(7);
  aCondition.excludedStates.push_back(100000);
  addRunStatusCondition(aCondition);

  aCondition.includedStates.clear();
  aCondition.excludedStates.clear();
  // BI207_RUNS
  aCondition.statusId = BI207_RUNS;
  aCondition.includedStates.push_back(0);
  aCondition.includedStates.push_back(200000);
  addRunStatusCondition(aCondition);
    
  std::cout << " RunStatusController::beginJob " 
	    << ": defined dictionary of run statuses with "
	    << runStatesDictionary_.size() << " entries " << std::endl;
    
  // building up the dictionary of phases
  // the code here below rewrites the definitions that can be foudn in 
  // Bool_t ana10::RunList(int runnumber, Int_t &timerun)    
  DataTakingPhase aPhase;
    
  //Phase 1 0nu data
  aPhase.phaseName = "P1_0nu";
  aPhase.phaseId = P1_0nu;
  DataTakingPhase::RunRange aRange(-1, 3400);
  aPhase.runRanges.push_back(aRange);
  aRange = DataTakingPhase::RunRange(3553, 3566);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
    
  aPhase.runRanges.clear();
  // Phase 1 data
  aPhase.phaseName = "P1";
  aPhase.phaseId = P1;
  aRange = DataTakingPhase::RunRange(-1, 3396);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
 
  aPhase.runRanges.clear();
  // Phase 2 data
  aPhase.phaseName = "P2";
  aPhase.phaseId = P2;
  aRange = DataTakingPhase::RunRange(3395, 10000);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
   
  aPhase.runRanges.clear();
  //Phase 2 period a) from Oct 2004 to 22 may 2006
  aPhase.phaseName = "P2a";
  aPhase.phaseId = P2a;
  aRange = DataTakingPhase::RunRange(3395, 4859);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
    
  aPhase.runRanges.clear();
  // Phase 2 period b) from 22 may 2006 to 31 Dec 2007
  aPhase.phaseName = "P2b";
  aPhase.phaseId = P2b;
  aRange = DataTakingPhase::RunRange(4858, 5469);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
    
  aPhase.runRanges.clear();
  // Phase 2 period for 0nu search
  aPhase.phaseName = "P2_0nu";
  aPhase.phaseId = P2_0nu;
  aRange = DataTakingPhase::RunRange(3407, 5469);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
    
  //Phase3 , 2007, 2008, data
  aPhase.runRanges.clear();
  // Phase 2 period for 0nu search
  aPhase.phaseName = "P3";
  aPhase.phaseId = P3;
  aRange = DataTakingPhase::RunRange(5468, 7921);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);

  // Bi207 - Run Set 1
  aPhase.runRanges.clear();
  aPhase.phaseName = "Bi207_Runs_1";
  aPhase.phaseId = Bi207_Runs_1;
  aRange = DataTakingPhase::RunRange(2942, 2946);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
   
  // Bi207 - Run Set 2
  aPhase.runRanges.clear();
  aPhase.phaseName = "Bi207_Runs_2";
  aPhase.phaseId = Bi207_Runs_2;
  aRange = DataTakingPhase::RunRange(2945, 2948);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
   
  // Bi207 - Run Set 3
  aPhase.runRanges.clear();
  aPhase.phaseName = "Bi207_Runs_3";
  aPhase.phaseId = Bi207_Runs_3;
  aRange = DataTakingPhase::RunRange(3188, 3194);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
   
  // Bi207 - Run Set 4
  aPhase.runRanges.clear();
  aPhase.phaseName = "Bi207_Runs_4";
  aPhase.phaseId = Bi207_Runs_4;
  aRange = DataTakingPhase::RunRange(4785, 4794);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
       
  // all runs are being processed
  aPhase.runRanges.clear();
  aPhase.phaseName = "AllRuns";
  aPhase.phaseId = AllRuns;
  aRange = DataTakingPhase::RunRange(-1,10000);
  aPhase.runRanges.push_back(aRange);
  addPhase(aPhase);
    
  std::cout << " RunStatusController::beginJob " 
	    << ": defined dictionary data taking phases with  "
	    << phasesDictionary_.size() << " entries " << std::endl;
  std::map<PhaseId, DataTakingPhase>::iterator it= phasesDictionary_.begin();
  while(it != phasesDictionary_.end()) {
    std::cout << it->second;
    ++it;
  }
  std::cout << std::endl;

  addRequiredDataTakingPhase(AllRuns);

  std::cout << " Required phases : \n";
  for (unsigned int i = 0; i < requiredPhases_.size(); ++i) {
    std::cout << phasesDictionary_[requiredPhases_[i]];
  }
  std::cout << std::endl;

  if (loadBetaBetaRunSummary_) {
    loadBetaBetaRunSummary();
  }
}

RunStatusController::~RunStatusController() {
  runStatesDictionary_.clear();
  phasesDictionary_.clear();
  requiredRunStates_.clear();
  requiredPhases_.clear();
  runInfos_.clear();
  recoRunInfos_.clear();
  // 09/10/2012 - ST
  delete runTable_;
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult RunStatusController::beginJob(AppEvent *aJob) {

  // report on the required phases
  std::cout << std::string(80, '*') << '\n';
  std::cout << "*  " 
	    << std::setw(76) 
	    << std::left <<"RunStatusController - begin job checks"
	    << "*\n"
	    << "*" << std::string(78, ' ') << "*" << std::endl;
  std::cout << "*  "
	    << std::setw(76) << "******* Required phases :" <<  "*\n";
  for (unsigned int i = 0; i < requiredPhases_.size(); ++i) {
    std::cout << "* " 
	      << phasesDictionary_[requiredPhases_[i]] << std::endl;
  }
  std::cout << "*" << std::endl;

  if (useListFromFile_) {
    std::cout << "******* loading list of runs from file\n"
	      << "*    filename : " << runListFileName_  
	      << std::endl;
    std::ifstream inputListFile(runListFileName_.c_str());
        
    if (inputListFile.is_open()) {
      while (!inputListFile.eof()) {
      	int runNumber;
      	inputListFile >> runNumber;
      	listOfRuns_.push_back(runNumber);
      }
      inputListFile.close();
    } else {
      std::cout << "RunStatusController::beginJob "
        << ": could not open requested run list "
        << inputListFile << std::endl;
      return AppResult::ERROR;
    }

    std::cout << "*    read " << listOfRuns_.size() << " runs " << std::endl; 
  }   

  if (useRecoRunList_){
    recoRunInfos_.clear();
    std::ifstream recoList(recoRunListFileName_.c_str());
    std::string line;
    if (recoList.is_open()){
      getline (recoList,line);
      int runnum;
      while(recoList >> runnum){
        RunInfo recoRun;
        recoRun.number = runnum;
        recoList 
          >> recoRun.length 
          >> recoRun.generatedEvents 
          >> recoRun.status 
          >> recoRun.accepted;
        recoRunInfos_[recoRun.number] = recoRun;
      }
      recoList.close();
    } else {
      std::cout 
        << "RunStatusController::beginJob : Unable to open Reco RunList File" 
        << std::endl;
      return AppResult::ERROR;
    }
  }
 
  if (loadBetaBetaRunSummary_) {
    std::cout << "*  "
	      << std::setw(76) << "******* Load BetaBetaRunSummaryTable :" <<  "*\n";
    loadBetaBetaRunSummary();
  }

  if (useAssignedEventsFile_) {
    std::cout << "*  "
	      << std::setw(76) << "******* List of events assigned per run number :" <<  "*\n";
    readEventsAssignedPerEvents();
  }

  std::cout << std::string(80, '*') << std::endl;

  return AppResult::OK;
}

AppResult RunStatusController::beginRun(AppEvent *aRun) {
  EventRecord::ConstIterator
    evtHeader(aRun, StorableObject::SelectByClassName("EventHeader"));
  if (!evtHeader.is_valid()) {
    std::cout << " Error Accessing the EventHeader" << std::endl;
    aRun->listObjects();
    return AppResult::ERROR;
  }     
  EventHeader_ch eventHeader(evtHeader);
  currentRun_ = eventHeader->runNumber();

  isMC = eventHeader->mcFlag(); // 24/10/13 - CV

  // 1) Check if this is the first time we encounter this run and if needed 
  // create a record for it
  bool firstTimeEncountered = false;
  if (runInfos_.find(currentRun_) == runInfos_.end()) {
    RunInfo thisRunRecord;
    firstTimeEncountered = true;
    thisRunRecord.number = currentRun_;
    if (useN3Db_) {
      thisRunRecord.status   = n3db_->runStatus();
      thisRunRecord.length   = n3db_->runTime();
      thisRunRecord.activity = n3db_->runActivity();
    } else {
      thisRunRecord.status = db_->runSummaryData()->runStatus(currentRun_);
      thisRunRecord.length = db_->runSummaryData()->runTime(currentRun_);
    }
    thisRunRecord.generatedEvents = eventHeader->numberOfGeneratedEvents();
    thisRunRecord.observedEvents = 0;

    // 09/10/2012 - ST
    if (loadBetaBetaRunSummary_) {
      if (runTable_->deadTime(currentRun_) == -1 or
      	  runTable_->deadTime(currentRun_) == 0) {
      	if (!correctBadDeadTimes_){
          // we do the correction below 
      	  std::cout << " WARNING Deadtime for run " << currentRun_ 
      		    << " is " << runTable_->deadTime(currentRun_)
      		    << " no deadtime will be calculated " << std::endl;
      	}
      	thisRunRecord.deadTime = 0;
      } else {
        thisRunRecord.deadTime = 
      	  (runTable_->deadTime(currentRun_) * 
           runTable_->numEvents(currentRun_) + 55) /
          1e6; // us -> s
      }
    } else {
      thisRunRecord.deadTime = -1;
    }
    
    // 16/10/2012 - JM: If deadtime is 0, then Victor says it's because something
    // went wrong with the Run Stop DAQ.  He believes that these runs are OK to be
    // used.  Therefore we set this deadtime to be equal to the modal deadtime fraction
    // which shouldn't be too bad for a small correction to a small correction.
    // We make a similar assumption for those where the dead time fraction is greater
    // than 10%.
    if (loadBetaBetaRunSummary_ and 
        correctBadDeadTimes_ and 
        (thisRunRecord.deadTime == 0 or 
          thisRunRecord.deadTime/thisRunRecord.length > 0.1)) {
      thisRunRecord.deadTime = 0.0098 * thisRunRecord.length;
    }

    // ST: at the begin of the job we read the number of events assigned to each 
    //     run by NEMOR and crate a run record in the runInfos_ map. If this run
    //     is not present in the map, then it means that either the run was not 
    //     present in the list provided or that no list was provided at all.
    thisRunRecord.assignedEvents = -1;
    
    runInfos_.insert(std::pair<int, RunInfo>
		     (currentRun_, thisRunRecord));
  } else if (useAssignedEventsFile_) {
    // ST: the run is in the runInfos_ map, however it may be added there at the 
    //     beginning of the jobs because NEMOR assigned events to it and not
    //     but this could still be the first time we encounter this run
    if (runInfos_[currentRun_].observedEvents == -1) {
      firstTimeEncountered = true;
      if (useN3Db_) {
      	runInfos_[currentRun_].status   = n3db_->runStatus();
      	runInfos_[currentRun_].length   = n3db_->runTime();
      	runInfos_[currentRun_].activity = n3db_->runActivity();
      } else {
      	runInfos_[currentRun_].status = db_->runSummaryData()->runStatus(currentRun_);
      	runInfos_[currentRun_].length = db_->runSummaryData()->runTime(currentRun_);
      }
      runInfos_[currentRun_].generatedEvents = eventHeader->numberOfGeneratedEvents();
      runInfos_[currentRun_].observedEvents = 0;

      if (loadBetaBetaRunSummary_) {
      	if (runTable_->deadTime(currentRun_) == -1 or
      	    runTable_->deadTime(currentRun_) == 0) {
      	  if(!correctBadDeadTimes_){
      	    std::cout << " WARNING Deadtime for run " << currentRun_ 
      		      << " is " << runTable_->deadTime(currentRun_)
      		      << " no deadtime will be calculated " << std::endl;
      	  }
      	  runInfos_[currentRun_].deadTime = 0;
      	} else {
      	  runInfos_[currentRun_].deadTime = 
      	    (runTable_->deadTime(currentRun_) * runTable_->numEvents(currentRun_)+ 55) /
      	    1e6; // us -> s
      	} 
      }
      // 16/10/2012 - JM: Correct deadtimes as described above
      if ( loadBetaBetaRunSummary_ and 
           correctBadDeadTimes_ and 
	         (runInfos_[currentRun_].deadTime == 0 or 
            runInfos_[currentRun_].deadTime/runInfos_[currentRun_].length > 0.1)){
      	runInfos_[currentRun_].deadTime = 0.0098 * runInfos_[currentRun_].length;
      }
    }
  }

  if (firstTimeEncountered) {
    // 2) check if the run belongs to a requested phase
    bool goodPhase = false;
    std::vector<PhaseId>::iterator phaseIter = requiredPhases_.begin();
    while (!goodPhase and phaseIter != requiredPhases_.end()) {
      goodPhase |= checkPhase(*phaseIter);
      phaseIter++;
    }
        
    // 3) check if the run status is included in the requested statuses
    bool goodStatus = false;
    std::vector<RunStatusClass>::iterator 
      statusIter = requiredRunStates_.begin();
    while (!goodStatus and statusIter != requiredRunStates_.end()) {
      goodStatus |= checkStatus(*statusIter);
      statusIter++;
    }
        
    // 4) check if the run is included in the list provided by the file
    bool runInList = false;
    if (useListFromFile_) {
      runInList = (find(listOfRuns_.begin(), listOfRuns_.end(), currentRun_)
		   != listOfRuns_.end());
    } else {
      runInList = true;
    }
        
    currentRunIsAccepted_ = goodPhase && goodStatus && runInList;
    runInfos_[currentRun_].accepted = currentRunIsAccepted_;
  } else {
    currentRunIsAccepted_ = runInfos_[currentRun_].accepted;
    runInfos_[currentRun_].generatedEvents +=
      eventHeader->numberOfGeneratedEvents();
  }

  // JM 18/5/13 - Check whether we've missed an entry in the RunInfos_ table.  These are runs
  // that were assigned events in MC which haven't made it through the reconstruction (usually as a crate is 
  // missing or suchlike) and should all have observedEvents = -1.
  if(lastRun_ < currentRun_){
    std::map<int, RunInfo>::const_iterator summaryIter;
    if(lastRun_ == -1){
      summaryIter = runInfos_.begin();
    } else {
      summaryIter = runInfos_.find(lastRun_);
    }

    for (summaryIter; summaryIter != runInfos_.find(currentRun_); summaryIter++) {

      if (summaryIter->second.observedEvents == -1) {
        int missingRun = summaryIter->second.number;

      	// 1) Load data from N3Db, load deadtime and correct if required
      	if (useN3Db_) {
      	  N3DbInterfaceModule* n3dbtmp_ = N3DbInterfaceModule::instance();
      	  n3dbtmp_->loadRunData(missingRun);
      	  runInfos_[missingRun].status   = n3dbtmp_->runStatus();
      	  runInfos_[missingRun].length   = n3dbtmp_->runTime();
      	  runInfos_[missingRun].activity = n3dbtmp_->runActivity();
      	} else {
      	  runInfos_[missingRun].status = db_->runSummaryData()->runStatus(missingRun);
      	  runInfos_[missingRun].length = db_->runSummaryData()->runTime(missingRun);
      	}
      	runInfos_[missingRun].observedEvents = 0;

      	if (loadBetaBetaRunSummary_) {
      	  if (runTable_->deadTime(missingRun) == -1 or runTable_->deadTime(missingRun) == 0) {
      	    if(!correctBadDeadTimes_){
      	      std::cout 
                << " WARNING Deadtime for run " << missingRun 
          			<< " is " << runTable_->deadTime(missingRun)
          			<< " no deadtime will be calculated " 
                << std::endl;
      	    }
      	    runInfos_[missingRun].deadTime = 0;
      	  } else {
      	    runInfos_[missingRun].deadTime = 
      	      ( runTable_->deadTime(missingRun) * 
                runTable_->numEvents(missingRun)+ 55) / 1e6; // us -> s
      	  } 
      	}

      	if ( loadBetaBetaRunSummary_ and 
             correctBadDeadTimes_ and 
      	     ( runInfos_[missingRun].deadTime == 0 or 
               runInfos_[missingRun].deadTime/runInfos_[missingRun].length > 0.1)) {
      	  runInfos_[missingRun].deadTime = 0.0098 * runInfos_[missingRun].length;
      	}

      	// 2) check if the run belongs to a requested phase
      	bool goodPhase = false;
      	std::vector<PhaseId>::iterator phaseIter = requiredPhases_.begin();
      	while (!goodPhase and phaseIter != requiredPhases_.end()) {
      	  goodPhase |= checkPhase(*phaseIter);
      	  phaseIter++;
      	}
        
      	// 3) check if the run status is included in the requested statuses
      	bool goodStatus = false;
      	std::vector<RunStatusClass>::iterator statusIter = requiredRunStates_.begin();
      	while (!goodStatus and statusIter != requiredRunStates_.end()) {
      	  goodStatus |= checkStatus(*statusIter);
      	  statusIter++;
      	}
        
      	// 4) check if the run is included in the list provided by the file
      	bool runInList = false;
      	if (useListFromFile_) {
      	  runInList = (find(listOfRuns_.begin(), listOfRuns_.end(), missingRun) != listOfRuns_.end());
      	} else {
      	  runInList = true;
      	}

      	runInfos_[missingRun].accepted = goodPhase && goodStatus && runInList;
      }
    }
  }

  lastRun_ = currentRun_;

  return AppResult::OK;
}


AppResult RunStatusController::event(AppEvent *anEvent) {
  runInfos_[currentRun_].observedEvents++;      
  return AppResult::OK;
}

AppResult RunStatusController::endRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult RunStatusController::endJob(AppEvent *aJob) {  
  // at the end of the job we want to clear the summary list and print a 
  // report summarizing all the relevant informations
  std::ofstream report("RunStatusControllerResult.log");
  if (report.is_open()) {
    report 
      << std::setw(7) << std::internal << "Number"
      << std::setw(7) << std::internal << "Length"
      << std::setw(12) << std::internal << "DeadTime"
      << std::setw(12) << std::internal << "Activity"
      << std::setw(12) << std::internal << "ObsEvts"
      << std::setw(12) << std::internal << "AssgnEvts"
      << std::setw(12) << std::internal << "Status"
      << std::setw(9) << std::internal << "Accepted"
      << std::endl;
    std::map<int, RunInfo>::iterator iter = runInfos_.begin();
    while (iter != runInfos_.end()) {
      RunInfo entry = iter->second;
      report 
      	<< std::setw(7) << std::right << entry.number 
      	<< std::setw(7) << std::right << entry.length 
      	<< std::setw(12) << std::right << entry.deadTime
        << std::setw(12) << std::right << entry.activity
      	<< std::setw(12) << std::right << entry.observedEvents 
      	<< std::setw(12) << std::right << entry.assignedEvents 
      	<< std::setw(12) << std::right << entry.status 
      	<< std::setw(9) << std::right << entry.accepted 
      	<< std::endl;
      ++iter;
    }
  } else {
    std::cout 
      << "RunStatusController::endJob "
      << ": could not write the report " 
      << std::endl;
    return  AppResult::ERROR;
  }

  // Same as above but in XML and without the activity [CV 14/11/13]
  std::ofstream reportXML("RunStatusControllerResult.xml");
  if (reportXML.is_open()) {
    reportXML << "<?xml version=\"1.0\"?>" << std::endl;
    reportXML << "<runStatCtrl>" << std::endl;
    
    std::map<int, RunInfo>::iterator iter = runInfos_.begin();
    while (iter !=  runInfos_.end()){
      RunInfo entry = iter->second;
      reportXML 
        << "  <run>\n"
        << "    <number>" << entry.number << "</number>\n"
        << "    <length>" << entry.length << "</length>\n"
        << "    <deadTime>" << entry.deadTime << "</deadTime>\n"
        << "    <activity>" << entry.activity << "</activity>\n"
        << "    <observedEvents>" << entry.observedEvents << "</observedEvents>\n"
        << "    <assignedEvents>" << entry.assignedEvents << "</assignedEvents>\n"
        << "    <status>" << entry.status << "</status>\n"
        << "    <accepted>" << entry.accepted << "</accepted>\n"
        << "  </run>" << std::endl;
      ++iter;
    }
    reportXML << "</runStatCtrl>" << std::endl;
  }  else {
    std::cout << "RunStatusController::endJob "
	      << ": could not write the report " 
	      << std::endl;
    return  AppResult::ERROR;
  }

  // And a few more useful numbers in a separate file [CV 14/11/13]
  std::ofstream jobSumXML("JobSummary.xml");
  if (jobSumXML.is_open()){
    jobSumXML << "<?xml version=\"1.0\"?>" << std::endl;
    jobSumXML << "<jobSummary>" << std::endl;
    
    // Don't want times to be rounded
    jobSumXML << std::setprecision(10);

    // MC flag
    if (isMC) {
      jobSumXML << "  <MC/>" << std::endl;
      // Round max generated events to nearest 100.
      jobSumXML << "  <totGenEvents>" << (long) (100.0*floor(((double)maxGeneratedEvents())/100.0+0.5)) << "</totGenEvents>" << std::endl;

      jobSumXML << "  <totAssignedEvents>" << totalAssignedEvents() << "</totAssignedEvents>" << std::endl;
      jobSumXML << "  <totAccAssignedEvents>" << totalAccAssignedEvents() << "</totAccAssignedEvents>" <<std::endl;

    } else {
      jobSumXML << "  <Data/>" << std::endl;
    }
    
    jobSumXML 
      << "\n\n <!-- Processed Data -->\n"
      << "  <totalRunTime>" << totalRunTime() << "</totalRunTime>\n"
      << "  <totalAcceptedRunTime>" << totalAccRunTime() << "</totalAcceptedRunTime>\n"
      << "\n\n <!-- Reconstruction Input -->\n"
      << "  <totalRecoTime>" << totalRecoTime() << "</totalRecoTime>\n"
      << "  <totalAcceptedRecoTime>" << totalAccRecoTime() << "</totalAcceptedRecoTime>\n"
      << "\n\n <!-- Dead Time Info - Processed Data -->\n"
      << "  <totalDeadTime>" << totalDeadTime() << "</totalDeadTime>\n"
      << "  <totalAcceptedDeadTime>" << totalAccDeadTime() << "</totalAcceptedDeadTime>\n"
      << "\n\n <!-- Phase 1 -->\n"
      << "  <recoAcceptedRunTimeP1>" << totalAccRecoTime("P1") << "</recoAcceptedRunTimeP1>\n"
      << "  <totalAcceptedRunTimeP1>" << totalAccRunTime("P1") << "</totalAcceptedRunTimeP1>\n"
      << "  <totalAcceptedDeadTimeP1>" << totalAccDeadTime("P1") << "</totalAcceptedDeadTimeP1>\n"
      << "\n\n <!-- Phase 2 -->\n"
      << "  <recoAcceptedRunTimeP2>" << totalAccRecoTime("P2") << "</recoAcceptedRunTimeP2>\n"
      << "  <totalAcceptedRunTimeP2>" << totalAccRunTime("P2") << "</totalAcceptedRunTimeP2>\n"
      << "  <totalAcceptedDeadTimeP2>" << totalAccDeadTime("P2") << "</totalAcceptedDeadTimeP2>\n";

    jobSumXML << "</jobSummary>" << std::endl;

  }  else {
    std::cout << "RunStatusController::endJob "
	      << ": could not write the report " 
	      << std::endl;
    return  AppResult::ERROR;
  }

  return AppResult::OK;
}

//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------
const RunStatusController* RunStatusController::instance() {
  if (runControl_ == 0)
    runControl_ = new RunStatusController();
  return runControl_;
}

void RunStatusController::addPhase(DataTakingPhase aPhase) { 
  phasesDictionary_.insert(std::pair<PhaseId, DataTakingPhase>
			   (aPhase.phaseId, aPhase));
}

void RunStatusController::addRunStatusCondition(RunStatusClassCondition aCondition) {
  runStatesDictionary_.insert(std::pair<RunStatusClass, RunStatusClassCondition>
			      (aCondition.statusId, aCondition));
}

void RunStatusController::addRequiredRunStatus(RunStatusClass aRunClass) {
  requiredRunStates_.push_back(aRunClass);
}

void RunStatusController::addRequiredDataTakingPhase(PhaseId aPhaseId) {
  std::vector<PhaseId>::iterator entryPos = 
    find(requiredPhases_.begin(), requiredPhases_.end(), AllRuns);
    
  if (entryPos != requiredPhases_.end()) {
    requiredPhases_.erase(entryPos);
  }
  requiredPhases_.push_back(aPhaseId);
}

void RunStatusController::removeDataTakingPhase(PhaseId aPhaseId) {
  std::vector<PhaseId>::iterator iter =
    find(requiredPhases_.begin(), requiredPhases_.end(), aPhaseId);
    
  if (iter != requiredPhases_.end()) {
    requiredPhases_.erase(iter);
  }
}

void RunStatusController::removeRequiredRunStatus(RunStatusClass aRunClass) {
  std::vector<RunStatusClass>::iterator iter =
    find(requiredRunStates_.begin(), requiredRunStates_.end(), aRunClass);
    
  if (iter != requiredRunStates_.end()) {
    requiredRunStates_.erase(iter);
  }
}

bool RunStatusController::checkPhase(RunStatusController::PhaseId aPhase) {        
  DataTakingPhase thisPhase = phasesDictionary_[aPhase];
  bool result = false;
  std::vector<DataTakingPhase::RunRange>::iterator rangeIter =
    thisPhase.runRanges.begin();
    
  while (!result and rangeIter != thisPhase.runRanges.end()) {
    result |= ((currentRun_ > (*rangeIter).firstRun) &&
	       (currentRun_ < (*rangeIter).lastRun));
    ++rangeIter;
  }   
  return result;
}

bool RunStatusController::checkStatusBits(int runStatus, int aStatus) {
  // this code has been copied from rootant pmstatus.C CheckStatus(int, int)
  // checks if the runStatus contains the aStatus
  if (aStatus < 10) {
    return runStatus == aStatus;
  } else {
    while (aStatus >= 10) {
      aStatus = aStatus/10;
      runStatus = runStatus/10;
      if (aStatus < 10) {
      	return aStatus == runStatus%10;
      }
    }
  }
}

bool RunStatusController::checkStatus(RunStatusController::RunStatusClass aStatus) {
  RunStatusClassCondition thisStatus = runStatesDictionary_[aStatus];

  // 1) Make sure that status definition only has included or excluded states and
  // not both
  if(thisStatus.includedStates.size() > 0 and thisStatus.excludedStates.size() > 0){
    std:: cout << "RunStatusController::checkStatus : Run status definition has "
	       << "both included and excluded states." << std::endl;
    return false;
  }

  // 2) If definition has included states, check if the status is among the ones 
  // listed as good for this run status definition
  bool includedBit = false;
  if (thisStatus.includedStates.size() > 0) {
    std::vector<int>::iterator includedBitsIter = thisStatus.includedStates.begin();    
    while (!includedBit and includedBitsIter != thisStatus.includedStates.end()) {
      includedBit |= checkStatusBits(runInfos_[currentRun_].status, (*includedBitsIter));
      ++includedBitsIter;
    }
    return includedBit;
  } 

  // 3) If definition doesn't have included states, make sure that this status is not 
  // among the statuses which should be excluded. 
  bool excludedBit = false;
  if (thisStatus.excludedStates.size() > 0) {
    std::vector<int>::iterator excludedBitsIter = thisStatus.excludedStates.begin();
    while (!excludedBit and excludedBitsIter != thisStatus.excludedStates.end()) {
      excludedBit |= checkStatusBits(runInfos_[currentRun_].status, (*excludedBitsIter));
      ++excludedBitsIter;
    }
    return !excludedBit;
  } 

  // 4) If definition doesn't have included or excluded states, then panic.
  if(thisStatus.includedStates.size() == 0 and thisStatus.excludedStates.size() == 0){
    std:: cout 
      << "RunStatusController::checkStatus : Run status definition has "
      << "no included or excluded states." << std::endl;
    return false;
  }

  return false;
}

int RunStatusController::totalRunTime() const {
  int totalTime = 0;
  std::map<int, RunInfo>::const_iterator summaryIter;
  for(summaryIter = runInfos_.begin(); summaryIter != runInfos_.end(); summaryIter++){
    if(summaryIter->second.length > 0){
      totalTime += summaryIter->second.length;
    }
  }
  return totalTime;
}

int RunStatusController::totalAccRunTime() const {
  int totalAccTime = 0;
  std::map<int, RunInfo>::const_iterator summaryIter;
  for(summaryIter = runInfos_.begin(); summaryIter != runInfos_.end(); summaryIter++){
    if(summaryIter->second.accepted){
      if(summaryIter->second.length > 0){
      	totalAccTime += summaryIter->second.length;
      }
    }
  }
  return totalAccTime;
}

int RunStatusController::totalRecoTime() const {
  int totalTime = 0;
  std::map<int, RunInfo>::const_iterator recoIter;
  for(recoIter = recoRunInfos_.begin(); recoIter != recoRunInfos_.end(); recoIter++){
    if(recoIter->second.length > 0){
      totalTime += recoIter->second.length;
    }
  }
  return totalTime;
}
int RunStatusController::totalAccRecoTime() const {
  int totalAccTime = 0;
  std::map<int, RunInfo>::const_iterator recoIter;
  for(recoIter = recoRunInfos_.begin(); recoIter != recoRunInfos_.end(); recoIter++){
    if(recoIter->second.accepted){
      if(recoIter->second.length > 0){
      	totalAccTime += recoIter->second.length;
      }
    }
  }
  return totalAccTime;
}

long RunStatusController::maxGeneratedEvents() const {
  long biggestGenEvts = 0;
  std::map<int, RunInfo>::const_iterator summaryIter;
  for(summaryIter = runInfos_.begin(); summaryIter != runInfos_.end(); summaryIter++){
    if(summaryIter->second.generatedEvents > biggestGenEvts){
      biggestGenEvts = summaryIter->second.generatedEvents;
    }
  }
  return biggestGenEvts;
}

double RunStatusController::totalDeadTime() const {
  double totDeadTime = 0;
  for (std::map<int, RunInfo>::const_iterator summaryIter = runInfos_.begin(); 
       summaryIter != runInfos_.end(); summaryIter++){
    if(summaryIter->second.deadTime > 0){
      totDeadTime += summaryIter->second.deadTime;
    }
  }
  return totDeadTime;
}

double RunStatusController::totalAccDeadTime() const {
  double totDeadTime = 0;
  for (std::map<int, RunInfo>::const_iterator summaryIter = runInfos_.begin(); 
       summaryIter != runInfos_.end(); summaryIter++){
    if (summaryIter->second.accepted) {
      if(summaryIter->second.deadTime > 0){
      	totDeadTime += summaryIter->second.deadTime;
      }
    }
  }
  return totDeadTime;
}

long RunStatusController::totalAssignedEvents() const {
  long totAssignedEvents = 0;
  for (std::map<int, RunInfo>::const_iterator summaryIter = runInfos_.begin(); 
       summaryIter != runInfos_.end(); summaryIter++){
    if(summaryIter->second.assignedEvents > 0){
      totAssignedEvents += summaryIter->second.assignedEvents;
    }
  }
  return totAssignedEvents;
}

long RunStatusController::totalAccAssignedEvents() const {
  long totAssignedEvents = 0;
  for (std::map<int, RunInfo>::const_iterator summaryIter = runInfos_.begin(); 
       summaryIter != runInfos_.end(); summaryIter++){
    if (summaryIter->second.accepted) {
      if(summaryIter->second.assignedEvents > 0){
      	totAssignedEvents += summaryIter->second.assignedEvents;
      }
    }
  }
  return totAssignedEvents;
}

// 11/10/12 - JEM
int RunStatusController::totalAccRunTime(std::string phase) const {
  int totalAccTime = 0;
  std::map<int, RunInfo>::const_iterator summaryIter;
  for(summaryIter = runInfos_.begin(); summaryIter != runInfos_.end(); summaryIter++){
    if(phase == "P1" && summaryIter->second.number < 3396){
      if(summaryIter->second.accepted){
        if(summaryIter->second.length > 0){
          totalAccTime += summaryIter->second.length;
        }
      }
    }
    else if (phase == "P2" && summaryIter->second.number > 3395){
      if(summaryIter->second.accepted){
        if(summaryIter->second.length > 0){
          totalAccTime += summaryIter->second.length;
        }
      }
    }
  }
  return totalAccTime;
}

//14/11/12 - JEM
double RunStatusController::totalAccDeadTime(std::string phase) const {
  double totDeadTime = 0;
  std::map<int, RunInfo>::const_iterator summaryIter;
  for(summaryIter = runInfos_.begin(); summaryIter != runInfos_.end(); summaryIter++){
    if(phase == "P1" && summaryIter->second.number < 3396){
      if(summaryIter->second.accepted){
        if(summaryIter->second.deadTime > 0){
          totDeadTime += summaryIter->second.deadTime;
        }
      }
    }
    else if (phase == "P2" && summaryIter->second.number > 3395){
      if(summaryIter->second.accepted){
        if(summaryIter->second.deadTime > 0){
          totDeadTime += summaryIter->second.deadTime;
        }
      }
    }
  }
  return totDeadTime;
}

//14/11/12 - JEM
int RunStatusController::totalAccRecoTime(std::string phase) const {
  int totalTime = 0;
  std::map<int, RunInfo>::const_iterator recoIter;
  for(recoIter = recoRunInfos_.begin(); recoIter != recoRunInfos_.end(); recoIter++){
    if(recoIter->second.accepted){
      if(phase == "P1" && recoIter->second.number < 3396){
        if(recoIter->second.length > 0){
          totalTime += recoIter->second.length;
        }
      }
      else if (phase == "P2" && recoIter->second.number > 3395){
        if(recoIter->second.length > 0){
          totalTime += recoIter->second.length;
        }
      }
    }
  }

  return totalTime;
}

// 11/10/12 - JEM
double RunStatusController::meanActivity(std::string phase) const {
  double totalDecays = 0;
  std::map<int, RunInfo>::const_iterator summaryIter;
  for(summaryIter = runInfos_.begin(); summaryIter != runInfos_.end(); summaryIter++){
    if(phase == "P1" && summaryIter->second.number < 3396){
      if(summaryIter->second.accepted){
        if((summaryIter->second.activity)*(summaryIter->second.length) > 0){
          totalDecays += (summaryIter->second.length)*(summaryIter->second.activity);
        }
      }
    }
    else if (phase == "P2" && summaryIter->second.number > 3395){
      if(summaryIter->second.accepted){
        if((summaryIter->second.activity)*(summaryIter->second.length) > 0){
          totalDecays += (summaryIter->second.length)*(summaryIter->second.activity);
        }
      }
    }
  }

  double meanAct = 0;
  if(phase == "P1" && totalAccRunTime("P1") > 0){
    meanAct = totalDecays/totalAccRunTime("P1");
  } else if(phase == "P2" && totalAccRunTime("P2") > 0){
    meanAct = totalDecays/totalAccRunTime("P2");
  } else {
    meanAct = 0;
  }

  return meanAct;
}

std::ostream& operator << (std::ostream& os, 
			   const RunStatusController::DataTakingPhase& obj) {
  obj.print(os);
  return os;
}

// 09/10/2012 - ST
AppResult RunStatusController::loadBetaBetaRunSummary() {
  std::cout 
    << " RunStatusController::loadBetaBetaRunSummary - "
    << " loading summary table with all run informations "
    << std::endl;
  std::cout 
    << " ....... connecting to the database "
    << std::endl;

  int attempt = 0;
  mysql_init(&mySqlConnection_);
  
  MYSQL_RES *result;

  std::cout 
    << " ....... trying to connect to "       << std::endl
    << " ... server: " << serverName_.c_str() << std::endl
    << " ... user  : " << userName_.c_str()   << std::endl
    << " ... dbName: " << dbName_.c_str()     << std::endl
    << " ... port  : " << port_               << std::endl;

  while (attempt < maxConnectinAttempts_ && !isConnected_) {
    if (!mysql_real_connect(&mySqlConnection_, 
          serverName_.c_str(), 
          userName_.c_str(), 
          password_.c_str(), 
          dbName_.c_str(),
          port_, 
          NULL, 0)) {
      std::cout 
        << " ....... attempt " << attempt 
        << " was unsuccessfull - MYSQL error: " 
        << mysql_errno(&mySqlConnection_)
        << " - "<< mysql_error(&mySqlConnection_)
        << std::endl;
      usleep(10000);
    } else {
      std::cout 
        << " ....... connection successfull at attempt " 
        << attempt << std::endl;
      isConnected_ = true;
      result=mysql_list_processes(&mySqlConnection_);
      int n_connections = mysql_num_rows(result);
      std::cout 
        << " ....... there are " << n_connections
        << " active connections " << std::endl;
    }
    attempt++;
  }
  
  if (!isConnected_) {
    std::cout 
      << " ERROR: Impossible to connect to the DB after " 
      << attempt << " attempts " << std::endl;
    return  AppResult::ERROR;
  }
  std::cout 
    << " ....... performing the query "
    << std::endl;  
  
  std::stringstream query;
  query << "select * from NEMO.RunMetaDataStatic;";
  // Query to run on the development view - works only in UCL
  // query << "select * from SuperNEMO.NemoBetaBetaRunSummaryStatic;";

  mysql_query(&mySqlConnection_, query.str().c_str());
  result = mysql_store_result(&mySqlConnection_);
        
  int num_fields = mysql_num_fields(result);
        
  MYSQL_ROW row;
  MYSQL_FIELD *field;
  int nWarnings = 0;

  while ((row = mysql_fetch_row(result))) {
    RunSummaryEntry thisEntry;
    thisEntry.runNumber          = atoi(row[0]);
    thisEntry.runDate            = SqlDate(row[1]);
    thisEntry.numEvents          = atol(row[2]);
    if (row[3] == NULL) {
      std::cout 
        << " WARNING : not valid number of events in the RunStop table for run: "
        << thisEntry.runNumber << std::endl;
        ++nWarnings;
    } else if (atoi(row[3]) != 0){
      std::cout 
        << " WARNING : different number of events in RunStore and RunStop tables: "
		    << atoi(row[3]) << " for run " << thisEntry.runNumber << std::endl;
        ++nWarnings;
    }
    thisEntry.runStatus          = atol(row[4]);
    thisEntry.runStart           = (row[5] != NULL) ? SqlDate(row[5]) : SqlDate();
    thisEntry.runStop            = (row[6] != NULL) ? SqlDate(row[6]) : SqlDate();
    thisEntry.deltaStartStop     = (row[7] != NULL) ? atol(row[7]) : -1;  
    if (row[8] != NULL) {
      thisEntry.deadTime         = atof(row[8]);	       
    } else {
      std::cout 
        << " WARNING : no deadtime available for run : "
  		  << thisEntry.runNumber 
  	   	<< " - Setting the deadtime to -1 " << std::endl;      
      thisEntry.deadTime           = -1;	       
      ++nWarnings;
    }
    thisEntry.runTime            = (row[9] != NULL) ? atol(row[9]) : -1;
    thisEntry.firstEventDate     = (row[10] != NULL) ? SqlDate(row[10]) : SqlDate();
    thisEntry.lastEventDate      = (row[11] != NULL) ? SqlDate(row[11]) : SqlDate();
    thisEntry.deltaFirstLast     = (row[12] != NULL) ? atol(row[12]) : -1;
    thisEntry.field              = (row[13] != NULL) ? atoi(row[13]) : -1;
    thisEntry.trigger            = (row[14] != NULL) ? atoi(row[14]) : -1;
    
    runTable_->add(thisEntry);
  }
  std::cout << " ....... read  " << runTable_->nEntries() << " entries "
	    << std::endl;
  std::cout << " ....... found " << nWarnings << " warnings" << std::endl;  
  mysql_free_result(result);

  std::cout << " ....... disconnecting to the database "
	    << std::endl;  
  try {
    mysql_close(&mySqlConnection_);
    isConnected_ = false;
  } catch (std::exception e) {
    std::cout << e.what();
  }
  return AppResult::OK;
}

AppResult RunStatusController::readEventsAssignedPerEvents() {
  std::ifstream file(assignedEventsFileName_.c_str());
  std::string line;
  if (file.is_open()) {

    // JM - 18/5/13 - Get file size
    long begin = file.tellg();
    file.seekg(0,std::ios::end);
    long end = file.tellg();    
    long filesize = end-begin;

    // JM - 18/5/13 - If file size is 0 then it's an empty file (e.g. Data)
    // and we don't want to process it here.
    if(filesize > 0){
      file.seekg(0, std::ios::beg);

      while (!file.eof()) {
        RunInfo thisRunRecord;
        file >> thisRunRecord.number;
        file >> thisRunRecord.assignedEvents;
        std::cout 
          << "*   Run = " << thisRunRecord.number 
          << " - Assigned Events = " << thisRunRecord.assignedEvents
          << std::endl;
        thisRunRecord.status          = -1;
        thisRunRecord.length          = -1;
        thisRunRecord.activity        = -1;
        thisRunRecord.generatedEvents = -1;
        thisRunRecord.observedEvents  = -1;
        thisRunRecord.deadTime        = -1;
        runInfos_.insert( std::pair<int, RunInfo> 
                          (thisRunRecord.number, thisRunRecord)
                        );
      }
    }
    file.close();
  } else {
    std::cout << " ERROR : problem opening " << assignedEventsFileName_ << std::endl;
    return AppResult::ERROR;
  }
  
  return AppResult::OK;
}

// 12/11/13 - JEM
TTimeStamp RunStatusController::runStart() const {

  // If runStart is not blank then return this date
  SqlDate runStartDate = runTable_->runStart(currentRun_);
  if(runStartDate != SqlDate()){
    return TTimeStamp(runStartDate.year, runStartDate.month, runStartDate.day,
		      runStartDate.hour, runStartDate.minute, runStartDate.second);
  }

  // Some runs don't appear in the RunStart table(!). In this case, return the
  // runStop date minus the run length unless the runStop date is blank too
  SqlDate runStopDate = runTable_->runStop(currentRun_);
  if (runStopDate != SqlDate()){
    TTimeStamp stopTimeStamp(runStopDate.year, runStopDate.month, runStopDate.day,
			     runStopDate.hour, runStopDate.minute, runStopDate.second);
    return TTimeStamp(stopTimeStamp.GetSec()-runLength(),stopTimeStamp.GetNanoSec());
  }
  
  // If it doesn't have a runStart or runStop date then it must only have entry in
  // RunStore table.  Therefore use firstEventDate instead
  SqlDate firstEventDate = runTable_->firstEventDate(currentRun_);
  if(firstEventDate != SqlDate()){
    return TTimeStamp(firstEventDate.year, firstEventDate.month, firstEventDate.day,
		      firstEventDate.hour, firstEventDate.minute, firstEventDate.second);
  }

  // Finally if it doesn't have any useful dates return blank TTimeStamp
  return TTimeStamp(0,0,0,0,0,0);
}

