//
//  GammaFinder.h
//
//  Created by Stefano Torre on 09/05/12.
//

#ifndef NEMO_GAMMAFINDER_H_
#define NEMO_GAMMAFINDER_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/NemoDataBaseManager.h"
#include "NemoMods/N3DbInterfaceModule.h"
#include "NemoObjects/CalibCaloHitColl.h"
#include "NemoObjects/Gamma.h"
#include <map>
#include <vector>
#include <TRandom3.h>

class GammaFinder : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructor and Destructor
    //-------------------------------------------------------------------------
    GammaFinder(const std::string theName = "GammaFinder",
	       const std::string theDecription = 
	       "Looks for gamma in the event");
    virtual ~GammaFinder();

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
    bool      setRecordHitAtFaceCenter(const bool aValue)  {recordHitAtFaceCenter = aValue;}//Default == true ( != ROOTANA)
    bool      setUseLinearEnergyRes(const bool aValue) {useLinearEnergyRes_ = aValue;}//Default == true, See DocDB 3107-v2
    bool      setUseConstantTimeRes(const bool aValue) {useConstantTimeRes_ = aValue;}//Obsolete. NOT recommended for use.
    bool      setUseSummersTimeRes(const bool aValue) {useSummersTimeRes_ = aValue;}//Obsolete. 

    void      setDebugLevel(int aValue) { debugLevel_ = aValue; }
private:

    // added S.Blot 5/1/14
    // functions to perform energy and time resolution smearing and apply optimized errors
    void applyConstantTimeRes(CalibCaloHit calohit, Gamma &gamma);  // JEM
    void applyFittedTOFParameters(CalibCaloHit calohit, Gamma &gamma); // SDB updated values 24/2/14
    void applyLinearEnergyRes(CalibCaloHit calohit, Gamma &gamma); //JEM DocDB 2812 (presentation),DocDB 3107 (note/memo)  
    
    //added by SBlot 2/7/13.
    bool recordHitAtFaceCenter; // records hit at the center of the front face of the scintillator block. See DocDB 3023 for motivation

    // JEM 9/7/12.  Flag to switch off using the improved energy resolution model, 
    // where resolution goes linearly with energy, described in DocDB 2812.
    bool useLinearEnergyRes_; // DocDB 3107-v2
    bool useConstantTimeRes_; // Obsolete. Not recommended for use.
    bool useSummersTimeRes_; // Obsolete.
    bool mcFlag_;
    TRandom3* RandomNumGen;

    //ST  3/3/14. debugLevel to control the printout
    int debugLevel_;


};

#endif
