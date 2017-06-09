//
//  NemoDataBaseManager.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#ifndef NEMO_NEMODATABASEMANAGER_H_
#define NEMO_NEMODATABASEMANAGER_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/SqlDate.h"
#include "NemoMods/RunSummaryTable.h"
#include "NemoMods/LaserTimeCorrectionTable.h"
#include "NemoMods/EnergyCorrectionTable.h"
#include "NemoMods/BadPMTStatusInLaserRunTable.h"
#include "mysql.h"

class NemoDataBaseManager : public AppModule {
public:
    //------------------------------------------------------------
    // Constructor and Destructor
    //------------------------------------------------------------
    NemoDataBaseManager(const std::string theName = "NemoDataBaseManager", 
                        const std::string theDescription = "");
    virtual ~NemoDataBaseManager();

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
    void setSocket(const std::string val)     { socket_ = val;}
    void setDbName(const std::string val)     { dbName_ = val;}
    void setUserName(const std::string val)   { userName_ = val; }
    void setPassword(const std::string val)   { password_ = val; }
    
    static const NemoDataBaseManager* instance();
    
    RunSummaryTable*            runSummaryData() const {
        return runSummaryData_;
    }
    LaserTimeCorrectionTable*   laserTimeCorrectionData() const {
        return laserTimeCorrectionData_;
    }
    EnergyCorrectionTable*      energyCorrectionData() const {
        return energyCorrectionData_;
    }
    BadPMTStatusInLaserRunTable* badPMTStatusInLaserRunData() const {
        return badPMTStatusInLaserRunData_;
    }
    
private:
    
    bool                        isConnected_;
    int                         port_;
    std::string                 serverName_;
    std::string                 socket_;
    std::string                 dbName_;
    std::string                 userName_;
    std::string                 password_;
    static NemoDataBaseManager* dbManger_;
    MYSQL                       mySqlConnection_;
    
    void        connect();
    void        disconnect();
    bool        getBetaBetaRunSummaryData();
    bool        getLaserTimeCorrectionData();
    bool        getEnergyCorrectionData();
    bool        getBadPMTStatusInLaserRunData();
    
    RunSummaryTable*                runSummaryData_;
    LaserTimeCorrectionTable*       laserTimeCorrectionData_;
    EnergyCorrectionTable*          energyCorrectionData_;
    BadPMTStatusInLaserRunTable*    badPMTStatusInLaserRunData_;
};

#endif
