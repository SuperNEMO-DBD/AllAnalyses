//
//  SeExtEGCuts.h
//
//  Created by James Mott from 15/11/12
//

#ifndef SEEXTEGCUTS_H_
#define SEEXTEGCUTS_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoUtils/SectorData.h"
#include "NemoUtils/AngularCorrection.h"
#include "NemoUtils/RadonWeight.h"
#include "JEM_Analysis/HotSpots.h"
#include "NemoUtils/SFoilSide.h"

class SeExtEGCuts : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    SeExtEGCuts(const std::string theName = "SeExtEGCuts",
               const std::string theDescription = "");
    virtual ~SeExtEGCuts();
  
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
    double      gammaEnergy_;
    double      trackLength_;
    double      trackSign_;
    double      vertexR_, vertexZ_, vertexSector_;
    double      trueVertexR_, trueVertexZ_, trueVertexSector_;
    int         vertexLocation_;
    int         scintLocation_;
    double      radonWeight_, bi210Weight_;
    int         foilSide_;
    double      gammaLowEnergy_[9];
    int         nLowEGammas_;
    double      probInt_, probExt_;
    double      cosTheta_;
    int         entryPoint_;
    double      eventTime_;

    int         sourceId_;
    bool        dataFlag;

    SectorData* sectorInfo_;
    RadonWeight* radonweighter_;
    HotSpots* HotSpotChecker_;
    SFoilSide*   SFoilSide_;
    
    TH1D* hElectronEnergy_;
    TH1D* hGammaEnergy_;

    TH1D* hNumLowEGammas_;
    TH1D* hTotGammaLowEnergy_;

    TH1D* hTrackLength_;    

    TH2D* hVertexPosition_;
    TH1D* hVertexR_;
    TH1D* hVertexZ_;
    TH2D* hVertexXY_;

    TH1D* hProbInt_;
    TH1D* hProbExt_;

    int TotalNumEvents_; 
    int GoodRunStatus_; 
    int OneTrack_;
    int AssociatedTrack_;
    int OneGamma_;
    int IsolatedCalos_;
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
    int Electron300keV_;
    int Gamma300keV_;
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
    int IntProb1Percent_;
    int ExtProb1Percent_;
    
    TTree* tree_;
    
};

#endif
