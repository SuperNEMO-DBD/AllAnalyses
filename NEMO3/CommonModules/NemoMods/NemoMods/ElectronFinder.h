//
//  ElectronFinder.h
//
//  Created by Stefano Torre on 09/05/12.
//

#ifndef NEMO_ELECTRONFINDER_H_
#define NEMO_ELECTRONFINDER_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/NemoDataBaseManager.h"
#include "NemoMods/N3DbInterfaceModule.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/ElectronColl.h"
#include <map>
#include <vector>

class ElectronFinder : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructor and Destructor
    //-------------------------------------------------------------------------
    ElectronFinder(const std::string theName = "ElectronFinder",
                        const std::string theDecription = 
                        "Looks for electron in the event");
    virtual ~ElectronFinder();

    //-------------------------------------------------------------------------
    // Operations
    //-------------------------------------------------------------------------
    AppResult beginJob(AppEvent* aJob);
    AppResult beginRun(AppEvent* aRun);
    AppResult event(AppEvent* anEvent);
    AppResult endRun(AppEvent* aRun);
    AppResult endJob(AppEvent* aJob);
    void setDebugLevel(int value) { debugLevel_ = value;}
    
    //-------------------------------------------------------------------------
    // Accessors
    //-------------------------------------------------------------------------     
    bool      setUseLocalFit(const bool aValue) { useLocalFit_ = aValue; }
    bool      setUseElectronScintToPMTTime_(const bool aValue) { useElectronScintToPMTTime_ = aValue; }
private:
    double    calculateEnergyLoss(Electron eCand, CalibCaloHit calohit);
    AppResult createElectronFromGlobalFit(AppEvent* anEvent);
    AppResult createElectronFromLocalFit(AppEvent* anEvent);
    bool      useLocalFit_;
    bool      useElectronScintToPMTTime_;
    int       debugLevel_;
};

#endif
