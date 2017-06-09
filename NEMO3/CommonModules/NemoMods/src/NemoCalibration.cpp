//
//  NemoCalibration.cpp
//
//  Created by Stefano Torre on 23/01/12.
//

// Nemo analysis modules and objects
#include "NemoMods/NemoCalibration.h"
#include "NemoMods/RunStatusController.h"
#include "NemoObjects/N3CalorimeterHitColl.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/NemorHeader.h"
#define SC_TDC_CH 0.053

// Hereward modules and objects
#include "Hereward/SuperNemoData/EventHeader.h"

// STL
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
NemoCalibration::NemoCalibration(const std::string theName, 
				 const std::string theDescription) :
  AppModule(theName, theDescription),
  useN3Db_(true), useNominalResolution_(false) {
  if (useN3Db_) {
    n3db_ = N3DbInterfaceModule::instance();
  } else {
    db_ = NemoDataBaseManager::instance();
  }
  keepNoisyPMTs_ = false;
}

NemoCalibration::~NemoCalibration() {
}

//-------------------------------------------------------------------------
// Operations
//-------------------------------------------------------------------------
AppResult NemoCalibration::beginJob(AppEvent *aJob) {
  return AppResult::OK;
}

AppResult NemoCalibration::beginRun(AppEvent *aRun) {
  AppResult retval = AppResult::OK;
  if (RunStatusController::instance()->currentRunIsAccepted()) {
  }
  return retval;
}

AppResult NemoCalibration::event(AppEvent *anEvent) {
  // if (RunStatusController::instance()->currentRunIsAccepted()) {

  // 1) Get the header of the event, this is needed to determine whether
  //    we are processing real or simulated data.
  StorableObject::SelectByClassName cName("EventHeader");
  EventRecord::ConstIterator eventHeader_ci(anEvent, cName);    
  if (!eventHeader_ci.is_valid()) {
    std::cout << "Error Accessing the EventHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 
  EventHeader_ch eventHeader(eventHeader_ci);

  StorableObject::SelectByClassName cName2("NemorHeader");
  EventRecord::ConstIterator nemorHeader_ci(anEvent, cName2);
  if (!nemorHeader_ci.is_valid()) {
    std::cout << "Error Accessing the NemorHeader" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  } 
  NemorHeader_ch nemorHeader(nemorHeader_ci);

  N3CalorimeterHitColl_ch theCaloHitColl;
  if (! N3CalorimeterHitColl::find(anEvent, theCaloHitColl)) {
    std::cout << "--    ERROR: No N3CalorimterHitColl in the event" << std::endl;
    anEvent->listObjects();
    return AppResult::ERROR;
  }
        
  N3CalorimeterHitColl::N3CalorimeterHitList 
    recoCaloHits = theCaloHitColl->contents();
    
  CalibCaloHitColl *calibratedHitColl = new CalibCaloHitColl();
  for (unsigned hitId = 0; hitId < recoCaloHits.size(); ++hitId) {
    N3CalorimeterHit recoHit = recoCaloHits.at(hitId);
    if (recoHit.pmtNumber() <= 1940 and (!recoHit.isNoisy() or keepNoisyPMTs_)) {
      PmtCalibrationData* calibrations = pmtData(recoHit.pmtNumber());

      // initialize calibrated hit from the reconstructed hit
      CalibCaloHit newHit(recoHit);
      newHit.setHitId(hitId);
      newHit.setStatus(calibrations->status);

      newHit.setGoodFlag(goodPmtStatus(newHit.status()));
      newHit.setLeFlag(calibrations->leFlag);
      newHit.setLdFlag(calibrations->ldFlag);
      newHit.setLdCorr(calibrations->ldCorrection);
      newHit.setLdCorrErr(calibrations->ldCorrectionEr);
      newHit.setHsFlag(calibrations->hsFlag);

      // first calculate the time of the hit in ns
      newHit.setHitTime(-recoHit.tdcCounter() * SC_TDC_CH);
      
      // 1) set energy resolution of the block. 
      if (useNominalResolution() && eventHeader->mcFlag()) {
        // In case of simulated events we use the resolutions in nemos
        if (recoHit.iobtFlag() == 0) {
          newHit.setFwhm(0.171);
        } 

        if (recoHit.iobtFlag() == 1) {
          if (recoHit.fcll() == 0 or recoHit.fcll() == 2) {
            newHit.setFwhm(0.139);
          } else if (recoHit.fcll() == 1) {
            newHit.setFwhm(0.140);
          } else {
            std::cout << "--    ERROR - NemoCalibration::event /n"
        	      << "      bad FCLL flag for hit /n" << hitId
        	      << recoHit << std::endl;
            return AppResult::ERROR;
          }
        }

        if (recoHit.iobtFlag() > 1) {
          switch (recoHit.fcll()) {
          case 0:
            newHit.setFwhm(0.158);
            break;
          case 1:
            newHit.setFwhm(0.158);
            break;
          case 2:
            newHit.setFwhm(0.169);
            break;
          case 3:
            newHit.setFwhm(0.148);
            break;
          default:
            std::cout << "--    ERROR - NemoCalibration::event /n"
        	      << "      bad FCLL flag for hit /n" << hitId
        	      << recoHit << std::endl;
            return AppResult::ERROR;
          }
        }
      } else {
        // use the resolution stored in the database
        newHit.setFwhm(calibrations->resolution);
      }

      // 2) time resolution
      double scintillationTime;
      if (eventHeader->mcFlag()) {
        // 2.1) set the value used in the simulation
        scintillationTime = 4.3;
      
        // 2.2) during the reconstructino we shoudl have saved this 
        //      value, if so use that
        if (nemorHeader->scintillationTime() > 1 and
            nemorHeader->scintillationTime() < 10) {
          scintillationTime = nemorHeader->scintillationTime();
        }

        newHit.setGammaScintillationTime(scintillationTime);
        newHit.setElectronScintillationTime(scintillationTime);
      } else {
        newHit.setGammaScintillationTime(4.1); 
        newHit.setElectronScintillationTime(4.3);
      }

      // 3) number of photo electrons
      double nPhotoElectrons = newHit.energyDeposit() *
                                pow(2.3548/newHit.fwhm(),2);

      // 3) calculate error on the time 
      //-- sigma from transit time fluctuation and TDC convertion   
      double fwhm_tr = 1.;
      double gainVariation = 0.0025;

      double gammaTimeError2 = (pow(newHit.gammaScintillationTime(),2) +
                                pow(fwhm_tr/2.3548,2))/
                               (nPhotoElectrons * (1 + gainVariation));
      double electronTimeError2 = (pow(newHit.electronScintillationTime(),2) +
                                   pow(fwhm_tr/2.3548,2))/
                                  (nPhotoElectrons * (1 + gainVariation));

      if (eventHeader->mcFlag()) {
        // in MC events we do not need to add any other
        // contribution to the time error
        newHit.setGammaTimeError(sqrt(gammaTimeError2));
        newHit.setElectronTimeError(sqrt(electronTimeError2));
      } else {
        double calibrationUncertainties2 =
          pow(calibrations->ltCorrectionEr,2) +
          pow(calibrations->timeShiftError,2) +
          pow(calibrations->tdcFluctuation,2);
        newHit.setGammaTimeError(sqrt(gammaTimeError2 +
                calibrationUncertainties2));
        newHit.setElectronTimeError(sqrt(electronTimeError2 +
                calibrationUncertainties2));
      }

      newHit.setAlpha(calibrations->alpha);
      newHit.setAlphaError(calibrations->alphaEr);

      calibratedHitColl->add(newHit);
      delete calibrations;
    } // if (recoHit.pmtNumber() <= 1940)
  } // for (unsigned hitId = 0; hitId < recoCaloHits.size(); ++hitId) 

  CalibCaloHitColl_ch collHandle(calibratedHitColl);
  if ((anEvent->append(collHandle)).is_null()) {
    std::cout 
      << "ERROR - NemoCalibration - error loading calibrated hit "
      << "colleciotn in the record"
      << std::endl;
    return AppResult::ERROR; 
  }
  // } // if (RunStatusController::instance()->currentRunIsAccepted()) 
  return AppResult::OK;
}

AppResult NemoCalibration::endRun(AppEvent *aRun) {
  return AppResult::OK;
}

AppResult NemoCalibration::endJob(AppEvent *aJob) {
  return AppResult::OK;
}

//-------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------
PmtCalibrationData* NemoCalibration::pmtData(int pmtNumber) {

  PmtCalibrationData* data = new PmtCalibrationData();
  if (useN3Db_) {

    data->status	 = n3db_->pmtStatus(pmtNumber)        ;
    if (n3db_->hasEnergyCorrection()) {
      data->alpha	 = n3db_->pmtAlpha(pmtNumber)         ;
      data->alphaEr	 = n3db_->pmtAlphaEr(pmtNumber)       ;
      data->resolution	 = n3db_->pmtResolution(pmtNumber)    ;
      data->resolutionEr = n3db_->pmtResolutionEr(pmtNumber)  ;
    } 
    if (n3db_->hasLaserTimeCorrection()) {
      data->ltCorrection   = n3db_->pmtLtCorrection(pmtNumber)  ;
      data->ltCorrectionEr = n3db_->pmtLtCorrectionEr(pmtNumber);
      data->tdcFluctuation = n3db_->pmtTdcFluctuation(pmtNumber);
    }
    if (n3db_->hasLaserEnergyCorrection()) {
      data->leFlag	  = n3db_->pmtLeFlag(pmtNumber)        ;
      data->leCoefficient = n3db_->pmtLeCoefficient(pmtNumber) ;
    }
    if (n3db_->hasLaserEnergyCorrectionLD()) {
      data->ldFlag	  = n3db_->pmtLdFlag(pmtNumber)        ;
      data->ldCorrection  = n3db_->pmtLdCorrection(pmtNumber)  ;
      data->ldCorrectionEr= n3db_->pmtLdCorrectionEr(pmtNumber);
    }
    if (n3db_->hasTimeShiftCorrection()) {
      data->timeShiftError = n3db_->pmtTimeShiftError(pmtNumber);
    }
    if (n3db_->hasHsFlag()){
      data->hsFlag = n3db_->pmtHSflag(pmtNumber);
    }
  } else {
  }
  return data;
}

bool NemoCalibration::checkStatus(int status, int check) {
  if (check < 10) return status = check;
  while (check >= 10) {
    check = check/10;
    status = status/10;
    if (check < 10) {
      return (check == status % 10);
    }
  }
  return false;
}

bool NemoCalibration::goodPmtStatus(int status) {
  bool good = true;
  
  //PM threshold was changed. TS is not valid
  if (checkStatus(status, 20)) good = false;

  //TE or TS is missing
  if (checkStatus(status, 3000) or 
      checkStatus(status, 1000) or
      checkStatus(status, 2000)) good = false;
  
  //LTC is missing or wrong
  if (checkStatus(status, 1000000) or 
      checkStatus(status, 2000000) or 
      checkStatus(status, 3000000) or 
      checkStatus(status, 4000000) or 
      checkStatus(status, 5000000) or 
      checkStatus(status, 6000000) or 
      checkStatus(status, 7000000)) good = false;
  
  return good;
}

bool NemoCalibration::lecJumps(int status) {
  bool result = false;

  if (checkStatus(status,100000) or 
      checkStatus(status,200000) or 
      checkStatus(status,300000) or 
      checkStatus(status,400000) or 
      checkStatus(status,500000) or 
      checkStatus(status,600000)) result = true;

  return result;
}
