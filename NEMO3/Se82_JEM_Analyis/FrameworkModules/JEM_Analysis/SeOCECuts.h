//
//  SeOCECuts.h
//
//  Created by James Mott from 15/11/12
//

#ifndef SEOCECUTS_H_
#define SEOCECUTS_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoUtils/SectorData.h"
#include "NemoUtils/AngularCorrection.h"
#include "NemoUtils/RadonWeight.h"
#include "JEM_Analysis/HotSpots.h"
#include "NemoUtils/SFoilSide.h"

class SeOCECuts : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    SeOCECuts(const std::string theName = "SeOCECuts",
                   const std::string theDescription = "");
    virtual ~SeOCECuts();
  
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

private:

    int    run_;
    int    event_;
    double energy_[2];
    double trackLength_[2];
    double trackSign_[2];
    int    nNACaloHits_;
    int    nClusters_;
    double gammaEnergy_[25];
    double clusterEnergy_[25];
    double totGammaEnergy_;
    double probInt_, probExt_;
    double cosTheta_, cosThetaWeight_;
    double vertexR_, vertexZ_, vertexSector_;
    double trueVertexR_, trueVertexZ_, trueVertexSector_;
    int    vertexLocation_;
    double radonWeight_, bi210Weight_;
    int    foilSide_;
    bool   goodRun_;
    int    scintLocation_[2];
    int    firstGgHitLayer_[2];
    int    lastGgHitLayer_[2];
    double vertexDistXY_, vertexDistZ_;
    double eventTime_;
    int    entryPoint_;

    bool dataFlag;
    SectorData* sectorInfo_;
    AngularCorrection* cosCorrection_;
    RadonWeight* radonweighter_;
    HotSpots* HotSpotChecker_;
    SFoilSide*   SFoilSide_;

    int     TotalNumEvents_;
    int     GoodorStandardRun_;
    int     TwoTracks_;
    int     AssociatedTracks_;
    int     DifferentScints_;
    int     IsolatedCalos_;
    int     FrontofBlock_;
    int     NoClosePetals_;
    int     ElectronGoodPMT_;
    int     ElectronLD_;
    int     ElectronLDCorr_;
    int     ElectronLDCorrErr_;
    int     ElectronHS_;
    int     GammasGoodPMT_;
    int     GammasLD_;
    int     GammasLDCorr_;
    int     GammasLDCorrErr_;
    int     GammasHS_;
    int     EachScint300keV_;
    int     GammaEnergy_;
    int     TwoIntersectFoil_;
    int     SeleniumAngle_;
    int     ZinFoil_;
    int     ZNotZero_;
    int     NotInHotSpot_;
    int     dXYLessThan2_;
    int     dZLessThan4_;
    int     TrackLengthMin20cm_;
    int     TrackLengthMax50cm_;
    int     TrackLengthSum80cm_;
    int     TracksFirstLayer_;
    int     TracksLastLayer_;
    int     NegativeTracks_;
    int     OneNACloseHit_;
    int     TwoNAFarHits_;
    int     NoAlphaCandidates_;
    int     IntProb4Percent_;
    int     ExtProb1Percent_;

    TTree* tree_;

};

#endif
