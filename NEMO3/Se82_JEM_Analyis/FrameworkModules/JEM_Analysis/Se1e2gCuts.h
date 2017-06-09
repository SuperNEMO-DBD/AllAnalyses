//
//  Se1e2gCuts.h
//
//  Created by James Mott from 15/11/12
//

#ifndef SE1E2GCUTS_H_
#define SE1E2GCUTS_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoUtils/SectorData.h"
#include "NemoUtils/AngularCorrection.h"
#include "NemoUtils/RadonWeight.h"
#include "JEM_Analysis/HotSpots.h"
#include "NemoUtils/SFoilSide.h"

class Se1e2gCuts : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    Se1e2gCuts(const std::string theName = "Se1e2gCuts",
               const std::string theDescription = "");
    virtual ~Se1e2gCuts();
  
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
    double      gammaEnergyMin_;
    double      gammaEnergyMax_;
    double      trackLength_;
    double      trackSign_;
    double      vertexR_, vertexZ_, vertexSector_;
    double      trueVertexR_, trueVertexZ_, trueVertexSector_;
    int         vertexLocation_;
    int         scintLocation_;
    double      radonWeight_, bi210Weight_;
    int         foilSide_;
    double      gammaLowEnergy_[8];
    int         nLowEGammas_;
    double      probIntMin_, probExtMin_;
    double      probIntMax_, probExtMax_;
    double      cosThetaEGMax_;
    double      cosThetaEGMin_;
    double      cosThetaGG_;
    double      eventTime_;

    int         sourceId_;
    bool        dataFlag;

    SectorData* sectorInfo_;
    RadonWeight* radonweighter_;
    HotSpots* HotSpotChecker_;
    SFoilSide*   SFoilSide_;
    
    TH1D* hElectronEnergy_;
    TH1D* hGammaEnergyMin_;
    TH1D* hGammaEnergyMax_;
    TH1D* hGammaEnergyTot_;

    TH1D* hNumLowEGammas_;
    TH1D* hTotGammaLowEnergy_;

    TH1D* hTrackLength_;    

    TH2D* hVertexPosition_;
    TH1D* hVertexR_;
    TH1D* hVertexZ_;
    TH2D* hVertexXY_;

    TH1D* hProbIntMin_;
    TH1D* hProbExtMin_;
    TH1D* hProbIntMax_;
    TH1D* hProbExtMax_;

    int TotalNumEvents_; 
    int GoodRunStatus_; 
    int OneTrack_;
    int AssociatedTrack_;
    int TwoGammas_;
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
    int GammaMin300keV_;
    int GammaMax1700keV_;
    int Electron300keV_;
    int ElectronSum_;
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
    int IntProbMin4Perc_;
    int ExtProbMin1Perc_;
    int IntProbMax4Perc_;
    int ExtProbMax1Perc_;
    
    TTree* tree_;
    
};

#endif
