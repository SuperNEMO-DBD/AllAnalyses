//
//  Se1e1aCuts.h
//
//  Created by James Mott on 23/11/12
//

#ifndef SE1E1ACUTS_H_
#define SE1E1ACUTS_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoUtils/SectorData.h"
#include "NemoUtils/AngularCorrection.h"
#include "NemoUtils/RadonWeight.h"
#include "NemoUtils/SFoilSide.h"
#include "JEM_Analysis/HotSpots.h"


class Se1e1aCuts : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    Se1e1aCuts(const std::string theName = "Se1e1aCuts",
               const std::string theDescription = "");
    virtual ~Se1e1aCuts();
  
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
    double      electronEnergy_;
    double      trackLength_;
    double	trackSign_;
    double      vertexR_, vertexZ_, vertexSector_;
    int         vertexLocation_;
    int         scintLocation_;
    double      trueVertexR_, trueVertexZ_, trueVertexSector_;
    double      radonWeight_, bi210Weight_;
    int         foilSide_;
    double      gammaEnergy_[10];
    int         nGammas_;
    int         alphaNHits_;
    double      alphaTime_, alphaMaxTimeDiff_, alphaLength_;
    double      alphaClosestHitDistFoil_, alphaClosestHitDistWire_, alphaFurthestHitDistFoil_;
    int         alphaSide_,electronSide_;
    bool        alphaNearWire_;
    double      alphaVertexZ_, alphaVertexSector_, alphaVertexDist_;
    int         trueVertexLayer_;
    bool        goodRun_;
    double	eventTime_;

    int         sourceId_;

    SectorData*  sectorInfo_;
    RadonWeight* radonweighter_;
    HotSpots*    HotSpotChecker_;
    SFoilSide*   SFoilSide_;

    bool dataFlag;

    TH1D* hElectronEnergy_;

    TH1D* hNumGammas_;
    TH1D* hGammaEnergy_;
    TH1D* hTotGammaEnergy_;

    TH1D* hTrackLength_;    

    TH2D* hVertexPosition_;
    TH1D* hVertexR_;
    TH1D* hVertexZ_;
    TH2D* hVertexXY_;

    int TotalNumEvents_; 
    int GoodRunStatus_; 
    int OneTrack_;
    int AssociatedTrack_;
    int DelayedHits_;
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
    int Electron300keV_;
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
    int AlphaNearFoil_;
    int AlphaLess13Hits_;
    int AlphaClosestHitZ_;
    int AlphaLowestLayer_;
    int AlphaIntersectFoil_;
    int AlphaVertexDistXY_;
    int AlphaVertexDistZ_;
    int AlphaLengthLess40_;
    int AlphaMore3Hits_;

    TTree* tree_;
    
};

#endif
