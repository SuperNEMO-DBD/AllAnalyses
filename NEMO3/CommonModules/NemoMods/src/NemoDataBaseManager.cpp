//
//  NemoDataBaseManager.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//
#include "mysql.h"
#include <stdexcept>
#include <exception>
#include <sstream>
#include "NemoMods/NemoDataBaseManager.h"
#include "Hereward/DataProcPipeline/AbsEnv.h"
#include "stdlib.h"

//******************************************************************************

NemoDataBaseManager* NemoDataBaseManager::dbManger_ = 0;

//------------------------------------------------------------------------------
// Constructor and Destructor
//------------------------------------------------------------------------------
NemoDataBaseManager::NemoDataBaseManager(const std::string theName,
                                         const std::string theDescription) :
AppModule(theName, theDescription),
port_(3306), 
serverName_("db1.hep.ucl.ac.uk"), 
dbName_("SuperNEMO"),
userName_("nemo"),
password_("betabeta"){
    execType_ = App_module;
    runSummaryData_          = new RunSummaryTable();
    laserTimeCorrectionData_ = new LaserTimeCorrectionTable();
    energyCorrectionData_    = new EnergyCorrectionTable();
    badPMTStatusInLaserRunData_ = new BadPMTStatusInLaserRunTable();
    dbManger_ = this;
}

NemoDataBaseManager::~NemoDataBaseManager() {}

//------------------------------------------------------------------------------
// Server handshake methods
//------------------------------------------------------------------------------
const NemoDataBaseManager* NemoDataBaseManager::instance() {
    if (dbManger_ == 0) 
        dbManger_ = new NemoDataBaseManager();
    return dbManger_;
}

void NemoDataBaseManager::connect() {
    if (isConnected()) {
        throw std::runtime_error("DB already connected - possible error");
    }
    
    try {
        
        mysql_init(&mySqlConnection_);
        
        if (!mysql_real_connect(&mySqlConnection_, 
                                serverName_.c_str(), 
                                userName_.c_str(), 
                                password_.c_str(), 
                                dbName_.c_str(),
                                port_, 
                                NULL, 0)) {
            std::ostringstream errorStream;
            std::cout << port_ << std::endl;
            
            errorStream << " Error " << mysql_errno(&mySqlConnection_) 
            << " : " << mysql_error(&mySqlConnection_);
            
            std::cout << errorStream.str() << std::endl;
            
            throw std::runtime_error(errorStream.str());
        }
        
        // got here so we are connected
        isConnected_ = true;
        
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

void NemoDataBaseManager::disconnect() {
    if (!isConnected()) {
        throw std::runtime_error("DB is not connected ");
    }
    
    try {
        mysql_close(&mySqlConnection_);
        isConnected_ = false;
    } catch (std::exception e) {
        std::cout << e.what();
    }
}


//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult NemoDataBaseManager::beginJob(AppEvent* aJob) {
    try {
        connect();
    } catch (std::exception e) {
        std::cout << e.what();
        return AppResult::ERROR;
    }
    
    AppResult retval = AppResult::OK;
    
    if (retval != AppResult::ERROR)
        retval = (getLaserTimeCorrectionData()) ? retval : AppResult::ERROR;
    
    if (retval != AppResult::ERROR)
        retval = (getEnergyCorrectionData()) ? retval : AppResult::ERROR;
    
    if (retval != AppResult::ERROR)
        retval = (getBadPMTStatusInLaserRunData()) ? retval : AppResult::ERROR;

    if (retval != AppResult::ERROR)
        retval = (getBetaBetaRunSummaryData()) ? retval : AppResult::ERROR;

    return retval;
}

AppResult NemoDataBaseManager::beginRun(AppEvent* aRun) {
    int currentRunNumber = AbsEnv::instance()->runNumber();
    return AppResult::OK;
}

AppResult NemoDataBaseManager::event(AppEvent *anEvent) {
    return AppResult::OK;
}

AppResult NemoDataBaseManager::endRun(AppEvent *aRun) {
    return AppResult::OK;
}

AppResult NemoDataBaseManager::endJob(AppEvent *aJob) {
    disconnect();
    return AppResult::OK;
}

bool NemoDataBaseManager::getBetaBetaRunSummaryData() {
    if (isConnected()) {
        std::cout << "------ Loading Run status data " << std::endl;
        
        std::stringstream query;
        query << "select * from SuperNEMO.BetaBetaRunSummaryStatic;";
        
        MYSQL_RES *result;
        mysql_query(&mySqlConnection_, query.str().c_str());
        result = mysql_store_result(&mySqlConnection_);
        
        int num_fields = mysql_num_fields(result);
        
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        
        std::vector<std::string> fields;
        while ((row = mysql_fetch_row(result)))
        {
	  // 05/10/2012 ST: the definition of the RunSummaryTable is changed, so I am
	  //                here commenting all obsolete bits of code. This module is 
	  //                not currently used.
            RunSummaryEntry thisEntry;
            thisEntry.runNumber                         = atoi(row[0]);
            thisEntry.runDate                           = SqlDate(row[1]);
            // thisEntry.timeStamp                         = atoi(row[2]);
            thisEntry.numEvents                         = atol(row[3]);
            thisEntry.field                             = atoi(row[4]);
            thisEntry.runStatus                         = atoi(row[5]);
            thisEntry.trigger                           = atoi(row[6]);
            thisEntry.runTime                           = atol(row[7]);
            thisEntry.firstEventDate                    = SqlDate(row[8]);
            thisEntry.lastEventDate                     = SqlDate(row[9]);
            

            // if (row[10] != NULL) {
            //     thisEntry.lastLaserTimeCalibrationId        = atoi(row[10]);
            //     thisEntry.timeSinceLastTimeCalibration      = atol(row[11]);
            // } else {
            //     thisEntry.lastLaserTimeCalibrationId        = -1;
            //     thisEntry.timeSinceLastTimeCalibration      = -1;
            // }
            
            // if (row[12] != NULL) {
            //     thisEntry.nextLaserTimeCalibrationId        = atoi(row[12]);
            //     thisEntry.timeToNextTimeCalibration         = atol(row[13]);
            // } else  {
            //     thisEntry.nextLaserTimeCalibrationId        = -1;
            //     thisEntry.timeToNextTimeCalibration         = -1;
            // }
            
            // if (row[14] != NULL) {
            //     thisEntry.laserEnergyCalibrationId      	= atoi(row[14]);
            // } else {
            //     thisEntry.laserEnergyCalibrationId          = -1;
            // }
            
            // if (row[15] != NULL) {
            //     thisEntry.lastEnergyCorrId                  = atoi(row[15]);
            //     thisEntry.timeSinceLaserEnergyCorrection    = atol(row[16]);
            // } else {
            //     thisEntry.lastEnergyCorrId                  = -1;
            //     thisEntry.timeSinceLaserEnergyCorrection    = -1;
            // }
            
            
            // if (row[17] != NULL) {
            //     thisEntry.nextEnergyCorrId                  = atoi(row[17]);
            //     thisEntry.timeToNextLaserEnergyCorrection   = atol(row[18]);
            // } else {
            //     thisEntry.nextEnergyCorrId                  = -1;
            //     thisEntry.timeToNextLaserEnergyCorrection   = -1;
            // }
            runSummaryData_->add(thisEntry);
        }
        std::cout << " --- " << runSummaryData_->nEntries() 
        << " entries read " << std::endl;
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}

bool NemoDataBaseManager::getLaserTimeCorrectionData() {
    if (isConnected()) {
        std::cout << "------ Laser time correction data " << std::endl;
        
        std::stringstream query;
        query << "select * from LaserTimeCorrections;";

        MYSQL_RES *result;
        
        mysql_query(&mySqlConnection_, query.str().c_str());
        result = mysql_store_result(&mySqlConnection_);
        
        int num_fields = mysql_num_fields(result);
        
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        
        std::vector<std::string> fields;
        while ((row = mysql_fetch_row(result)))
        {
            LaserTimeCorrectionEntry thisEntry;
            thisEntry.runId                             = atoi(row[0]);
            thisEntry.runNumber                         = atoi(row[1]);
            thisEntry.numberOfLasers                    = atoi(row[2]);
            thisEntry.version                           = atoi(row[5]);

            for (int columnId = 5; columnId < num_fields; ++columnId) {
                int pmtId = columnId - 5;
                thisEntry.correction[pmtId] = atof(row[columnId]);
            }
            laserTimeCorrectionData_->add(thisEntry);
        }
        std::cout << " --- " << laserTimeCorrectionData_->nEntries() 
        << " entries read " << std::endl;
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}

bool NemoDataBaseManager::getEnergyCorrectionData() {
    if (isConnected()) {
        std::cout << "------ Energy correction data " << std::endl;
        
        std::stringstream query;
        query << "select * from EnergyCorrections;";

        MYSQL_RES *result;
        
        mysql_query(&mySqlConnection_, query.str().c_str());
        result = mysql_store_result(&mySqlConnection_);
        
        int num_fields = mysql_num_fields(result);
        
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        
        std::vector<std::string> fields;
        while ((row = mysql_fetch_row(result))) {
            int thisEntryId = atoi(row[0]);            
            if (!energyCorrectionData_->contains(thisEntryId)) {
                EnergyCorrectionEntry thisEntry;
                thisEntry.runId             = thisEntryId;
                thisEntry.ecRelease         = atoi(row[1]);
                thisEntry.ecVersion         = atoi(row[2]);
                thisEntry.runDate           = SqlDate(row[3]);
                thisEntry.endDate           = SqlDate(row[4]);
                thisEntry.aplDate           = SqlDate(row[5]);
                thisEntry.ecType            = atoi(row[6]);
                
                ECPhotoMultiplierData pmtEntry;
                pmtEntry.pmNum = atoi(row[7]);
                pmtEntry.resolution         = double(atoi(row[8]))/10000.;
                pmtEntry.resolutionError    = double(atoi(row[9]))/100000.;
                pmtEntry.alpha              = double(atoi(row[10]))/1000.;
                pmtEntry.alphaError         = double(atoi(row[11]))/100000.;
                pmtEntry.beta               = atof(row[12]);
                pmtEntry.betaError          = atof(row[13]);
                pmtEntry.status             = atoi(row[14]);
                
                thisEntry.add(pmtEntry);
                energyCorrectionData_->add(thisEntry);
                
            } else {
                // we already have an entry for this calibration run, so we 
                // need only to add the informantion on the pmt corrections
                ECPhotoMultiplierData pmtEntry;
                pmtEntry.pmNum = atoi(row[7]);
                pmtEntry.resolution         = double(atoi(row[8]))/10000.;
                pmtEntry.resolutionError    = double(atoi(row[9]))/100000.;
                pmtEntry.alpha              = double(atoi(row[10]))/1000.;
                pmtEntry.alphaError         = double(atoi(row[11]))/100000.;
                pmtEntry.beta               = atof(row[12]);
                pmtEntry.betaError          = atof(row[13]);
                pmtEntry.status             = atoi(row[14]);
                energyCorrectionData_->addPmtData(thisEntryId, pmtEntry);
            }
        }
        std::cout << " --- " << energyCorrectionData_->nEntries() 
        << " entries read " << std::endl;
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
}

bool NemoDataBaseManager::getBadPMTStatusInLaserRunData() {
    if (isConnected()) {
        std::cout << "------ PMT with bad status in Laser Runs " << std::endl;
        
        std::stringstream query;
        query << "select * from BadPMTInLaserRun;";
        
        MYSQL_RES *result;
        
        mysql_query(&mySqlConnection_, query.str().c_str());
        result = mysql_store_result(&mySqlConnection_);
        
        int num_fields = mysql_num_fields(result);
        
        MYSQL_ROW row;
        MYSQL_FIELD *field;
        
        std::vector<std::string> fields;
        while ((row = mysql_fetch_row(result))) {
            int thisVersion = atoi(row[0]);
    
            if (!badPMTStatusInLaserRunData_->contains(thisVersion)) {
                VersionDataSummary *aVersionSummary = new VersionDataSummary();
                aVersionSummary->version = thisVersion;

                PmtDataSummary     aPmtSummary;
                aPmtSummary.pmtNumber = atoi(row[1]);
                aPmtSummary.runCouples.insert(std::pair<int, int>
                                              (atoi(row[2]), atoi(row[3])));
                
                aVersionSummary->add(aPmtSummary);
                badPMTStatusInLaserRunData_->add(aVersionSummary);
            } else {
                int thisPMT = atoi(row[1]);
                if (!badPMTStatusInLaserRunData_->contains(thisVersion, thisPMT)) {
                    PmtDataSummary aPmtSummary;
                    aPmtSummary.pmtNumber = thisPMT;
                    aPmtSummary.runCouples.insert(std::pair<int, int>
                                                  (atoi(row[2]),atoi(row[3])));
                    badPMTStatusInLaserRunData_->addPmtData(thisVersion, aPmtSummary);
                } else {
                    badPMTStatusInLaserRunData_
                    ->addEntry(thisVersion, thisPMT, 
                               std::pair<int, int>(atoi(row[2]), atoi(row[3])));
                }
            }
        }
        
        std::cout << " --- " << badPMTStatusInLaserRunData_->nEntries() 
        << " entries read " << std::endl;
        mysql_free_result(result);
        return true;
    } else {
        return false;
    }
    
}








