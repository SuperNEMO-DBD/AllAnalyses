//
//  N3DbInterfaceModule.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#ifndef NEMO_N3DBINTERFACEMODULE_H_
#define NEMO_N3DBINTERFACEMODULE_H_
#include "Hereward/DataProcPipeline/AppModule.h"

#define N3DB_NO_CONFIG_H
#include "N3Db.h"
#include "N3DbMgr.h"

#include <map>
#include <vector>

#define PMMAX 1940

struct N3DbEnergyCorrection {
  int ecId;
  std::vector<float> pmAlpha;
  std::vector<float> pmAlphaError;
  std::vector<float> pmResolution;
  std::vector<float> pmResolutionError;
};

struct N3DbLaserTimeCorrection {
  int ltId;
  std::vector<float> tdcFluctuations;
  std::vector<float> correction;
  std::vector<float> correctionError;
};

struct N3DbLaserEnergyCorrection {
  std::vector<int>   flag;
  std::vector<float> coefficient;
};

struct N3DbLaserEnergyCorrectionLD {
  std::vector<int>   flag;
  std::vector<float> correction;
  std::vector<float> correctionError;
};

struct N3DbTimeShiftCorrection {
  int tsId;
  std::vector<float> timeShiftError;
};

struct N3DbRateMonitoringHS {
  int hsId;
  std::vector<int>   flag;
};


typedef std::vector<int> N3DbPmtStatuses;

struct N3DbPMTInfo {
  int    status;
  double alpha;
  double alphaEr;
  double resolution;
  double resolutionEr;
  double tdcFluctuation;
  int    leFlag;
  double leCoefficient;
  int    ldFlag;
  double ldCorrection;
  double ldCorrectionEr;
  double ltCorrection;
  double ltCorrectionEr;
  double timeShiftError;
  int hsFlag;
};

struct N3DbRunInfo {
  int             number;
  int             status;
  int             time;
  int             date;
  float           activity;
  int             ecLocalId;
  int             ltLocalId;
  int             leLocalId;
  int             ldLocalId;
  int             tsId;
  int             hsId;
  N3DbPmtStatuses pmtStatuses;
  void addStatusToPmt(int pmt, int status) {
    pmtStatuses.at(pmt) += status;
  }
  int  statusOfPmt(int pmt) { 
    return pmtStatuses.at(pmt);
  }
  bool hasLaserTimeCorrection()     { return ltLocalId != -1; }
  bool hasEnergyCorrection()        { return ecLocalId != -1; }
  bool hasLaserEnergyCorrection()   { return leLocalId != -1; }
  bool hasLaserEnergyCorrectionLD() { return ldLocalId != -1; }
  bool hasTimeShiftCorrection()     { return tsId != -1; }
  bool hasHsFlag()                  { return hsId != -1; }
};

struct DoublePeakInterval {
  int firstRun;
  int lastRun;
  int sector;
  int ioFlag;
};


class N3DbInterfaceModule : public AppModule {
 public:
  //------------------------------------------------------------
  // Constructor and Destructor
  //------------------------------------------------------------
  N3DbInterfaceModule(const std::string theName = "N3DbInterfaceModule", 
		      const std::string theDescription = "");
  virtual ~N3DbInterfaceModule();

  //-------------------------------------------------------------------------
  // Operations
  //-------------------------------------------------------------------------
  AppResult beginJob(AppEvent* aJob);
  AppResult beginRun(AppEvent* aRun);
  AppResult event(AppEvent* anEvent);
  AppResult endRun(AppEvent* aRun);
  AppResult endJob(AppEvent* aJob);

  //-------------------------------------------------------------------------
  // Accessors
  //-------------------------------------------------------------------------
  bool isConnected() const                  { return isConnected_; }
  void setServerName(const std::string val) { serverName_ = val; }
  void setPort(const int val)               { port_ = val; }
  void setVersion(const int val)            { version_ = val; }
  void setEnableLTC(const bool val)         { enableLTC_ = val; }
    
  static N3DbInterfaceModule* instance();

  int runNumber() const {return currentRunData_->second.number; }
  int runStatus() const {return currentRunData_->second.status; }
  int runTime()   const {return currentRunData_->second.time; }
  int runDate()   const {return currentRunData_->second.date; }
  float runActivity() const {return currentRunData_->second.activity;}
    
  int    pmtStatus(int pmtNum)        const;
  double pmtAlpha(int pmtNum)         const;
  double pmtAlphaEr(int pmtNum)       const;
  double pmtResolution(int pmtNum)    const;
  double pmtResolutionEr(int pmtNum)  const;
  double pmtTdcFluctuation(int pmtNum)const;
  int    pmtLeFlag(int pmtNum)        const;
  double pmtLeCoefficient(int pmtNum) const;
  int    pmtLdFlag(int pmtNum)        const;
  double pmtLdCorrection(int pmtNum)  const;
  double pmtLdCorrectionEr(int pmtNum)const;
  double pmtLtCorrection(int pmtNum)  const;
  double pmtLtCorrectionEr(int pmtNum)const;
  double pmtTimeShiftError(int pmtNum)const;
  int pmtHSflag(int pmtNum)        const;
   
  friend class NemorH10InputModule;
  friend class NemorH10LocalTrackingInputMod;

  inline bool   hasEnergyCorrection()      const {
    return currentRunData_->second.hasEnergyCorrection();
  }

  inline bool   hasLaserEnergyCorrection() const {
    return currentRunData_->second.hasLaserEnergyCorrection();
  }

  inline bool   hasLaserEnergyCorrectionLD() const {
    return currentRunData_->second.hasLaserEnergyCorrectionLD();
  }

  inline bool   hasLaserTimeCorrection()   const {
    return currentRunData_->second.hasLaserTimeCorrection();
  }

  inline bool   hasTimeShiftCorrection()   const {
    return currentRunData_->second.hasLaserEnergyCorrection();
  }

  inline bool   hasHsFlag()   const {
    return currentRunData_->second.hasHsFlag();
  }

  // Choose whether to write DB output to file or to stdout  - JEM (30.03.13)
  void setWriteOutputToFile(const bool aValue) { writeOutputToFile_ = aValue; }

  // JEM 18/05/13 - Move load run data so we can access it from RunStatusController
  void        loadRunData(int runNumber);

  // Choose whether to write DB output to file or to stdout  - JEM (30.03.13)
  void setRunType(const std::string aValue) { runType_ = aValue; }

 private:
  void        loadPmtData(N3DbRunInfo& runRecord);
  void        loadTwoPeakRegions();
  void        checkTwoPeakRegions(N3DbRunInfo& runRecord);

  bool                        isConnected_;
  int                         port_;
  std::string                 serverName_;
  static N3DbInterfaceModule* dbManger_;
  std::map<int, N3DbRunInfo>  data_;
  std::map<int, N3DbRunInfo>::iterator       currentRunData_;
  std::vector<DoublePeakInterval>            listOfDoublePeakIntervals_;

  bool writeOutputToFile_;

  std::string runType_;
					      
  std::map<int, N3DbEnergyCorrection>        energyCorrections_;
  std::map<int, N3DbLaserTimeCorrection>     laserTimeCorrections_;
  int lastLeLocalId_;
  int lastLdLocalId_;
  int lastLtLocalId_;
  int lastEcLocalId_;
  int lastHsLocalId_;
  std::map<int, N3DbLaserEnergyCorrection>   laserEnergyCorrections_;  
  std::map<int, N3DbLaserEnergyCorrectionLD> laserEnergyCorrectionsLD_;  
  std::map<int, N3DbTimeShiftCorrection>     timeShiftCorrections_;
  std::map<int, N3DbRateMonitoringHS>        rateMonitoringHS_;

  int         version_;
  bool        enableLTC_;
  void        connect();
  void        disconnect();
};



#endif
