//
//  NemoCalibration.h
//
//  Created by Stefano Torre on 23/01/12.
//

#ifndef NEMO_NEMOCALIBRATION_H_
#define NEMO_NEMOCALIBRATION_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/NemoDataBaseManager.h"
#include "NemoMods/N3DbInterfaceModule.h"
#include <map>
#include <vector>

struct PmtCalibrationData {
  int    status;
  double alpha;
  double alphaEr;
  double resolution;
  double resolutionEr;
  double tdcFluctuation;
  int    leFlag;
  double leCoefficient;
  int    ldFlag;
  int    hsFlag;
  double ldCorrection;
  double ldCorrectionEr;
  double ltCorrection;
  double ltCorrectionEr;
  double timeShiftError;
};


class NemoCalibration : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructor and Destructor
    //-------------------------------------------------------------------------
    NemoCalibration(const std::string theName = "NemoCalibration",
                        const std::string theDecription = 
                        "Applies calibrations to calorimeter data");
    virtual ~NemoCalibration();

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
    void setUseNominalResolution(const bool aValue) { useNominalResolution_ = aValue; }
    bool useNominalResolution() const { return useNominalResolution_; }

    void setKeepNoisyPMTs(const bool aValue) { keepNoisyPMTs_ = aValue; }
private:
    const NemoDataBaseManager* db_;
    const N3DbInterfaceModule* n3db_;
    PmtCalibrationData* pmtData(int pmtNumber);
    bool checkStatus(int status, int check);
    bool goodPmtStatus(int status);
    bool lecJumps(int status);
    bool useN3Db_;
    bool useNominalResolution_;
    bool keepNoisyPMTs_;
};

#endif
