//
//  NemorInputModule.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#include "NemoMods/NemorInputModule.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/N3CalorimeterHitColl.h"
#include "NemoObjects/N3TrackSegmentColl.h"
#include "Hereward/SuperNemoData/TrueGeigerHitColl.h"
#include "Hereward/SuperNemoData/TrueParticleColl.h"
#include "Hereward/SuperNemoData/TrueVertexColl.h"
#include "Hereward/SuperNemoData/EventHeader.h"
#include <cstdlib>

//------------------------------------------------------------------------------
// Constructor and Destructor
//------------------------------------------------------------------------------
NemorInputModule::NemorInputModule(const std::string theName,
                                   const std::string theDescription) :
AppNtupleInputModule(theName, theDescription) {
    execType_ = App_input;
    
    setNTupleName("h10");
    
    //--------------------------------------------------------------------------
    //    fChain->SetBranchAddress("Ievntu", &Ievntu, &b_Ievntu);
    //    fChain->SetBranchAddress("run", &run, &b_run);
    //    fChain->SetBranchAddress("date", &date, &b_date);
    //    fChain->SetBranchAddress("time", &time, &b_time);
    //    fChain->SetBranchAddress("tau_sc_save", &tau_sc_save, &b_tau_sc_save);
    addBranch("run", &runNumber_);
    addBranch("date", &date_);
    addBranch("time", &time_);
    addBranch("Ievntu", &eventNumber_);
    //--------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    //    fChain->Branch("Nsc",&Nsc,"Nsc/I");
    //    fChain->Branch("Sc",Sc,"Sc[Nsc][12]/F");    
    addBranch("Nsc", &nScintialltorHits_);
    addBranch("Sc", ScintillatorHits_);
    //--------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    //    fChain->Branch("Ngg",&Ngg,"Ngg/I");
    //    fChain->Branch("Gg",Gg,"Gg[Ngg][15]/F");
    addBranch("Ngg", &nGeigerHits_);
    addBranch("Gg", GeigerHits_);
    //--------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    //    fChain->SetBranchAddress("Nbr_tks1", &Nbr_tks1, &b_Nbr_tks1);
    //    fChain->SetBranchAddress("Nbr_pts1", Nbr_pts1, &b_Nbr_pts1);
    //    fChain->SetBranchAddress("Xc1", Xc1, &b_Xc1);
    //    fChain->SetBranchAddress("Yc1", Yc1, &b_Yc1);
    //    fChain->SetBranchAddress("Zc1", Zc1, &b_Zc1);
    //    fChain->SetBranchAddress("Radc1", Radc1, &b_Radc1);
    //    fChain->SetBranchAddress("Hc1", Hc1, &b_Hc1);
    //    fChain->SetBranchAddress("Qc1", Qc1, &b_Qc1);
    //    fChain->SetBranchAddress("Thmin1", Thmin1, &b_Thmin1);
    //    fChain->SetBranchAddress("Thmax1", Thmax1, &b_Thmax1);
    //    fChain->SetBranchAddress("Xcv1", Xcv1, &b_Xcv1);
    //    fChain->SetBranchAddress("Ycv1", Ycv1, &b_Ycv1);
    //    fChain->SetBranchAddress("Zcv1", Zcv1, &b_Zcv1);
    //    fChain->SetBranchAddress("Radcv1", Radcv1, &b_Radcv1);
    //    fChain->SetBranchAddress("Hcv1", Hcv1, &b_Hcv1);
    //    fChain->SetBranchAddress("Qcv1", Qcv1, &b_Qcv1);
    //    fChain->SetBranchAddress("Thminv1", Thminv1, &b_Thminv1);
    //    fChain->SetBranchAddress("Thmaxv1", Thmaxv1, &b_Thmaxv1);
    //    fChain->SetBranchAddress("Xcs1", Xcs1, &b_Xcs1);
    //    fChain->SetBranchAddress("Ycs1", Ycs1, &b_Ycs1);
    //    fChain->SetBranchAddress("Zcs1", Zcs1, &b_Zcs1);
    //    fChain->SetBranchAddress("Radcs1", Radcs1, &b_Radcs1);
    //    fChain->SetBranchAddress("Hcs1", Hcs1, &b_Hcs1);
    //    fChain->SetBranchAddress("Qcs1", Qcs1, &b_Qcs1);
    //    fChain->SetBranchAddress("Thmins1", Thmins1, &b_Thmins1);
    //    fChain->SetBranchAddress("Thmaxs1", Thmaxs1, &b_Thmaxs1);
    //    fChain->SetBranchAddress("X_foil1", X_foil1, &b_X_foil1);
    //    fChain->SetBranchAddress("Y_foil1", Y_foil1, &b_Y_foil1);
    //    fChain->SetBranchAddress("Z_foil1", Z_foil1, &b_Z_foil1);
    //    fChain->SetBranchAddress("Cos_dir1", Cos_dir1, &b_Cos_dir1);
    //    fChain->SetBranchAddress("Ass_foi1", Ass_foi1, &b_Ass_foi1);
    //    fChain->SetBranchAddress("Foil_me1", Foil_me1, &b_Foil_me1);
    //    fChain->SetBranchAddress("Xyz_foi1", Xyz_foi1, &b_Xyz_foi1);
    //    fChain->SetBranchAddress("X_scint1", X_scint1, &b_X_scint1);
    //    fChain->SetBranchAddress("Y_scint1", Y_scint1, &b_Y_scint1);
    //    fChain->SetBranchAddress("Z_scint1", Z_scint1, &b_Z_scint1);
    //    fChain->SetBranchAddress("Ind_sci1", Ind_sci1, &b_Ind_sci1);
    //    fChain->SetBranchAddress("Impact1", Impact1, &b_Impact1);
    //    fChain->SetBranchAddress("Ind_poi1", Ind_poi1, &b_Ind_poi1);
    //    fChain->SetBranchAddress("Ip_join1", Ip_join1, &b_Ip_join1);
    //    fChain->SetBranchAddress("Foil_na1", Foil_na1, &b_Foil_na1);
    
    addBranch("Nbr_tks1",   &nTracks1_);
    addBranch("Nbr_pts1",   nFittedPoints1_);
    addBranch("Xc1",        xCenterOfCurvature1_);
    addBranch("Yc1",        yCenterOfCurvature1_);
    addBranch("Zc1",        zCenterOfCurvature1_);
    addBranch("Radc1",      radiusOfCurvature1_);
    addBranch("Hc1",        helixPitch1_);
    addBranch("Qc1",        chargeOfTrack1_);
    addBranch("Thmin1",     thetaMin1_);
    addBranch("Thmax1",     thetaMax1_);
    
    addBranch("Xcv1",       xCenterOfCurvatureV1_);
    addBranch("Ycv1",       yCenterOfCurvatureV1_);
    addBranch("Zcv1",       zCenterOfCurvatureV1_);
    addBranch("Radcv1",     radiusOfCurvatureV1_);
    addBranch("Hcv1",       helixPitchV1_);
    addBranch("Qcv1",       chargeOfTrackV1_);
    addBranch("Thminv1",    thetaMinV1_);
    addBranch("Thmaxv1",    thetaMaxV1_);
    
    addBranch("Xcs1",       xCenterOfCurvatureS1_);
    addBranch("Ycs1",       yCenterOfCurvatureS1_);
    addBranch("Zcs1",       zCenterOfCurvatureS1_);
    addBranch("Radcs1",     radiusOfCurvatureS1_);
    addBranch("Hcs1",       helixPitchS1_);
    addBranch("Qcs1",       chargeOfTrackS1_);
    addBranch("Thmins1",    thetaMinS1_);
    addBranch("Thmaxs1",    thetaMaxS1_);
    
    addBranch("X_foil1",    xIntersectionOnFoil1_);
    addBranch("Y_foil1",    yIntersectionOnFoil1_);
    addBranch("Z_foil1",    zIntersectionOnFoil1_);
    addBranch("Cos_dir1",   directionCosine1_);
    addBranch("Ass_foi1",   isAssociatedToFoil1_);
    addBranch("Foil_me1",   foilMedium1_);
    addBranch("Xyz_foi1", 	foilCenter1_);
    
    addBranch("X_scint1",   xIntersectionOnScint1_);
    addBranch("Y_scint1",   yIntersectionOnScint1_);
    addBranch("Z_scint1",   zIntersectionOnScint1_);
    addBranch("Ind_sci1",   indexOfScintillator1_);
    addBranch("Impact1",    impactRegion1_);
    addBranch("Ind_poi1",   indexOfGeigerHits1_);
    //    addBranch("Ip_join1", Ip_join1, &b_Ip_join1);
    addBranch("Foil_na1",   foilName1_);
    
    //    fChain->SetBranchAddress("Nbr_tks2", &Nbr_tks2, &b_Nbr_tks2);
    //    fChain->SetBranchAddress("Nbr_pts2", Nbr_pts2, &b_Nbr_pts2);
    //    fChain->SetBranchAddress("Xc2", Xc2, &b_Xc2);
    //    fChain->SetBranchAddress("Yc2", Yc2, &b_Yc2);
    //    fChain->SetBranchAddress("Zc2", Zc2, &b_Zc2);
    //    fChain->SetBranchAddress("Radc2", Radc2, &b_Radc2);
    //    fChain->SetBranchAddress("Hc2", Hc2, &b_Hc2);
    //    fChain->SetBranchAddress("Qc2", Qc2, &b_Qc2);
    //    fChain->SetBranchAddress("Thmin2", Thmin2, &b_Thmin2);
    //    fChain->SetBranchAddress("Thmax2", Thmax2, &b_Thmax2);
    //    fChain->SetBranchAddress("Xcv2", Xcv2, &b_Xcv2);
    //    fChain->SetBranchAddress("Ycv2", Ycv2, &b_Ycv2);
    //    fChain->SetBranchAddress("Zcv2", Zcv2, &b_Zcv2);
    //    fChain->SetBranchAddress("Radcv2", Radcv2, &b_Radcv2);
    //    fChain->SetBranchAddress("Hcv2", Hcv2, &b_Hcv2);
    //    fChain->SetBranchAddress("Qcv2", Qcv2, &b_Qcv2);
    //    fChain->SetBranchAddress("Thminv2", Thminv2, &b_Thminv2);
    //    fChain->SetBranchAddress("Thmaxv2", Thmaxv2, &b_Thmaxv2);
    //    fChain->SetBranchAddress("Xcs2", Xcs2, &b_Xcs2);
    //    fChain->SetBranchAddress("Ycs2", Ycs2, &b_Ycs2);
    //    fChain->SetBranchAddress("Zcs2", Zcs2, &b_Zcs2);
    //    fChain->SetBranchAddress("Radcs2", Radcs2, &b_Radcs2);
    //    fChain->SetBranchAddress("Hcs2", Hcs2, &b_Hcs2);
    //    fChain->SetBranchAddress("Qcs2", Qcs2, &b_Qcs2);
    //    fChain->SetBranchAddress("Thmins2", Thmins2, &b_Thmins2);
    //    fChain->SetBranchAddress("Thmaxs2", Thmaxs2, &b_Thmaxs2);
    //    fChain->SetBranchAddress("X_foil2", X_foil2, &b_X_foil2);
    //    fChain->SetBranchAddress("Y_foil2", Y_foil2, &b_Y_foil2);
    //    fChain->SetBranchAddress("Z_foil2", Z_foil2, &b_Z_foil2);
    //    fChain->SetBranchAddress("Cos_dir2", Cos_dir2, &b_Cos_dir2);
    //    fChain->SetBranchAddress("Ass_foi2", Ass_foi2, &b_Ass_foi2);
    //    fChain->SetBranchAddress("Foil_me2", Foil_me2, &b_Foil_me2);
    //    fChain->SetBranchAddress("Xyz_foi2", Xyz_foi2, &b_Xyz_foi2);
    //    fChain->SetBranchAddress("X_scint2", X_scint2, &b_X_scint2);
    //    fChain->SetBranchAddress("Y_scint2", Y_scint2, &b_Y_scint2);
    //    fChain->SetBranchAddress("Z_scint2", Z_scint2, &b_Z_scint2);
    //    fChain->SetBranchAddress("Ind_sci2", Ind_sci2, &b_Ind_sci2);
    //    fChain->SetBranchAddress("Impact2", Impact2, &b_Impact2);
    //    fChain->SetBranchAddress("Ind_poi2", Ind_poi2, &b_Ind_poi2);
    //    fChain->SetBranchAddress("Ip_join2", Ip_join2, &b_Ip_join2);
    //    fChain->SetBranchAddress("Foil_na2", Foil_na2, &b_Foil_na2);
    
    addBranch("Nbr_tks2",   &nTracks2_);
    addBranch("Nbr_pts2",   nFittedPoints2_);
    addBranch("Xc2",        xCenterOfCurvature2_);
    addBranch("Yc2",        yCenterOfCurvature2_);
    addBranch("Zc2",        zCenterOfCurvature2_);
    addBranch("Radc2",      radiusOfCurvature2_);
    addBranch("Hc2",        helixPitch2_);
    addBranch("Qc2",        chargeOfTrack2_);
    addBranch("Thmin2",     thetaMin2_);
    addBranch("Thmax2", 	thetaMax2_);
    
    addBranch("Xcv2",       xCenterOfCurvatureV2_);
    addBranch("Ycv2",       yCenterOfCurvatureV2_);
    addBranch("Zcv2",       zCenterOfCurvatureV2_);
    addBranch("Radcv2",     radiusOfCurvatureV2_);
    addBranch("Hcv2",       helixPitchV2_);
    addBranch("Qcv2",       chargeOfTrackV2_);
    addBranch("Thminv2",    thetaMinV2_);
    addBranch("Thmaxv2",    thetaMaxV2_);
    
    addBranch("Xcs2",       xCenterOfCurvatureS2_);
    addBranch("Ycs2",       yCenterOfCurvatureS2_);
    addBranch("Zcs2",       zCenterOfCurvatureS2_);
    addBranch("Radcs2",     radiusOfCurvatureS2_);
    addBranch("Hcs2",       helixPitchS2_);
    addBranch("Qcs2",       chargeOfTrackS2_);
    addBranch("Thmins2",    thetaMinS2_);
    addBranch("Thmaxs2", 	thetaMaxS2_);
    
    addBranch("X_foil2",    xIntersectionOnFoil2_);
    addBranch("Y_foil2", 	yIntersectionOnFoil2_);
    addBranch("Z_foil2", 	zIntersectionOnFoil2_);
    addBranch("Cos_dir2",   directionCosine2_);
    addBranch("Ass_foi2",   isAssociatedToFoil2_);
    addBranch("Foil_me2",   foilMedium2_);
    addBranch("Xyz_foi2",   foilCenter2_);
    
    addBranch("X_scint2",   xIntersectionOnScint2_);
    addBranch("Y_scint2",   yIntersectionOnScint2_);
    addBranch("Z_scint2",   zIntersectionOnScint2_);
    addBranch("Ind_sci2",   indexOfScintillator2_);
    addBranch("Impact2",    impactRegion2_);
    addBranch("Ind_poi2",   indexOfGeigerHits2_);
    //    addBranch("Ip_join2", Ip_join2, &b_Ip_join2);
    addBranch("Foil_na2",   foilName2_);
    
    //--------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    //    fChain->Branch("tau_sc_save",&Nsc,"tau_sc_save/F");
    //    fChain->Branch("Nvntu",&Nvntu,"Nvntu/I");
    //    fChain->Branch("Xvntu",Xvntu,"Xvntu[Nvntu]/F");
    //    fChain->Branch("Yvntu",Yvntu,"Yvntu[Nvntu]/F");
    //    fChain->Branch("Zvntu",Zvntu,"Zvntu[Nvntu]/F");
    //    fChain->Branch("Tofvntu",Tofvntu,"Tofvntu[Nvntu]/F");
    addBranch("Nvntu", &nTrueVertices_);
    addBranch("Xvntu", xOfTrueVertex_);
    addBranch("Yvntu", yOfTrueVertex_);
    addBranch("Zvntu", zOfTrueVertex_);
    addBranch("Tofvntu", tOfTrueVertex_);
    //--------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------
    //    fChain->SetBranchAddress("Ntntu", &Ntntu, &b_Ntntu);
    //    fChain->SetBranchAddress("Pxntu", Pxntu, &b_Pxntu);
    //    fChain->SetBranchAddress("Pyntu", Pyntu, &b_Pyntu);
    //    fChain->SetBranchAddress("Pzntu", Pzntu, &b_Pzntu);
    //    fChain->SetBranchAddress("Toftntu", Toftntu, &b_Toftntu);
    //    fChain->SetBranchAddress("Ivntu", Ivntu, &b_Ivntu);
    //    fChain->SetBranchAddress("Ipntu", Ipntu, &b_Ipntu);
    addBranch("Ntntu",      &nTrueParticles_);
    addBranch("Pxntu",      xMomentum_);
    addBranch("Pyntu",      yMomentum_);
    addBranch("Pzntu",      zMomentum_);
    addBranch("Toftntu",    tParticleGeneration_);
    addBranch("Ivntu",      vertexOfOrigin_);
    addBranch("Ipntu",      geantParticleId_);
    //--------------------------------------------------------------------------    
}

NemorInputModule::~NemorInputModule() {}

AppResult NemorInputModule::fillRecordFromNtuple(AppEvent *anEvent) {
    AppResult retVal;
    
    retVal = fillEventHeader(anEvent);
    if (retVal != AppResult::OK) {
        return retVal;
    }
    
    retVal = fillGeigerHitsData(anEvent);
    if (retVal != AppResult::OK) {
        return retVal;
    }
    
    retVal = fillScintillatorHitsData(anEvent);
    if (retVal != AppResult::OK) {
        return retVal;
    }
    
    retVal = fillTrackSegmentData(anEvent);
    if (retVal != AppResult::OK) {
        return retVal;
    }
    
    retVal = fillGeneratorData(anEvent);
    if (retVal != AppResult::OK) {
        return retVal;
    }
    
    return retVal;
}

AppResult NemorInputModule::fillEventHeader(AppEvent *anEvent) {
    EventHeader* theHeader = new EventHeader();
    theHeader->setRunNumber(abs(runNumber_));
    
    if (runNumber_ < 0) {
        theHeader->setMcFlag(true);
        theHeader->setNumberOfGeneratedEvents(time_);
        theHeader->setRunDuration(-1);
    } else {
        theHeader->setNumberOfGeneratedEvents(-1);
        theHeader->setRunDuration(time_);
    }
    
    theHeader->setEventDate(date_);
    theHeader->setEventNumber(eventNumber_);
    
    EventHeader_ch handle(theHeader);
    if ((theRecord()->append(handle)).is_null()) {
        std::cout 
        << "ERROR - fillEventHeader - error loading event header in the record"
        << std::endl;
        return AppResult::ERROR;
    }
    
    anEvent = theRecord();
    
    return AppResult::OK;
}

AppResult NemorInputModule::fillGeigerHitsData(AppEvent *anEvent) {
    
    N3GeigerHitColl         *theGeigerColl      = new N3GeigerHitColl();
    
    // fill raw an reconstructed geiger hit collections
    for (int hitId = 0; hitId < nGeigerHits_; ++hitId) {
        N3GeigerHit     theHit;
        
        theHit.setStatus            ((int)GeigerHits_[hitId][0]);
        theHit.setSectorNumber      ((int)GeigerHits_[hitId][1]);
        theHit.setSide              ((int)GeigerHits_[hitId][2]);
        theHit.setLayer             ((int)GeigerHits_[hitId][3]);
        theHit.setCellNumber        ((int)GeigerHits_[hitId][4]);
        theHit.setFastTdcContent    ((long)GeigerHits_[hitId][5]);
        theHit.setSlowTdcContent    ((long)GeigerHits_[hitId][6]);
        theHit.setBottomTdcContent  ((long)GeigerHits_[hitId][7]);
        theHit.setTopTdcContent     ((long)GeigerHits_[hitId][8]);
        theHit.setAnodePosition     ((double)GeigerHits_[hitId][9], 
                                     (double)GeigerHits_[hitId][10]);
        theHit.setZ                 ((double)GeigerHits_[hitId][11]);
        theHit.setAnodeInformation  ((double)GeigerHits_[hitId][12]);
        theHit.setZError            ((double)GeigerHits_[hitId][13]);
        theHit.setWeightReciprocal  ((double)GeigerHits_[hitId][14]);
        
        theGeigerColl->add(theHit);
    }
    
    // load collections into the EventRecord
    N3GeigerHitColl_ch hitCollHandle(theGeigerColl);
    if ((theRecord()->append(hitCollHandle)).is_null()) {
        std::cout 
        << "ERROR - fillGeigerHitsData - error loading geiger hit collection in the record"
        << std::endl;
        return AppResult::ERROR;
    }
    
    anEvent = theRecord();
    
    return AppResult::OK;
}

AppResult NemorInputModule::fillScintillatorHitsData(AppEvent *anEvent) {
    
    N3CalorimeterHitColl    *theCalColl    = new N3CalorimeterHitColl();
    
    for (int hitId = 0; hitId < nScintialltorHits_; ++hitId) {
        N3CalorimeterHit      theHit;
        
        theHit.setStatus            ((int)ScintillatorHits_[hitId][0]);
        theHit.setSectorNumber      ((int)ScintillatorHits_[hitId][1]);
        theHit.setIobtFlag          ((int)ScintillatorHits_[hitId][2]);
        theHit.setFcll              ((int)ScintillatorHits_[hitId][3]);
        theHit.setBlockNumber       ((int)ScintillatorHits_[hitId][4]);
        theHit.setAdcCounter        ((double)ScintillatorHits_[hitId][5]);
        theHit.setTdcCounter        ((double)ScintillatorHits_[hitId][6]);
        theHit.setOverThresholdFlag ((int)ScintillatorHits_[hitId][7]);
        theHit.setEnergyDeposit     ((double)ScintillatorHits_[hitId][8]*1000);
        theHit.setBlockCenter       ((double)ScintillatorHits_[hitId][9], 
                                     (double)ScintillatorHits_[hitId][10], 
                                     (double)ScintillatorHits_[hitId][11]);
        
        theCalColl->add(theHit);
    }
    
    N3CalorimeterHitColl_ch theHitsHandle(theCalColl);
    if ((theRecord()->append(theHitsHandle)).is_null()) {
        std::cout 
        << "ERROR - fillScintillatorHitsData - error loading calorimeter hits colleciotn in the record"
        << std::endl;
        return AppResult::ERROR; 
    }
    
    anEvent = theRecord();
    
    return AppResult::OK;
}

AppResult NemorInputModule::fillTrackSegmentData(AppEvent* anEvent) {
    N3TrackSegmentColl    *theSegmentColl = new N3TrackSegmentColl();
    
    // algorithms:
    // 0 - with ghost hits and cluster fit      - binary: 00
    // 1 - w/out ghost hits and cluster fit     - bianry: 01
    // 2 - with ghost hits and single hit fit   - binary: 10
    // 3 - w/out ghost hits and single hit fit  - binary: 11
    
    // first fill the tracks that use ghosts, algorithm 00 and 10;
    for (int segId= 0; segId < nTracks1_; ++segId) {
        N3TrackSegment thisSeg;
        int algorithm = 0;
        
        // First we set all data-members of the Segment object which are 
        // independent from the type of fit
        std::vector<int> hitList;
        for (int fittedHitId = 0; 
             fittedHitId < (int)nFittedPoints1_[segId]; ++fittedHitId) {
            
            hitList.push_back((int)indexOfGeigerHits1_[segId][fittedHitId]-1);
        }
        thisSeg.setGeigerHitList(hitList);   
        
        thisSeg.setIsAssociatedToFoil(isAssociatedToFoil1_[segId]);
        
        CLHEP::Hep3Vector hitOnFoil = 
        CLHEP::Hep3Vector((double)xIntersectionOnFoil1_[segId],
                          (double)yIntersectionOnFoil1_[segId],
                          (double)zIntersectionOnFoil1_[segId]);
        thisSeg.setIntersectionOnFoil(hitOnFoil);
        
        CLHEP::Hep3Vector dirCosine =
        CLHEP::Hep3Vector((double)directionCosine1_[segId][0],
                          (double)directionCosine1_[segId][1],
                          (double)directionCosine1_[segId][2]);
        
        CLHEP::Hep3Vector foilCenter = 
        CLHEP::Hep3Vector((double)foilCenter1_[segId][0],
                          (double)foilCenter1_[segId][1],
                          (double)foilCenter1_[segId][2]);
        thisSeg.setFoilCenter(foilCenter);
        
        CLHEP::Hep3Vector hitOnScint = 
        CLHEP::Hep3Vector((double)xIntersectionOnScint1_[segId],
                          (double)yIntersectionOnScint1_[segId],
                          (double)zIntersectionOnScint1_[segId]);
        thisSeg.setIntersectionOnScint(hitOnScint);
        
        thisSeg.setIndexOfScintillator(indexOfScintillator1_[segId] - 1);
        thisSeg.setImpactRegion(impactRegion1_[segId]);
        
        // now fit the information that dependend on the fit algorithm
        for (unsigned int fitId = 0; fitId < 2; ++fitId) {
            algorithm = (fitId << 1) | algorithm;            
            
            thisSeg.setAlgorithm(algorithm);
            
            TrackHelix tmpTrack;
            
            tmpTrack =
            TrackHelix((double)xCenterOfCurvature1_[segId][fitId],
                       (double)yCenterOfCurvature1_[segId][fitId],
                       (double)zCenterOfCurvature1_[segId][fitId],
                       (double)radiusOfCurvature1_ [segId][fitId],
                       (double)helixPitch1_        [segId][fitId],
                       (double)chargeOfTrack1_     [segId][fitId],
                       (double)thetaMin1_          [segId][fitId],
                       (double)thetaMax1_          [segId][fitId]);
            thisSeg.setGlobalFit(tmpTrack);
            
            tmpTrack =
            TrackHelix((double)xCenterOfCurvatureV1_[segId][fitId],
                       (double)yCenterOfCurvatureV1_[segId][fitId],
                       (double)zCenterOfCurvatureV1_[segId][fitId],
                       (double)radiusOfCurvatureV1_ [segId][fitId],
                       (double)helixPitchV1_        [segId][fitId],
                       (double)chargeOfTrackV1_     [segId][fitId],
                       (double)thetaMinV1_          [segId][fitId],
                       (double)thetaMaxV1_          [segId][fitId]);
            thisSeg.setLocalFoilFit(tmpTrack);
            
            tmpTrack =
            TrackHelix((double)xCenterOfCurvatureS1_[segId][fitId],
                       (double)yCenterOfCurvatureS1_[segId][fitId],
                       (double)zCenterOfCurvatureS1_[segId][fitId],
                       (double)radiusOfCurvatureS1_ [segId][fitId],
                       (double)helixPitchS1_        [segId][fitId],
                       (double)chargeOfTrackS1_     [segId][fitId],
                       (double)thetaMinS1_          [segId][fitId],
                       (double)thetaMaxS1_          [segId][fitId]);
            thisSeg.setLocalCaloFit(tmpTrack);
            
            theSegmentColl->add(thisSeg);
        }
    }
    
    
    // first fill the tracks that use ghosts, algorithm 00 and 10;
    for (int segId= 0; segId < nTracks2_; ++segId) {
        N3TrackSegment thisSeg;
        int algorithm = 1;
        
        // First we set all data-members of the Segment object which are 
        // independent from the type of fit
        std::vector<int> hitList;
        for (int fittedHitId = 0; 
             fittedHitId < (int)nFittedPoints2_[segId]; ++fittedHitId) {
            
            hitList.push_back((int)indexOfGeigerHits2_[segId][fittedHitId]-1);
        }
        thisSeg.setGeigerHitList(hitList);   
        
        thisSeg.setIsAssociatedToFoil(isAssociatedToFoil2_[segId]);
        
        CLHEP::Hep3Vector hitOnFoil = 
        CLHEP::Hep3Vector((double)xIntersectionOnFoil2_[segId],
                          (double)yIntersectionOnFoil2_[segId],
                          (double)zIntersectionOnFoil2_[segId]);
        thisSeg.setIntersectionOnFoil(hitOnFoil);
        
        CLHEP::Hep3Vector dirCosine =
        CLHEP::Hep3Vector((double)directionCosine2_[segId][0],
                          (double)directionCosine2_[segId][1],
                          (double)directionCosine2_[segId][2]);
        thisSeg.setDirectionCosine(dirCosine);
        
        CLHEP::Hep3Vector foilCenter = 
        CLHEP::Hep3Vector((double)foilCenter2_[segId][0],
                          (double)foilCenter2_[segId][1],
                          (double)foilCenter2_[segId][2]);
        thisSeg.setFoilCenter(foilCenter);
        
        CLHEP::Hep3Vector hitOnScint = 
        CLHEP::Hep3Vector((double)xIntersectionOnScint2_[segId],
                          (double)yIntersectionOnScint2_[segId],
                          (double)zIntersectionOnScint2_[segId]);
        thisSeg.setIntersectionOnScint(hitOnScint);
        
        thisSeg.setIndexOfScintillator(indexOfScintillator2_[segId] - 1);
        thisSeg.setImpactRegion(impactRegion2_[segId]);
        
        // now fit the information that dependend on the fit algorithm
        for (unsigned int fitId = 0; fitId < 2; ++fitId) {
            algorithm = (fitId << 1) | algorithm;            
            
            thisSeg.setAlgorithm(algorithm);
            
            TrackHelix tmpTrack;
            
            tmpTrack =
            TrackHelix((double)xCenterOfCurvature2_[segId][fitId],
                       (double)yCenterOfCurvature2_[segId][fitId],
                       (double)zCenterOfCurvature2_[segId][fitId],
                       (double)radiusOfCurvature2_ [segId][fitId],
                       (double)helixPitch2_        [segId][fitId],
                       (double)chargeOfTrack2_     [segId][fitId],
                       (double)thetaMin2_          [segId][fitId],
                       (double)thetaMax2_          [segId][fitId]);
            thisSeg.setGlobalFit(tmpTrack);
            
            tmpTrack = 
            TrackHelix((double)xCenterOfCurvatureV2_[segId][fitId],
                       (double)yCenterOfCurvatureV2_[segId][fitId],
                       (double)zCenterOfCurvatureV2_[segId][fitId],
                       (double)radiusOfCurvatureV2_ [segId][fitId],
                       (double)helixPitchV2_        [segId][fitId],
                       (double)chargeOfTrackV2_     [segId][fitId],
                       (double)thetaMinV2_          [segId][fitId],
                       (double)thetaMaxV2_          [segId][fitId]);
            thisSeg.setLocalFoilFit(tmpTrack);
            
            tmpTrack = 
            TrackHelix((double)xCenterOfCurvatureS2_[segId][fitId],
                       (double)yCenterOfCurvatureS2_[segId][fitId],
                       (double)zCenterOfCurvatureS2_[segId][fitId],
                       (double)radiusOfCurvatureS2_ [segId][fitId],
                       (double)helixPitchS2_        [segId][fitId],
                       (double)chargeOfTrackS2_     [segId][fitId],
                       (double)thetaMinS2_          [segId][fitId],
                       (double)thetaMaxS2_          [segId][fitId]);
            thisSeg.setLocalCaloFit(tmpTrack);
            
            theSegmentColl->add(thisSeg);
        }
    }
    
    N3TrackSegmentColl_ch segCollHandle(theSegmentColl);
    if ((theRecord()->append(segCollHandle)).is_null()) {
        std::cout 
        << "ERROR - fillTrackSegmentData - error loading track colleciotn in the record"
        << std::endl;
        return AppResult::ERROR; 
    }
    
    return AppResult::OK;
}

AppResult NemorInputModule::fillGeneratorData(AppEvent* anEvent) {
    TrueParticleColl    *theTruePartColl = new TrueParticleColl();
    TrueVertexColl      *theTrueVertColl = new TrueVertexColl();
    
    unsigned long firstTrueHitOfParticle = 0;
    
    for (int vertId = 0; vertId < nTrueVertices_; ++vertId) {
        TrueVertex thisVertex;
        thisVertex.setPosition((double) xOfTrueVertex_[vertId],
                               (double) yOfTrueVertex_[vertId],
                               (double) zOfTrueVertex_[vertId]);
        
        thisVertex.setTime((double) tOfTrueVertex_[vertId]);
        thisVertex.setIsVirtual(false);
        
        theTrueVertColl->add(thisVertex);
    }
    
    for (int partId = 0; partId < nTrueParticles_; ++partId) {
        TrueParticle thisParticle;
        thisParticle.setMomentum((double) xMomentum_[partId], 
                                 (double) yMomentum_[partId], 
                                 (double) zMomentum_[partId]);
        thisParticle.setGenerationTime          (tParticleGeneration_[partId]);
        thisParticle.setIndexOfAttachedVertex   (vertexOfOrigin_[partId]);
        thisParticle.setGeantParticleId         (geantParticleId_[partId]);
        
        thisParticle.setEntryPointInCalorimeter(0,0,0);        
        thisParticle.setAddressOfFirstHit(0);
        thisParticle.setNumberOfGeigerHits(0);
        
        theTruePartColl->add(thisParticle);
    }
    
    TrueParticleColl_ch partCollHandle(theTruePartColl);
    if ((theRecord()->append(partCollHandle)).is_null()) {
        std::cout 
        << "ERROR - fillGeneratorData - error loading true particles colleciotn in the record"
        << std::endl;
        return AppResult::ERROR; 
    }
    
    TrueVertexColl_ch theTrueVertexHandle(theTrueVertColl);
    if ((theRecord()->append(theTrueVertexHandle)).is_null()) {
        std::cout 
        << "ERROR - fillGeneratroData - error loading true verteces colleciotn in the record"
        << std::endl;
        return AppResult::ERROR;         
    }
    
    anEvent = theRecord();
    
    return AppResult::OK;
}

