//
//  N3DbInterfaceModule.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//
#include "mysql.h"
#include <stdexcept>
#include <exception>
#include <sstream>
#include "NemoMods/N3DbInterfaceModule.h"
#include "Hereward/DataProcPipeline/AbsEnv.h"
#include "stdlib.h"

//******************************************************************************

N3DbInterfaceModule* N3DbInterfaceModule::dbManger_ = 0;

//------------------------------------------------------------------------------
// Constructor and Destructor
//------------------------------------------------------------------------------
N3DbInterfaceModule::N3DbInterfaceModule(const std::string theName,
                                         const std::string theDescription) :
AppModule(theName, theDescription),
  port_(3306), 
  serverName_("db1.hep.ucl.ac.uk"),
  version_(12), 
  enableLTC_(true),
  isConnected_(false),
  lastLeLocalId_(-1), lastLdLocalId_(-1), lastLtLocalId_(-1), lastEcLocalId_(-1),
  lastHsLocalId_(-1), writeOutputToFile_(true), runType_("betabeta")
{
  execType_ = App_module;
  dbManger_ = this;
  currentRunData_ = data_.end();
}

N3DbInterfaceModule::~N3DbInterfaceModule() {
  data_.clear();
  listOfDoublePeakIntervals_.clear();
}

//------------------------------------------------------------------------------
// Server handshake methods
//------------------------------------------------------------------------------
N3DbInterfaceModule* N3DbInterfaceModule::instance() {
  if (dbManger_ == 0) 
    dbManger_ = new N3DbInterfaceModule();
  return dbManger_;
}

void N3DbInterfaceModule::connect() {
  std::cout << "----- N3DbInterfaceModule::connect - Initializing N3Db \n"
	    << "---   Server name  : " << serverName_ << "\n"
	    << "---   Port         : " << port_ << "\n"
	    << "---   Is connected : " << isConnected() << std::endl;
 
  if (isConnected()) {
    throw std::runtime_error("DB already connected - possible error");
  }

  nemo3::DbMgr::Init(serverName_.c_str(), port_);

  isConnected_ = nemo3::DbMgr::Db().IsConnected();
  std::cout << "---   Is connected : " << isConnected_ << "\n";
}

void N3DbInterfaceModule::disconnect() {
  if (!isConnected()) {
    throw std::runtime_error("DB is not connected ");
  }
  nemo3::DbMgr::Db().Disconnect();
}


//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult N3DbInterfaceModule::beginJob(AppEvent* aJob) {
  try {
    connect();
  } catch (std::exception e) {
    std::cout << e.what();
    return AppResult::ERROR;
  }
    
  AppResult retval = AppResult::OK;
  if (isConnected()) {
    nemo3::DbMgr::Db().SetTVersion(version_);
    nemo3::DbMgr::Db().EnableLTC(enableLTC_);
    nemo3::DbMgr::Db().SetLVersion(2);
    /* ST - 24/01/2014 - I am commenting out the check on the two peaks because
      1) the routine is wrong as it assumes the run number to refer to a betabeta run
        not a laser run
      2) the revemo_two_peaks routine is executed at recosntruction level as part of 
        the load_lt_by_date routine and is not needed anymore to be executed at analysis
        level
    */
    //loadTwoPeakRegions();
  } else {
    retval = AppResult::ERROR;
  }
  return retval;
}

AppResult N3DbInterfaceModule::beginRun(AppEvent* aRun) {
  return AppResult::OK;
}

AppResult N3DbInterfaceModule::event(AppEvent *anEvent) {
  return AppResult::OK;
}

AppResult N3DbInterfaceModule::endRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult N3DbInterfaceModule::endJob(AppEvent *aJob) {
  disconnect();
  return AppResult::OK;
}

void N3DbInterfaceModule::loadRunData(int runNumber) {
  if (data_.find(runNumber) == data_.end()) {
    bool initialized = nemo3::DbMgr::Db().AnalyzeFile(runNumber,runType_);
    N3DbRunInfo entry;
    entry.number = runNumber;

    // Redirect output from N3Db to a file so that you can see other messages (JEM 30.03.13)
    if(writeOutputToFile_){ freopen("N3Db.dump","a",stdout); }

    if (initialized) {
      int status;
      nemo3::DbMgr::Db().Get("RUNSTORE", "Status",    &entry.status);
      nemo3::DbMgr::Db().Get("RUNSTORE", "TotalTime", &entry.time);
      nemo3::DbMgr::Db().Get("PD", "DateStart", &entry.date);
      nemo3::DbMgr::Db().Get("RN", "Status",    &status);
      if (status==0){
	nemo3::DbMgr::Db().Get("RN", "Act", &entry.activity);
      }

      if ( status != 0 || entry.activity < 1 ) {
	std::cout << "----- N3DbInterfaceModule::loadRunData - \n"
		  << "---   WARNING : Run " << runNumber 
		  << " has no RN activity stored in DB" << std::endl;
	entry.activity = 213; // Use mean acticity durin P2_0nu period as a temporar solution
      }

      if (entry.activity > 400 && entry.number > 3395) entry.status += 200000;
    } else {
      entry.status = -2;
      entry.time = 0;
    }

    loadPmtData(entry);
    data_.insert(std::pair<int, N3DbRunInfo>(entry.number, entry));

    // Close redirected output file and restore stdout (JEM 30.03.13)
    if(writeOutputToFile_){
      fclose(stdout);
      freopen("/dev/tty","w",stdout);
    }
  }

  if (currentRunData_ == data_.end()) {
    currentRunData_ = data_.find(runNumber);
  } else if (this->runNumber() != runNumber) {
    currentRunData_ = data_.find(runNumber);
  }
}

void N3DbInterfaceModule::loadPmtData(N3DbRunInfo& runRecord) {
  std::vector <int>   vecPmStatus;
  std::vector <float> vecPmAlpha;
  std::vector <float> vecPmAlphaError;
  std::vector <float> vecPmResolution;
  std::vector <float> vecPmResolutionError;
  std::vector <float> vecTdcFluctuations;
  std::vector <int>   vecLaserEnergyCorrectionFlag;
  std::vector <float> vecLaserEnergyCorrectionCoefficient;
  std::vector <int>   vecLaserEnergyFlagLD;
  std::vector <float> vecLaserEnergyCorrectionLD;
  std::vector <float> vecLaserEnergyCorrectionErrorLD;
  std::vector <float> vecLaserTimeCorrection;
  std::vector <float> vecLaserTimeCorrectionError;
  std::vector <float> vecTimeShiftError;
  std::vector <int>   vecRateMonitoringFlagHS;

  int hsId;
  int leId;
  int ldId;
  int ltId;
  int ecId;
  int tsIdValue;

  // JEM: 05/11/12. 9060 is the last run with laser runs before and after.  Trying to run 
  // on anything >= 9061 causes a crash here.  There just set these PMTs to have
  // bad status. 
  if(runRecord.number > 9060){
    // ST 3/12/12. Change this ot be compliant with new code structure
    for (int i = 0; i < PMMAX; ++i) { 
      runRecord.pmtStatuses.push_back(4000000);
    }
    // for (unsigned int pmtId = 1; pmtId < PMMAX+1; ++pmtId) {
    //   N3DbPMTInfo entry;
    //   entry.status = 4000000;
    //   runRecord.pmtInfos.insert(std::pair<int, N3DbPMTInfo>(pmtId, entry));
    // }

    ecId = -1;
    ltId = -1;
    leId = -1;
    ldId = -1;
    hsId = -1;
    tsIdValue = -1;
  } else {
    try {
      // 1) PMT status: get the status from the DB
      nemo3::DbMgr::Db().GetMore("PM","Status",   vecPmStatus,1,PMMAX);

      // there was a problem loading the status of the pmts - kill the run:
      if ( vecPmStatus.size() < 10 ) {	
        for (int i = 0; i < PMMAX; ++i) { 
          runRecord.pmtStatuses.push_back(4000000);
        }
      } else {
        runRecord.pmtStatuses = vecPmStatus;

        // 2) Energy Corrections
        nemo3::DbMgr::Db().GetMore("EC","Alpha",    vecPmAlpha,1,PMMAX);
        nemo3::DbMgr::Db().GetMore("EC","Alpha_er", vecPmAlphaError,1,PMMAX);
        std::cout << "----- N of PMT EC : " << vecPmAlpha.size() << std::endl;
        
        bool found = false;
        // if we have already found an energy calibration for a previous run, 
        // we search the list of EC loaded to see if we have already stored this 
        // calibration
        if (lastEcLocalId_ != -1) {
          std::map<int, N3DbEnergyCorrection>::iterator it = energyCorrections_.begin();
          while(!found && it != energyCorrections_.end()) {
            if (it->second.pmAlpha == vecPmAlpha and 
                it->second.pmAlphaError == vecPmAlphaError) {
              found = true;
              ecId = it->first;
            }
            it++;
          }
        }

        // we have not found a matching calibration or this is the first time we look for
        // an Energy Calibratino, so we add this entry.
        if (!found or lastEcLocalId_ == -1) {
          lastEcLocalId_++;
          ecId = lastEcLocalId_;
          N3DbEnergyCorrection thisCorr;
          thisCorr.pmAlpha = vecPmAlpha;
          thisCorr.pmAlphaError = vecPmAlphaError;
          nemo3::DbMgr::Db().GetMore("EC","Resol",    thisCorr.pmResolution,1,PMMAX);
          nemo3::DbMgr::Db().GetMore("EC","Resol_er", thisCorr.pmResolutionError,1,PMMAX);
          energyCorrections_.insert(std::pair<int, N3DbEnergyCorrection>(ecId, thisCorr));
        }

        // 3) Laser Energy Corrections - LE Info
        // first check whether we have already found a run with this calibrations
        found = false;
        nemo3::DbMgr::Db().GetMore("LE","Flag", vecLaserEnergyCorrectionFlag,1,PMMAX);
        nemo3::DbMgr::Db().GetMore("LE","Coef", vecLaserEnergyCorrectionCoefficient,1,PMMAX);
        if (lastLeLocalId_ != -1) {
          std::map<int, N3DbLaserEnergyCorrection>::iterator it = laserEnergyCorrections_.begin();
          while(!found && it != laserEnergyCorrections_.end()) {
            if (it->second.flag == vecLaserEnergyCorrectionFlag and 
        	it->second.coefficient == vecLaserEnergyCorrectionCoefficient) {
              found = true;
              leId = it->first;
            }
            it++;
          }
        }
        if (!found or lastLeLocalId_ == -1) {
          lastLeLocalId_++;
          leId = lastLeLocalId_;
          N3DbLaserEnergyCorrection thisCorr;
          thisCorr.flag = vecLaserEnergyCorrectionFlag;
          thisCorr.coefficient = vecLaserEnergyCorrectionCoefficient;
          nemo3::DbMgr::Db().GetMore("LE","Coef", thisCorr.coefficient,1,PMMAX);
          laserEnergyCorrections_.insert(
            std::pair<int, N3DbLaserEnergyCorrection>(leId, thisCorr));
        }

        // 4) Laser Energy Corrections - LD Info
        found = false;
        // JEM (16/7/13) - Add check so that you don't crash if there's your LD flags are out of the 
        // allowed time range
        if(nemo3::DbMgr::Db().CheckLD()){
          nemo3::DbMgr::Db().GetMore("LD","Flag",           vecLaserEnergyFlagLD,           1,PMMAX);
          nemo3::DbMgr::Db().GetMore("LD","Correction",     vecLaserEnergyCorrectionLD,     1,PMMAX);
          nemo3::DbMgr::Db().GetMore("LD","Correction_err", vecLaserEnergyCorrectionErrorLD,1,PMMAX);
        } else {
          for (int i = 0; i < PMMAX; i++){
            vecLaserEnergyFlagLD.push_back(100000);
            vecLaserEnergyCorrectionLD.push_back(1e6);
            vecLaserEnergyCorrectionErrorLD.push_back(1e6);
          }
        }
        if (lastLdLocalId_ != -1) {
          std::map<int, N3DbLaserEnergyCorrectionLD>::iterator it = laserEnergyCorrectionsLD_.begin();
          while(!found && it != laserEnergyCorrectionsLD_.end()) {

            if (it->second.flag == vecLaserEnergyFlagLD and 
        	it->second.correction == vecLaserEnergyCorrectionLD and
        	it->second.correctionError == vecLaserEnergyCorrectionErrorLD ) {
              found = true;
              ldId = it->first;
            }
            it++;
          }
        }
        if (!found or lastLdLocalId_ == -1) {
          lastLdLocalId_++;
          ldId = lastLdLocalId_;
          N3DbLaserEnergyCorrectionLD thisCorr;
          thisCorr.flag = vecLaserEnergyFlagLD;
          thisCorr.correction = vecLaserEnergyCorrectionLD;
          thisCorr.correctionError = vecLaserEnergyCorrectionErrorLD;
          laserEnergyCorrectionsLD_.insert(std::pair<int, N3DbLaserEnergyCorrectionLD>(ldId, thisCorr));
        }

        // 7) Hit rate monitoring flag HS // added by c.v. on 10 Feb 2014. I don't fully understand
        // what's going on here, mostly copying from the above...
        found = false;

        nemo3::DbMgr::Db().GetMore("HS", "Flag",         vecRateMonitoringFlagHS, 1, PMMAX);

        if (lastHsLocalId_ != 1){
          std::map<int, N3DbRateMonitoringHS>::iterator it = rateMonitoringHS_.begin();
          while (!found && it != rateMonitoringHS_.end() ){
            if( it->second.flag == vecRateMonitoringFlagHS ){
              found = true;
              hsId = it->first;
            }
            it++;
          }
        }

        if ( !found or lastHsLocalId_ == -1 ){
          lastHsLocalId_++;
          hsId = lastHsLocalId_;
          N3DbRateMonitoringHS thisCorr;
          thisCorr.flag = vecRateMonitoringFlagHS;
          rateMonitoringHS_.insert(std::pair<int, N3DbRateMonitoringHS>(hsId, thisCorr));
        }

        // 5) Laser Time Corrections
        found = false;
        nemo3::DbMgr::Db().GetMore("LT","TDC_fluct", vecTdcFluctuations, 1, PMMAX);
        nemo3::DbMgr::Db().GetMore("LT","LTc",   vecLaserTimeCorrection, 1, PMMAX);

        if (lastLtLocalId_ != -1) {
          std::map<int, N3DbLaserTimeCorrection>::iterator it = laserTimeCorrections_.begin();
          while (!found && it != laserTimeCorrections_.end()) {
            if (it->second.tdcFluctuations == vecTdcFluctuations and
                it->second.correction  == vecLaserTimeCorrection) {
              found = true;
              ltId = it->first;
            }
            it++;
          }
        }

        if (!found or lastLtLocalId_ == -1) {
          lastLtLocalId_++;
          ltId = lastLtLocalId_;
          N3DbLaserTimeCorrection thisCorr;
          thisCorr.tdcFluctuations = vecTdcFluctuations;
          thisCorr.correction = vecLaserTimeCorrection;
          nemo3::DbMgr::Db().GetMore("LT","LTce",     thisCorr.correctionError,1,PMMAX);
          laserTimeCorrections_.insert(std::pair<int, N3DbLaserTimeCorrection>(ltId, thisCorr));  
        }
        
        // 6) Time Shift Corrections
        nemo3::DbMgr::Db().Get("TS", "TsID", &tsIdValue);
        if (timeShiftCorrections_.find(tsIdValue) == timeShiftCorrections_.end()) {
          N3DbTimeShiftCorrection thisCorr;
          thisCorr.tsId = tsIdValue;
          nemo3::DbMgr::Db().GetMore("TS","Ts_er", thisCorr.timeShiftError,1,PMMAX);
          timeShiftCorrections_.insert(std::pair<int, N3DbTimeShiftCorrection>(tsIdValue, thisCorr));
        }
      }
    }
    catch(std::runtime_error & rte ){
      std::cout << "----- N3DbInterfaceModule::loadPmtData : run = " 
                << runRecord.number << "\n" 
                << " Error accessing DB tables: " << rte.what() << std::endl;
    }

    // if ( vecPmStatus.size() < 10 ) {
    //   // there was a problem loading the status of the pmts - kill the run:
    //   for (unsigned int pmtId = 1; pmtId < PMMAX+1; ++pmtId) {
    // 	N3DbPMTInfo entry;
    // 	entry.status = 4000000;
    // 	runRecord.pmtInfos.insert(std::pair<int, N3DbPMTInfo>(pmtId, entry));
    //   }
    // } else {
    //   for (unsigned int pmtId = 1; pmtId < PMMAX+1; ++pmtId) {
    // 	N3DbPMTInfo entry;
    // 	entry.status          = vecPmStatus.at(pmtId - 1);
    // 	entry.alpha           = vecPmAlpha.at(pmtId - 1);
    // 	entry.alphaEr         = vecPmAlphaError.at(pmtId - 1);
    // 	entry.resolution      = vecPmResolution.at(pmtId - 1);
    // 	entry.resolutionEr    = vecPmResolutionError.at(pmtId - 1);
    // 	entry.tdcFluctuation  = vecTdcFluctuations.at(pmtId - 1);
    // 	entry.leFlag          = vecLaserEnergyCorrectionFlag.at(pmtId - 1);
    // 	entry.leCoefficient   = vecLaserEnergyCorrectionCoefficient.at(pmtId - 1);
    // 	entry.ltCorrection    = vecLaserTimeCorrection.at(pmtId - 1);
    // 	entry.ltCorrectionEr  = vecLaserTimeCorrectionError.at(pmtId - 1);
    // 	entry.timeShiftError  = vecTimeShiftError.at(pmtId - 1);
    // 	runRecord.pmtInfos.insert(std::pair<int, N3DbPMTInfo>(pmtId, entry));
    //   }    
    // }
  }
  runRecord.ecLocalId       = ecId;
  runRecord.ltLocalId       = ltId;
  runRecord.leLocalId       = leId;
  runRecord.ldLocalId       = ldId;
  runRecord.tsId            = tsIdValue;
  runRecord.hsId            = hsId;
    
  std::cout << "---- Run     : " << runRecord.number << "\n"
	    << "---- ECID    : " << runRecord.ecLocalId << "\n"
	    << "---- LTID    : " << runRecord.ltLocalId << "\n"
	    << "---- LEID    : " << runRecord.leLocalId << "\n"
	    << "---- LDID    : " << runRecord.ldLocalId << "\n"
	    << "---- TSID    : " << runRecord.tsId << "\n"
	    << std::endl;
  /* ST - 24/01/2014 - I am commenting out the check on the two peaks because
    1) the routine is wrong as it assumes the run number to refer to a betabeta run
      not a laser run
    2) the revemo_two_peaks routine is executed at recosntruction level as part of 
      the load_lt_by_date routine and is not needed anymore to be executed at analysis
      level
  */      
  // checkTwoPeakRegions(runRecord);

  vecPmStatus.clear();
  vecPmAlpha.clear();
  vecPmAlphaError.clear();
  vecPmResolution.clear();
  vecPmResolutionError.clear();
  vecTdcFluctuations.clear();
  vecLaserEnergyCorrectionFlag.clear();
  vecLaserEnergyCorrectionCoefficient.clear();
  vecLaserEnergyFlagLD.clear();
  vecLaserEnergyCorrectionLD.clear();
  vecLaserEnergyCorrectionErrorLD.clear();
  vecLaserTimeCorrection.clear();
  vecLaserTimeCorrectionError.clear();
  vecTimeShiftError.clear();
  vecRateMonitoringFlagHS.clear();
}

void N3DbInterfaceModule::loadTwoPeakRegions() {
  DoublePeakInterval thisInterval;
  thisInterval.firstRun=4058; thisInterval.lastRun=4162; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=4680; thisInterval.lastRun=4729; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=4770; thisInterval.lastRun=4785; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=4805; thisInterval.lastRun=4805; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=4831; thisInterval.lastRun=4919; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=4996; thisInterval.lastRun=5011; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=5614; thisInterval.lastRun=5619; thisInterval.sector=9 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=5622; thisInterval.lastRun=5683; thisInterval.sector=9 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6395; thisInterval.lastRun=6485; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6676; thisInterval.lastRun=6693; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6676; thisInterval.lastRun=6693; thisInterval.sector=9 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6696; thisInterval.lastRun=6696; thisInterval.sector=9 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6714; thisInterval.lastRun=6719; thisInterval.sector=9 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6720; thisInterval.lastRun=6720; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6723; thisInterval.lastRun=6753; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=6890; thisInterval.lastRun=6929; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7146; thisInterval.lastRun=7158; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7203; thisInterval.lastRun=7247; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7263; thisInterval.lastRun=7264; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7292; thisInterval.lastRun=7329; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7316; thisInterval.lastRun=7328; thisInterval.sector=3 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7626; thisInterval.lastRun=7626; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7635; thisInterval.lastRun=7671; thisInterval.sector=0 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7677; thisInterval.lastRun=7689; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=7693; thisInterval.lastRun=8019; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8077; thisInterval.lastRun=8164; thisInterval.sector=0 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8207; thisInterval.lastRun=8395; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8432; thisInterval.lastRun=8440; thisInterval.sector=4 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8467; thisInterval.lastRun=8467; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8629; thisInterval.lastRun=8643; thisInterval.sector=0 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8727; thisInterval.lastRun=8732; thisInterval.sector=15; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8877; thisInterval.lastRun=8889; thisInterval.sector=3 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8878; thisInterval.lastRun=8887; thisInterval.sector=8 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8890; thisInterval.lastRun=8890; thisInterval.sector=0 ; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8890; thisInterval.lastRun=8890; thisInterval.sector=19; thisInterval.ioFlag=0; listOfDoublePeakIntervals_.push_back(thisInterval);
  thisInterval.firstRun=8891; thisInterval.lastRun=8914; thisInterval.sector=3 ; thisInterval.ioFlag=1; listOfDoublePeakIntervals_.push_back(thisInterval);
}

void N3DbInterfaceModule::checkTwoPeakRegions(N3DbRunInfo& runRecord) {
  // ST copy 1 to 1 of the logic in remove_two_peaks... whatever that logic is
  std::vector<DoublePeakInterval>::iterator listIterator = 
    listOfDoublePeakIntervals_.begin();
  
  while (listIterator != listOfDoublePeakIntervals_.end()) {
    DoublePeakInterval thisInterval = (*listIterator);
    
    if (runRecord.number >= thisInterval.firstRun and 
	runRecord.number <= thisInterval.lastRun) {
      int firstPmtInSector=thisInterval.sector*97; // ST: 97 pmt per secrtor
      if (thisInterval.ioFlag == 0) {
	int firstPmtInLoop = firstPmtInSector;
	int lastPmtInLoop = firstPmtInLoop + 34;
	for (int pmtId = firstPmtInLoop; pmtId < lastPmtInLoop; ++pmtId) {
	  runRecord.addStatusToPmt(pmtId, 4000000);
	  std::cout << "Pmt " << pmtId 
		    << " has Status " << runRecord.statusOfPmt(pmtId)
		    << std::endl;
	}
	
	firstPmtInLoop = firstPmtInSector + 73;
	lastPmtInLoop = firstPmtInLoop + 6;
	for (int pmtId = firstPmtInLoop; pmtId < lastPmtInLoop; ++pmtId) {
	  runRecord.addStatusToPmt(pmtId, 4000000);
	  std::cout << "Pmt " << pmtId 
		    << " has Status " << runRecord.statusOfPmt(pmtId)
		    << std::endl;
	}

	firstPmtInLoop = firstPmtInSector + 85;
	lastPmtInLoop = firstPmtInLoop + 6;	    
	for (int pmtId = firstPmtInLoop; pmtId < lastPmtInLoop; ++pmtId) {
	  runRecord.addStatusToPmt(pmtId, 4000000);
	  std::cout << "Pmt " << pmtId 
		    << " has Status " << runRecord.statusOfPmt(pmtId)
		    << std::endl;
	}
      } else {
	int firstPmtInLoop = firstPmtInSector + 34;
	int lastPmtInLoop = firstPmtInLoop + 39;
	for (int pmtId = firstPmtInLoop; pmtId < lastPmtInLoop; ++pmtId) {
	  runRecord.addStatusToPmt(pmtId, 4000000);
	  std::cout << "Pmt " << pmtId 
		    << " has Status " << runRecord.statusOfPmt(pmtId)
		    << std::endl;
	}

	firstPmtInLoop = firstPmtInSector + 79;
	lastPmtInLoop = firstPmtInLoop + 6;
	for (int pmtId = firstPmtInLoop; pmtId < lastPmtInLoop; ++pmtId) {
	  runRecord.addStatusToPmt(pmtId, 4000000);
	  std::cout << "Pmt " << pmtId 
		    << " has Status " << runRecord.statusOfPmt(pmtId)
		    << std::endl;
	}

	firstPmtInLoop = firstPmtInSector + 91;
	lastPmtInLoop = firstPmtInLoop + 6;	    
	for (int pmtId = firstPmtInLoop; pmtId < lastPmtInLoop; ++pmtId) {
	  runRecord.addStatusToPmt(pmtId, 4000000);
	  std::cout << "Pmt " << pmtId 
		    << " has Status " << runRecord.statusOfPmt(pmtId)
		    << std::endl;
	}	    
      }
    }
    listIterator++;
  }
}

int    N3DbInterfaceModule::pmtStatus(int pmtNum)         const {
  return currentRunData_->second.statusOfPmt(pmtNum-1);
}

double N3DbInterfaceModule::pmtAlpha(int pmtNum)          const {
  if (currentRunData_->second.hasEnergyCorrection()) {
    int entryId = currentRunData_->second.ecLocalId;
    return energyCorrections_.find(entryId)->second.pmAlpha.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtAlphaEr(int pmtNum)        const {
  if (currentRunData_->second.hasEnergyCorrection()) {  
    int entryId = currentRunData_->second.ecLocalId;
    return energyCorrections_.find(entryId)->second.pmAlphaError.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtResolution(int pmtNum)     const {
  if (currentRunData_->second.hasEnergyCorrection()) {  
    int entryId = currentRunData_->second.ecLocalId;
    return energyCorrections_.find(entryId)->second.pmResolution.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtResolutionEr(int pmtNum)   const {
  if (currentRunData_->second.hasEnergyCorrection()) {  
    int entryId = currentRunData_->second.ecLocalId;
    return energyCorrections_.find(entryId)->second.pmResolutionError.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtTdcFluctuation(int pmtNum) const {
  if (currentRunData_->second.hasLaserTimeCorrection()) {
    int entryId = currentRunData_->second.ltLocalId;
    return laserTimeCorrections_.find(entryId)->second.tdcFluctuations.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtLtCorrection(int pmtNum)   const {
  if (currentRunData_->second.hasLaserTimeCorrection()) {
    int entryId = currentRunData_->second.ltLocalId;
    return laserTimeCorrections_.find(entryId)->second.correction.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtLtCorrectionEr(int pmtNum) const {
  if (currentRunData_->second.hasLaserTimeCorrection()) {
    int entryId = currentRunData_->second.ltLocalId;
    return laserTimeCorrections_.find(entryId)->second.correctionError.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

int    N3DbInterfaceModule::pmtLeFlag(int pmtNum)         const {
  if (currentRunData_->second.hasLaserEnergyCorrection()) {
    int entryId = currentRunData_->second.leLocalId;
    return laserEnergyCorrections_.find(entryId)->second.flag.at(pmtNum-1);
  } else {
    return 100;
  }
}

double N3DbInterfaceModule::pmtLeCoefficient(int pmtNum)  const {
  if (currentRunData_->second.hasLaserEnergyCorrection()) {
    int entryId = currentRunData_->second.leLocalId;
    return laserEnergyCorrections_.find(entryId)->second.coefficient.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

int    N3DbInterfaceModule::pmtLdFlag(int pmtNum)         const {
  if (currentRunData_->second.hasLaserEnergyCorrectionLD()) {
    int entryId = currentRunData_->second.ldLocalId;
    return laserEnergyCorrectionsLD_.find(entryId)->second.flag.at(pmtNum-1);
  } else {
    return 100;
  }
}

double N3DbInterfaceModule::pmtLdCorrection(int pmtNum)  const {
  if (currentRunData_->second.hasLaserEnergyCorrectionLD()) {
    int entryId = currentRunData_->second.ldLocalId;
    return laserEnergyCorrectionsLD_.find(entryId)->second.correction.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtLdCorrectionEr(int pmtNum)  const {
  if (currentRunData_->second.hasLaserEnergyCorrectionLD()) {
    int entryId = currentRunData_->second.ldLocalId;
    return laserEnergyCorrectionsLD_.find(entryId)->second.correctionError.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

double N3DbInterfaceModule::pmtTimeShiftError(int pmtNum) const {
  if (currentRunData_->second.hasTimeShiftCorrection()) {
    int entryId = currentRunData_->second.tsId;
    return timeShiftCorrections_.find(entryId)->second.timeShiftError.at(pmtNum-1);
  } else {
    return 1e6;
  }
}

int N3DbInterfaceModule::pmtHSflag(int pmtNum) const {
  if (currentRunData_->second.hasHsFlag()){
    int entryId = currentRunData_->second.hsId;
    return rateMonitoringHS_.find(entryId)->second.flag.at(pmtNum-1);
  } else {
    return 100;
  }

}
