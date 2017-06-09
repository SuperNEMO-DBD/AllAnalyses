//
//  NemorH10LocalTrackingInputMod.cpp
//
//  Created by Stefano Torre on 14/01/13.
//

#include "NemoMods/NemorH10LocalTrackingInputMod.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/N3CalorimeterHitColl.h"
#include "NemoObjects/N3TrackColl.h"
#include "NemoObjects/NemorHeader.h"
#include "Hereward/SuperNemoData/TrueGeigerHitColl.h"
#include "Hereward/SuperNemoData/TrueParticleColl.h"
#include "Hereward/SuperNemoData/TrueVertexColl.h"
#include "Hereward/SuperNemoData/EventHeader.h"
#include "NemoObjects/N3TrackSegmentColl.h"
#include <cstdlib>

//------------------------------------------------------------------------------
// Constructor and Destructor
//------------------------------------------------------------------------------
NemorH10LocalTrackingInputMod::NemorH10LocalTrackingInputMod(const std::string theName,
							     const std::string theDescription) :
AppNtupleInputModule(theName, theDescription), 
  readTrueParticleInfo_(false) {
  execType_ = App_input;
    
  setNTupleName("h10");
    
  //--------------------------------------------------------------------------
  //    fChain->Branch("run",&run,"run/I");
  //    fChain->Branch("date",&date,"date/I");
  //    fChain->Branch("time",&time,"time/I");
  //    fChain->Branch("Myievent",&Myievent,"Myievent/I");
  //    fChain->Branch("tau_sc_save", &tau_sc_save, &b_tau_sc_save);
  addBranch("run", &runNumber_);
  addBranch("date", &date_);
  addBranch("time", &time_);
  addBranch("evntime", &evntime_);
  addBranch("Myievent", &eventNumber_);
  addBranch("tau_sc_save", &tau_sc_save_);
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
  //    fChain->Branch("Nbr_tks",&Nbr_tks,"Nbr_tks/I");
  //    fChain->Branch("Nbr_pts",Nbr_pts,"Nbr_pts[Nbr_tks]/B");
  //    fChain->Branch("Ind_points",Ind_points,"Ind_points[Nbr_tks][200]/b");
  //    fChain->Branch("Xc",Xc,"Xc[Nbr_tks]/F");
  //    fChain->Branch("Yc",Yc,"Yc[Nbr_tks]/F");
  //    fChain->Branch("Zc",Zc,"Zc[Nbr_tks]/F");
  //    fChain->Branch("Radc",Radc,"Radc[Nbr_tks]/F");
  //    fChain->Branch("Hc",Hc,"Hc[Nbr_tks]/F");
  //    fChain->Branch("Ec",Ec,"Ec[Nbr_tks]/F");
  //    fChain->Branch("Dec",Dec,"Dec[Nbr_tks]/F");
  //    fChain->Branch("Qc",Qc,"Qc[Nbr_tks]/F");
  //    fChain->Branch("Prob_radc",Prob_radc,"Prob_radc[Nbr_tks]/F");
  //    fChain->Branch("Prob_hc",Prob_hc,"Prob_hc[Nbr_tks]/F");
  //    fChain->Branch("Prob_helix",Prob_helix,"Prob_helix[Nbr_tks]/F");
  //    fChain->Branch("X_foil",X_foil,"X_foil[Nbr_tks]/F");
  //    fChain->Branch("Y_foil",Y_foil,"Y_foil[Nbr_tks]/F");
  //    fChain->Branch("Z_foil",Z_foil,"Z_foil[Nbr_tks]/F");
  //    fChain->Branch("Cos_dir",Cos_dir,"Cos_dir[Nbr_tks][3]/F");
  //    fChain->Branch("X_scintil",X_scintil,"X_scintil[Nbr_tks]/F");
  //    fChain->Branch("Y_scintil",Y_scintil,"Y_scintil[Nbr_tks]/F");
  //    fChain->Branch("Z_scintil",Z_scintil,"Z_scintil[Nbr_tks]/F");
  //    fChain->Branch("Ind_scintil",Ind_scintil,"Ind_scintil[Nbr_tks]/B");
  //    fChain->Branch("Myimpact",Myimpact,"Myimpact[Nbr_tks]/B");
  addBranch("Nbr_tksc",    &nTracks_);
  addBranch("Nbr_ptsc",    nFittedPoints_);
  addBranch("Ind_pointsc", indexOfPoints_);
  addBranch("Xcc",         xCenterOfCurvature_);
  addBranch("Ycc",         yCenterOfCurvature_);
  addBranch("Zcc",         zCenterOfCurvature_);
  addBranch("Radcc",       radiusOfCurvature_);
  addBranch("Hcc",         helixPitch_);
  addBranch("Ecc",         energyOfTrack_);
  addBranch("Decc",        Dec_);
  addBranch("Qcc",         chargeOfTrack_);
  addBranch("Prob_radcc",  fitProbabilityOnHorizontalPlane_);
  addBranch("Prob_hcc",    fitProbabilityOnRThetaPlane_);
  addBranch("Prob_helixc", fitProbabilityForHelix_);
  addBranch("X_foilc",     xIntersectionOnFoil_);
  addBranch("Y_foilc",     yIntersectionOnFoil_);
  addBranch("Z_foilc",     zIntersectionOnFoil_);
  addBranch("Cos_dirc",    directionCosine_);
  addBranch("X_scintil",   xOfScintillator_);
  addBranch("Y_scintil",   yOfScintillator_);
  addBranch("Z_scintil",   zOfScintillator_);
  addBranch("Ind_scintil", scintillatorBlockId_);
  addBranch("Myimpact",    impactRegion_);
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // fChain->SetBranchAddress("Xcvc", Xcvc, &b_Xcvc);
  // fChain->SetBranchAddress("Ycvc", Ycvc, &b_Ycvc);
  // fChain->SetBranchAddress("Zcvc", Zcvc, &b_Zcvc);
  // fChain->SetBranchAddress("Radcvc", Radcvc, &b_Radcvc);
  // fChain->SetBranchAddress("Hcvc", Hcvc, &b_Hcvc);
  // fChain->SetBranchAddress("Thminvc", Thminvc, &b_Thminvc);
  // fChain->SetBranchAddress("Thmaxvc", Thmaxvc, &b_Thmaxvc);
  // fChain->SetBranchAddress("X_foilvc", X_foilvc, &b_X_foilvc);
  // fChain->SetBranchAddress("Y_foilvc", Y_foilvc, &b_Y_foilvc);
  // fChain->SetBranchAddress("Z_foilvc", Z_foilvc, &b_Z_foilvc);
  // fChain->SetBranchAddress("Cos_dirvc", Cos_dirvc, &b_Cos_dirvc);
  // fChain->SetBranchAddress("Qcvc", Qcvc, &b_Qcvc);
  addBranch("Xcvc",      xCenterOfCurvature_v_ );
  addBranch("Ycvc",      yCenterOfCurvature_v_ );
  addBranch("Zcvc",      zCenterOfCurvature_v_ );
  addBranch("Radcvc",    radiusOfCurvature_v_  );
  addBranch("Hcvc",      helixPitch_v_         );
  addBranch("Thminvc",   thetaMin_v_           );
  addBranch("Thmaxvc",   thetaMax_v_           );
  addBranch("X_foilvc",  xIntersectionOnFoil_v_);
  addBranch("Y_foilvc",  yIntersectionOnFoil_v_);
  addBranch("Z_foilvc",  zIntersectionOnFoil_v_);
  addBranch("Cos_dirvc", directionCosine_v_    );
  addBranch("Qcvc",      chargeOfTrack_v_      );
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // fChain->SetBranchAddress("Xcsc", Xcsc, &b_Xcsc);
  // fChain->SetBranchAddress("Ycsc", Ycsc, &b_Ycsc);
  // fChain->SetBranchAddress("Zcsc", Zcsc, &b_Zcsc);
  // fChain->SetBranchAddress("Radcsc", Radcsc, &b_Radcsc);
  // fChain->SetBranchAddress("Hcsc", Hcsc, &b_Hcsc);
  // fChain->SetBranchAddress("Thminsc", Thminsc, &b_Thminsc);
  // fChain->SetBranchAddress("Thmaxsc", Thmaxsc, &b_Thmaxsc);
  // fChain->SetBranchAddress("Cos_dirsc", Cos_dirsc, &b_Cos_dirsc);
  // fChain->SetBranchAddress("Qcsc", Qcsc, &b_Qcsc);
  // fChain->SetBranchAddress("X_scintsc", X_scintsc, &b_X_scintsc);
  // fChain->SetBranchAddress("Y_scintsc", Y_scintsc, &b_Y_scintsc);
  // fChain->SetBranchAddress("Z_scintsc", Z_scintsc, &b_Z_scintsc);
  addBranch("Xcsc",      xCenterOfCurvature_s_);
  addBranch("Ycsc",      yCenterOfCurvature_s_);
  addBranch("Zcsc",      zCenterOfCurvature_s_);
  addBranch("Radcsc",    radiusOfCurvature_s_ );
  addBranch("Hcsc",      helixPitch_s_        );
  addBranch("Thminsc",   thetaMin_s_          );
  addBranch("Thmaxsc",   thetaMax_s_          );
  addBranch("Cos_dirsc", directionCosine_s_   );
  addBranch("Qcsc",      chargeOfTrack_s_     );
  addBranch("X_scintsc", xOfScintillator_s_   );
  addBranch("Y_scintsc", yOfScintillator_s_   );
  addBranch("Z_scintsc", zOfScintillator_s_   );
  //--------------------------------------------------------------------------

  //--------------------------------------------------------------------------
  // ST : The following branches are not yet mapped or readout
  //    fChain->Branch("Myievent",&Myievent,"Myievent/I");
  //    fChain->Branch("Xvert",&Xvert,"Xvert/F");
  //    fChain->Branch("Yvert",&Yvert,"Yvert/F");
  //    fChain->Branch("Zvert",&Zvert,"Zvert/F");
  //    fChain->Branch("run",&run,"run/I");
  //    fChain->Branch("date",&date,"date/I");
  //    fChain->Branch("time",&time,"time/I");
  //    fChain->Branch("tau_sc_save",&Nsc,"tau_sc_save/F");
  //    fChain->Branch("Nvntu",&Nvntu,"Nvntu/I");
  //    fChain->Branch("Xvntu",Xvntu,"Xvntu[Nvntu]/F");
  //    fChain->Branch("Yvntu",Yvntu,"Yvntu[Nvntu]/F");
  //    fChain->Branch("Zvntu",Zvntu,"Zvntu[Nvntu]/F");
  //    fChain->Branch("Tofvntu",Tofvntu,"Tofvntu[Nvntu]/F");
  addBranch("Nvntu",   &nTrueVertices_);
  addBranch("Xvntu",   xOfTrueVertex_);
  addBranch("Yvntu",   yOfTrueVertex_);
  addBranch("Zvntu",   zOfTrueVertex_);
  addBranch("Tofvntu", tOfTrueVertex_);
  //--------------------------------------------------------------------------
  
  if (readTrueParticleInfo_) {
    //--------------------------------------------------------------------------
    //    fChain->Branch("Ntntu",&Ntntu,"Ntntu/I");
    //    fChain->Branch("Pxntu",Pxntu,"Pxntu[Ntntu]/F");
    //    fChain->Branch("Pyntu",Pyntu,"Pyntu[Ntntu]/F");
    //    fChain->Branch("Pzntu",Pzntu,"Pzntu[Ntntu]/F");
    //    fChain->Branch("Toftntu",Toftntu,"Tofntu[Ntntu]/F");
    //    fChain->Branch("Ivntu",Ivntu,"Ivntu[Ntntu]/b");
    //    fChain->Branch("Ipntu",Ipntu,"Ipntu[Ntntu]/b");
    //    fChain->Branch("Scxntu", Scxntu, "Scxntu[Ntntu]/F");
    //    fChain->Branch("Scyntu", Scyntu, "Scyntu[Ntntu]/F");
    //    fChain->Branch("Sczntu", Sczntu, "Sczntu[Ntntu]/F");
    //    fChain->Branch("Ngghits",Ngghits,"Ngghits[Ntntu]/I");
    //    fChain->Branch("GGside", GGside, "GGside[Ntntu][100]/I");
    //    fChain->Branch("GGrow",  GGrow,  "GGrow[Ntntu][100]/I");
    //    fChain->Branch("GGcol",  GGcol,  "GGcol[Ntntu][100]/I");
    //    fChain->Branch("GGx",    GGx,    "GGx[Ntntu][100]/F");
    //    fChain->Branch("GGy",    GGy,    "GGy[Ntntu][100]/F");
    //    fChain->Branch("GGz",    GGz,    "GGz[Ntntu][100]/F");
    addBranch("Ntntu",      &nTrueParticles_);
    addBranch("Pxntu",      xMomentum_);
    addBranch("Pyntu",      yMomentum_);
    addBranch("Pzntu",      zMomentum_);
    addBranch("Toftntu",    tParticleGeneration_);
    addBranch("Ivntu",      vertexOfOrigin_);
    addBranch("Ipntu",      geantParticleId_);
    //-------------------------------------------------------------------------- 
  }
  n3db_ = N3DbInterfaceModule::instance();
  lastObsRun_ = -1;
  }

NemorH10LocalTrackingInputMod::~NemorH10LocalTrackingInputMod() {}

AppResult NemorH10LocalTrackingInputMod::fillRecordFromNtuple(AppEvent *anEvent) {
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
    
  retVal = fillTrackingData(anEvent);
  if (retVal != AppResult::OK) {
    return retVal;
  }

  retVal = fillLocalTrackingData(anEvent);
  if (retVal != AppResult::OK) {
    return retVal;
  }
    
  retVal = fillGeneratorData(anEvent);
  if (retVal != AppResult::OK) {
    return retVal;
  }
    
  return retVal;
}

AppResult NemorH10LocalTrackingInputMod::fillEventHeader(AppEvent *anEvent) {
  EventHeader* theHeader = new EventHeader();
  theHeader->setRunNumber(abs(runNumber_));

  NemorHeader* theNHeader = new NemorHeader();  
  if (lastObsRun_ != abs(runNumber_)) {
    n3db_->loadRunData(abs(runNumber_));
    lastObsRun_ = abs(runNumber_);
  }

  if (runNumber_ < 0) {	      
    theHeader->setMcFlag(true);
    // keep these for now for compatibility with existing code
    theHeader->setNumberOfGeneratedEvents(time_);
    theHeader->setRunDuration(n3db_->runTime());

    // this is the new header
    theNHeader->setNumberOfGeneratedEvents(time_);
    theNHeader->setRunDuration(n3db_->runTime());
  } else {
    // keep these for now for compatibility with existing code
    theHeader->setNumberOfGeneratedEvents(-1);
    theHeader->setRunDuration(time_);

    // this is the new header
    theNHeader->setNumberOfGeneratedEvents(-1);
    theNHeader->setRunDuration(time_);
  }

  theNHeader->setEventTimeStamp(evntime_, date_);
    
  theHeader->setEventDate(date_);
  theHeader->setEventNumber(eventNumber_);


  theNHeader->setScintillationTime(tau_sc_save_);

  EventHeader_ch handle(theHeader);
  if ((theRecord()->append(handle)).is_null()) {
    std::cout 
      << "ERROR - fillEventHeader - error loading event header in the record"
      << std::endl;
    return AppResult::ERROR;
  }

  NemorHeader_ch nHandle(theNHeader);
  if ((theRecord()->append(nHandle)).is_null()) {
    std::cout 
      << "ERROR - fillEventHeader - error loading nemor header in the record"
      << std::endl;
    return AppResult::ERROR;
  }
    
  anEvent = theRecord();
    
  return AppResult::OK;
}

AppResult NemorH10LocalTrackingInputMod::fillGeigerHitsData(AppEvent *anEvent) {

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

AppResult NemorH10LocalTrackingInputMod::fillScintillatorHitsData(AppEvent *anEvent) {
    
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

AppResult NemorH10LocalTrackingInputMod::fillLocalTrackingData(AppEvent* anEvent) {

  N3TrackSegmentColl    *theSegmentColl = new N3TrackSegmentColl();
    
  // algorithms:
  // 0 - with ghost hits and cluster fit      - binary: 00
  // 1 - w/out ghost hits and cluster fit     - bianry: 01
  // 2 - with ghost hits and single hit fit   - binary: 10
  // 3 - w/out ghost hits and single hit fit  - binary: 11
    
  for (int trId= 0; trId < nTracks_; ++trId) {
    N3TrackSegment thisSeg;
    int algorithm = 0;
        
    // First we set all data-members of the Segment object which are 
    // independent from the type of fit
    std::vector<int> hitList;
    for (int fittedHitId = 0; 
	 fittedHitId < (int)nFittedPoints_[trId]; ++fittedHitId) {
            
      hitList.push_back((int)indexOfPoints_[trId][fittedHitId]-1);
    }
    thisSeg.setGeigerHitList(hitList);   
        
    CLHEP::Hep3Vector hitOnFoil = 
      CLHEP::Hep3Vector((double)xIntersectionOnFoil_[trId],
			(double)yIntersectionOnFoil_[trId],
			(double)zIntersectionOnFoil_[trId]);
    thisSeg.setIntersectionOnFoil(hitOnFoil);
        
    hitOnFoil = 
      CLHEP::Hep3Vector((double)xIntersectionOnFoil_v_[trId],
			(double)yIntersectionOnFoil_v_[trId],
			(double)zIntersectionOnFoil_v_[trId]);
    thisSeg.setIntersectionOnFoil_foil(hitOnFoil);
        
    CLHEP::Hep3Vector dirCosine =
      CLHEP::Hep3Vector((double)directionCosine_[trId][0],
			(double)directionCosine_[trId][1],
			(double)directionCosine_[trId][2]);
    thisSeg.setDirectionCosine(dirCosine);

    dirCosine =
      CLHEP::Hep3Vector((double)directionCosine_v_[trId][0],
			(double)directionCosine_v_[trId][1],
			(double)directionCosine_v_[trId][2]);
    thisSeg.setDirectionCosine_foil(dirCosine);

    dirCosine =
      CLHEP::Hep3Vector((double)directionCosine_s_[trId][0],
			(double)directionCosine_s_[trId][1],
			(double)directionCosine_s_[trId][2]);
    thisSeg.setDirectionCosine_scint(dirCosine);

    thisSeg.setFoilCenter(CLHEP::Hep3Vector(0,0,0)); // this value is used in the joint tracking
        
    CLHEP::Hep3Vector hitOnScint = 
      CLHEP::Hep3Vector((double)xOfScintillator_[trId],
			(double)yOfScintillator_[trId],
			(double)zOfScintillator_[trId]);
    thisSeg.setIntersectionOnScint(hitOnScint);
        
    hitOnScint = 
      CLHEP::Hep3Vector((double)xOfScintillator_s_[trId],
			(double)yOfScintillator_s_[trId],
			(double)zOfScintillator_s_[trId]);
    thisSeg.setIntersectionOnScint_scint(hitOnScint);
        
    thisSeg.setIndexOfScintillator(scintillatorBlockId_[trId] - 1);
    thisSeg.setImpactRegion(impactRegion_[trId]);
        
    thisSeg.setAlgorithm(algorithm);
            
    TrackHelix tmpTrack;
            
    tmpTrack =
      TrackHelix((double)xCenterOfCurvature_[trId],
		 (double)yCenterOfCurvature_[trId],
		 (double)zCenterOfCurvature_[trId],
		 (double)radiusOfCurvature_ [trId],
		 (double)helixPitch_        [trId],
		 (double)chargeOfTrack_     [trId]);
    thisSeg.setGlobalFit(tmpTrack);
            
    tmpTrack =
      TrackHelix((double)xCenterOfCurvature_v_[trId],
		 (double)yCenterOfCurvature_v_[trId],
		 (double)zCenterOfCurvature_v_[trId],
		 (double)radiusOfCurvature_v_ [trId],
		 (double)helixPitch_v_        [trId],
		 (double)chargeOfTrack_v_     [trId],
		 (double)thetaMin_v_          [trId],
		 (double)thetaMax_v_          [trId]);
    thisSeg.setLocalFoilFit(tmpTrack);
            
    tmpTrack =
      TrackHelix((double)xCenterOfCurvature_s_[trId],
		 (double)yCenterOfCurvature_s_[trId],
		 (double)zCenterOfCurvature_s_[trId],
		 (double)radiusOfCurvature_s_ [trId],
		 (double)helixPitch_s_        [trId],
		 (double)chargeOfTrack_s_     [trId],
		 (double)thetaMin_s_          [trId],
		 (double)thetaMax_s_          [trId]);
    thisSeg.setLocalCaloFit(tmpTrack);
            
    theSegmentColl->add(thisSeg);
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

AppResult NemorH10LocalTrackingInputMod::fillTrackingData(AppEvent* anEvent) {
  N3TrackColl    *theTrackColl = new N3TrackColl();
    
  for (int trackId = 0; trackId < nTracks_; ++trackId) {
    bool corruptedCalo = false;
    bool corruptedGeiger = false;
      
    N3Track thisTrack;

    std::vector<int> hitList;
    for (int fittedHitId = 0; 
	 fittedHitId < int(nFittedPoints_[trackId]); ++fittedHitId) {
      int hitId = int(indexOfPoints_[trackId][fittedHitId])-1;

      hitList.push_back(hitId);

      if (hitId >= nGeigerHits_) {
	std::cout << "WARNING - NemorH10LocalTrackingInputMod::fillTrackingData - (Run, Event) = ("
		  << abs(runNumber_) << ", " << eventNumber_ 
		  << ")\nWARNING geiger Id out of bound "
		  << hitId << " / " << nGeigerHits_ << " for track " << trackId 
		  << " corruptedGeiger flag applied to the track "
		  << std::endl;
	corruptedGeiger = true;
      }
      if (hitId < 0) {
	std::cout << "WARNING - NemorH10LocalTrackingInputMod::fillTrackingData - (Run, Event) = ("
		  << abs(runNumber_) << ", " << eventNumber_ 
		  << ")\nWARNING geiger Id out of bound "
		  << hitId << " / " << nGeigerHits_ << " for track " << trackId 
		  << " corruptedGeiger flag applied to the track "
		  << std::endl;
	corruptedGeiger = true;
      }
    }

    thisTrack.setGeigerHitList(hitList);
    thisTrack.
      setCenterOfCurvature(CLHEP::Hep3Vector((double)xCenterOfCurvature_[trackId], 
					     (double)yCenterOfCurvature_[trackId],
					     (double)zCenterOfCurvature_[trackId]));
	
    thisTrack.setRadiusOfCurvature((double)radiusOfCurvature_[trackId]);
    thisTrack.setHelixPitch((double)helixPitch_[trackId]);
    thisTrack.setSign((double)chargeOfTrack_[trackId]);
        
    thisTrack.
      setIntersectionOnFoil(CLHEP::Hep3Vector((double)xIntersectionOnFoil_[trackId],
					      (double)yIntersectionOnFoil_[trackId],
					      (double)zIntersectionOnFoil_[trackId]));
        
    CLHEP::Hep3Vector dirCosine =
      CLHEP::Hep3Vector((double)directionCosine_[trackId][0],
			(double)directionCosine_[trackId][1],
			(double)directionCosine_[trackId][2]);
    thisTrack.setDirectionCosine(dirCosine);
        
    CLHEP::Hep3Vector caloIntersection = 
      CLHEP::Hep3Vector((double)xOfScintillator_[trackId],
			(double)yOfScintillator_[trackId],
			(double)zOfScintillator_[trackId]);
    thisTrack.setIntersectionOnCalo(caloIntersection);
        
    thisTrack.setImpactRegion(atoi(&impactRegion_[trackId]));

    if (int(scintillatorBlockId_[trackId]) > nScintialltorHits_) {
      std::cout << "WARNING - NemorH10LocalTrackingInputMod::fillTrackingData - (Run, Event) = ("
		<< abs(runNumber_) << ", " << eventNumber_ 
		<< ")\nWARNING scrintillator Id out of bound "
		<< int(scintillatorBlockId_[trackId])
		<< " / "
		<< nScintialltorHits_ 
		<< " for track " << trackId 
		<< " corruptedCalo flag applied to the track "
		<< std::endl; 
      corruptedCalo = true;
    } 
    thisTrack.setCorruptedCaloFlag(corruptedCalo);
    thisTrack.setCorruptedGeigerFlag(corruptedGeiger);
    thisTrack.setIndexOfScintillator(int(scintillatorBlockId_[trackId])-1);
        
    theTrackColl->add(thisTrack);
  }
    
  N3TrackColl_ch trackCollHandle(theTrackColl);
  if ((theRecord()->append(trackCollHandle)).is_null()) {
    std::cout 
      << "ERROR - fillTrackingData - error loading track colleciotn in the record"
      << std::endl;
    return AppResult::ERROR; 
  }

  return AppResult::OK;
}

AppResult NemorH10LocalTrackingInputMod::fillGeneratorData(AppEvent* anEvent) {
  TrueVertexColl      *theTrueVertColl = new TrueVertexColl();
    
  for (int vertId = 0; vertId < nTrueVertices_; ++vertId) {
    TrueVertex thisVertex;
    thisVertex.setPosition((double) xOfTrueVertex_[vertId],
			   (double) yOfTrueVertex_[vertId],
			   (double) zOfTrueVertex_[vertId]);
                               
    thisVertex.setTime((double) tOfTrueVertex_[vertId]);
    thisVertex.setIsVirtual(false);
        
    theTrueVertColl->add(thisVertex);
  }
    
  TrueVertexColl_ch theTrueVertexHandle(theTrueVertColl);
  if ((theRecord()->append(theTrueVertexHandle)).is_null()) {
    std::cout 
      << "ERROR - fillGeneratroData - error loading true verteces colleciotn in the record"
      << std::endl;
    return AppResult::ERROR;         
  }

  if (readTrueParticleInfo_) {
    TrueParticleColl    *theTruePartColl = new TrueParticleColl();

    unsigned long firstTrueHitOfParticle = 0;
    
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
  }
  anEvent = theRecord();
    
  return AppResult::OK;
}

























