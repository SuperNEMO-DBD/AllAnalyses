//
//  Se1eCuts.h
//
//  Created by James Mott from 15/11/12
//

#ifndef SE1ECUTS_H_
#define SE1ECUTS_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoUtils/SectorData.h"
#include "NemoUtils/AngularCorrection.h"
#include "NemoUtils/RadonWeight.h"
#include "JEM_Analysis/HotSpots.h"
#include "NemoUtils/SFoilSide.h"

class Se1eCuts : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    Se1eCuts(const std::string theName = "Se1eCuts",
	     const std::string theDescription = "");
    virtual ~Se1eCuts();
  
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

    
    //-------------------------------------------------------------------------
    // Run Summary Structure
    //-------------------------------------------------------------------------
    struct RunSummary {
      int number;
      int length;
      int events;
      int status;
      bool accepted;
    };


private:

    int         run_;
    bool        goodRun_;
    double      electronEnergy_;
    double      trackLength_;
    double      trackSign_;
    double      vertexR_, vertexZ_, vertexSector_;
    double      trueVertexR_, trueVertexZ_, trueVertexSector_;
    int         vertexLocation_;
    int         scintLocation_;
    double      radonWeight_, bi210Weight_;
    int         foilSide_;
    double      gammaEnergy_[10];
    int         nGammas_;
    double      eventTime_;

    int         sourceId_;
    bool        dataFlag;

    SectorData* sectorInfo_;
    RadonWeight* radonweighter_;
    HotSpots* HotSpotChecker_;
    SFoilSide*   SFoilSide_;
    
    TH1D* hElectronEnergy_;

    TH1D* hNumGammas_;
    TH1D* hGammaEnergy_;

    TH1D* hTrackLength_;    

    TH2D* hVertexPosition_;
    TH1D* hVertexR_;
    TH1D* hVertexZ_;
    TH2D* hVertexXY_;

    int TotalNumEvents_; 
    int GoodRunStatus_; 
    int OneTrack_;
    int AssociatedTrack_;
    int IsolatedCalo_;
    int FrontofBlock_;
    int NoClosePetals_;
    int ElectronGoodPMT_;
    int ElectronLD_;
    int ElectronLDCorr_;
    int ElectronLDCorrErr_;
    int ElectronHS_;
    int GammasGoodPMT_;
    int GammasLD_;
    int GammasLDCorr_;
    int GammasLDCorrErr_;
    int GammasHS_;
    int ScintHas300keV_;
    int GammaEnergy_;
    int TrackLayer0or1_;
    int TrackLastLayer_;
    int IntersectsFoil_;
    int TrackLength20cm_;
    int NegativeTracks_;
    int SeleniumAngle_;
    int ZinFoil_;
    int ZNotZero_;
    int NotInHotSpot_;
    int OneNACloseHit_;
    int TwoNAFarHits_;
    int NoDelayedHit_;
    int NoDelayedCluster_;

    TTree* tree_;
    
};

#endif
