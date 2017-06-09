//
//  NemorInputModule.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#ifndef NEMO_NEMORINPUTMODULE_H_
#define NEMO_NEMORINPUTMODULE_H_
#include "Hereward/SuperNemoProcessing/AppNtupleInputModule.h"

// forward declaration of classes: let the compiler know that somewhere a class with
// this name has been defined
class CalorimeterHit;
class GeigerHit;
class TrueGeigerHit;

class NemorInputModule : public AppNtupleInputModule {
public:
    //------------------------------------------------------------
    // Constructor and Destructor
    //------------------------------------------------------------
    NemorInputModule(const std::string theName = "NemorInputModule", 
                          const std::string theDescription = "");
    virtual ~NemorInputModule();
    
    // Inherited:
    //AppResult           childInitIOSystem();
    //AppResult           childBeginJob(AppEvent* aJob);
    //AppResult           childBeginRun(AppEvent* aRun);
    //AppResult           nextEvent(AppStopType& theDispatchStopType);
    //AppResult           fillEvent(AppEvent* event);
    
    AppResult           fillRecordFromNtuple(AppEvent* anEvent);
    
    // Inherited:
    //------------------------------------------------------------
	// Accessors for input definition variable
    //------------------------------------------------------------
    //std::string dataSource() const;
    //std::string dataFormat() const;    
    //std::string dataInputList() const;
    //std::string nTupleName() const;
    //void setDataSource      (const std::string aSource);
    //void setDataFormat      (const std::string aFormat);
    //void setDataInputList   (const std::string aInputList);
    //void setNTupleName      (const std::string aNTupleName);
    
    //protected:    
    //------------------------------------------------------------
	// Accessors for addition of branches to the ntuple
    //------------------------------------------------------------
    //AppResult addBranch(std::string theBranchName, void* theValue);
    
private:
    //------------------------------------------------------------
	// Private Methods
    //------------------------------------------------------------
    AppResult fillGeigerHitsData(AppEvent* anEvent);
    AppResult fillScintillatorHitsData(AppEvent* anEvent);
    AppResult fillTrackSegmentData(AppEvent* anEvent);
    AppResult fillGeneratorData(AppEvent* anEvent);
    AppResult fillEventHeader(AppEvent* anEvent);
    
    int           nScintialltorHits_;
    float         ScintillatorHits_[2000][12];   //[Nsc]
    /**--
     *--   SCINTILLATOR DATA:
     *--   NSC         : NUMBER OF SCINTILLATORS HIT (ISC RUNS FROM 1 TO NSC)
     *--   SC(1,ISC)   : PM STATUS
     *--   SC(2,ISC)   : SECTOR NUMBER (0-19 AS IN KDIGI)
     *--   SC(3,ISC)   : IOBT FLAG (0- 3 AS IN KDIGI)
     *--   SC(4,ISC)   : FCLL    (0- 3 AS IN KDIGI)
     *--   SC(5,ISC)   : BLOC NUMBER (0-16 AS IN KDIGI)
     *--   SC(6,ISC)   : ADC CONTENT OF THE SCINTILLATOR HIT
     *--   SC(7,ISC)   : TDC CONTENT OF THE SCINTILLATOR HIT
     *--   SC(8,ISC)   : FLAG    SET TO 1 IF SIGNAL ABOVE HIGH THRESHOLD
     *--   SC(9,ISC)   : ENERGY DEPOSIT (GeV)
     *--   SC(10,ISC)  : X COORDINATE OF THE FRONT FACE OF THE SCINTILLATOR HIT
     *--                 (M.R.S.)
     *--   SC(11,I`SC)  : Y COORDINATE OF THE FRONT FACE OF THE SCINTILLATOR HIT
     *--                 (M.R.S.)
     *--   SC(12,ISC)  : Z COORDINATE OF THE FRONT FACE OF THE SCINTILLATOR HIT
     *--                 (M.R.S.)
     **/

    int           nGeigerHits_;
    float         GeigerHits_[3000][15];   //[Ngg]
    /**--   GEIGER CELL DATA:
     *--   NGG         : NUMBER OF CELLS HIT (IGG RUNS FROM 1 TO NGG)
     *--   GG(1,IGG)   : WSTATUS
     *--   GG(2,IGG)   : SECTOR NUMBER (0-19 AS IN KDIGI)
     *--   GG(3,IGG)   : IO FLAG (0- 1 AS IN KDIGI)
     *--   GG(4,IGG)   : ABCD..I FLAG  (0- 8 AS IN KDIGI)
     *--   GG(5,IGG)   : CELL NUMBER
     *--   GG(6,IGG)   : FAST TDC CONTENT
     *--   GG(7,IGG)   : SLOW TDC CONTENT
     *--   GG(8,IGG)   : TDC CONTENT FOR CATHODE 1 (BOTTOM)
     *--   GG(9,IGG)   : TDC CONTENT FOR CATHODE 1 (TOP)
     *--   GG(10,IGG)  : X COORDINATE OF THE WIRE HIT (M.R.S.)
     *--   GG(11,IGG)  : Y COORDINATE OF THE WIRE HIT (M.R.S.)
     *--   GG(12,IGG)  : Z COORDINATE OF THE HIT (M.R.S.) -
     *--                 = 0. IF THE Z COORDINATE IS NOT  MEASURED
     *--   GG(13,IGG)  : ELECTRON DRIFT DISTANCE FOR FAST HITS -
     *--                 TIME (ns) FOR DELAYED HITS
     *--   GG(14,IGG)  : ERROR ON THE Z COORDINATE OF THE HIT (M.R.S.) -
     *--                 >= 5000. IF THE Z COORDINATE IS NOT OR POORLY MEASURED
     *--   GG(15,IGG)  : RECIPROCAL OF THE WEIGHT USED FOR CIRCLE FIT -
     *--                 FIXED TO 1.cm FOR DELAYED HITS
     **/

    int             nTracks1_;
    unsigned char   nFittedPoints1_[10];   //[Nbr_tks1]
    
    float           xCenterOfCurvature1_[10][2];   //[Nbr_tks1]
    float           yCenterOfCurvature1_[10][2];   //[Nbr_tks1]
    float           zCenterOfCurvature1_[10][2];   //[Nbr_tks1]
    float           radiusOfCurvature1_[10][2];   //[Nbr_tks1]
    float           helixPitch1_[10][2];   //[Nbr_tks1]
    float           chargeOfTrack1_[10][2];   //[Nbr_tks1]
    float           thetaMin1_[10][2];   //[Nbr_tks1]
    float           thetaMax1_[10][2];   //[Nbr_tks1]

    float           xCenterOfCurvatureV1_[10][2];   //[Nbr_tks1]
    float           yCenterOfCurvatureV1_[10][2];   //[Nbr_tks1]
    float           zCenterOfCurvatureV1_[10][2];   //[Nbr_tks1]
    float           radiusOfCurvatureV1_[10][2];   //[Nbr_tks1]
    float           helixPitchV1_[10][2];   //[Nbr_tks1]
    float           chargeOfTrackV1_[10][2];   //[Nbr_tks1]
    float           thetaMinV1_[10][2];   //[Nbr_tks1]
    float           thetaMaxV1_[10][2];   //[Nbr_tks1]
    
    float           xCenterOfCurvatureS1_[10][2];   //[Nbr_tks1]
    float           yCenterOfCurvatureS1_[10][2];   //[Nbr_tks1]
    float           zCenterOfCurvatureS1_[10][2];   //[Nbr_tks1]
    float           radiusOfCurvatureS1_[10][2];   //[Nbr_tks1]
    float           helixPitchS1_[10][2];   //[Nbr_tks1]
    float           chargeOfTrackS1_[10][2];   //[Nbr_tks1]
    float           thetaMinS1_[10][2];   //[Nbr_tks1]
    float           thetaMaxS1_[10][2];   //[Nbr_tks1]
    
    float           xIntersectionOnFoil1_[10];   //[Nbr_tks1]
    float           yIntersectionOnFoil1_[10];   //[Nbr_tks1]
    float           zIntersectionOnFoil1_[10];   //[Nbr_tks1]
    float           directionCosine1_[10][3];   //[Nbr_tks1]
    unsigned char   isAssociatedToFoil1_[10];   //[Nbr_tks1]
    int             foilMedium1_[10];   //[Nbr_tks1]
    float           foilCenter1_[10][3];   //[Nbr_tks1]
    float           xIntersectionOnScint1_[10];   //[Nbr_tks1]
    float           yIntersectionOnScint1_[10];   //[Nbr_tks1]
    float           zIntersectionOnScint1_[10];   //[Nbr_tks1]
    unsigned short  indexOfScintillator1_[10];   //[Nbr_tks1]
    int             impactRegion1_[10];   //[Nbr_tks1]
    int             indexOfGeigerHits1_[10][200];   //[Nbr_tks1]
    char            foilName1_[10];
    //    char            Ip_join1[10][2];   //[Nbr_tks1]

    int             nTracks2_;
    unsigned char   nFittedPoints2_[10];   //[Nbr_tks1]
    
    float           xCenterOfCurvature2_[10][2];   //[Nbr_tks1]
    float           yCenterOfCurvature2_[10][2];   //[Nbr_tks1]
    float           zCenterOfCurvature2_[10][2];   //[Nbr_tks1]
    float           radiusOfCurvature2_[10][2];   //[Nbr_tks1]
    float           helixPitch2_[10][2];   //[Nbr_tks1]
    float           chargeOfTrack2_[10][2];   //[Nbr_tks1]
    float           thetaMin2_[10][2];   //[Nbr_tks1]
    float           thetaMax2_[10][2];   //[Nbr_tks1]
    
    float           xCenterOfCurvatureV2_[10][2];   //[Nbr_tks1]
    float           yCenterOfCurvatureV2_[10][2];   //[Nbr_tks1]
    float           zCenterOfCurvatureV2_[10][2];   //[Nbr_tks1]
    float           radiusOfCurvatureV2_[10][2];   //[Nbr_tks1]
    float           helixPitchV2_[10][2];   //[Nbr_tks1]
    float           chargeOfTrackV2_[10][2];   //[Nbr_tks1]
    float           thetaMinV2_[10][2];   //[Nbr_tks1]
    float           thetaMaxV2_[10][2];   //[Nbr_tks1]
    
    float           xCenterOfCurvatureS2_[10][2];   //[Nbr_tks1]
    float           yCenterOfCurvatureS2_[10][2];   //[Nbr_tks1]
    float           zCenterOfCurvatureS2_[10][2];   //[Nbr_tks1]
    float           radiusOfCurvatureS2_[10][2];   //[Nbr_tks1]
    float           helixPitchS2_[10][2];   //[Nbr_tks1]
    float           chargeOfTrackS2_[10][2];   //[Nbr_tks1]
    float           thetaMinS2_[10][2];   //[Nbr_tks1]
    float           thetaMaxS2_[10][2];   //[Nbr_tks1]
    
    float           xIntersectionOnFoil2_[10];   //[Nbr_tks1]
    float           yIntersectionOnFoil2_[10];   //[Nbr_tks1]
    float           zIntersectionOnFoil2_[10];   //[Nbr_tks1]
    float           directionCosine2_[10][3];   //[Nbr_tks1]
    unsigned char   isAssociatedToFoil2_[10];   //[Nbr_tks1]
    int             foilMedium2_[10];   //[Nbr_tks1]
    float           foilCenter2_[10][3];   //[Nbr_tks1]
    float           xIntersectionOnScint2_[10];   //[Nbr_tks1]
    float           yIntersectionOnScint2_[10];   //[Nbr_tks1]
    float           zIntersectionOnScint2_[10];   //[Nbr_tks1]
    unsigned short  indexOfScintillator2_[10];   //[Nbr_tks1]
    int             impactRegion2_[10];   //[Nbr_tks1]
    int             indexOfGeigerHits2_[10][200];   //[Nbr_tks1]
    char            foilName2_[10];
    //    char            Ip_join1[10][2];   //[Nbr_tks1]

    
    /** TRACKS
     *--   NBR_TKS         : NUMBER OF RECONSTRUCTED TRACKS
     *--   NBR_PTS(IT)     : NUMBER OF ASSOCIATED HITS ON TRACK IT
     *--   IND_POINTS(NP,IT) IGG VALUE FOR HIT NP ON TRACK IT
     *--   XC(IT)          : X COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
     *--   YC(IT)          : Y COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
     *--   ZC(IT)          : Z COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
     *--   RADC(IT)        : RADIUS OF CURVATURE OF TRACK IT
     *--   HC(IT)          : HELIX PITCH OF TRACK IT
     *--   QC(IT)          : CHARGE OF TRACK IT CALCULATED FROM THE CURVATURE
     *--   X_FOIL(IT)      : X COORDINATE OF THE INTERSECTION OF TRACK IT
     *--   WITH THE FOIL CYLINDER (FROM TRACKING OR FROM TK_FOIL)
     *--   Y_FOIL(IT)      : Y COORDINATE OF THE INTERSECTION OF TRACK IT
     *--   WITH THE FOIL CYLINDER (FROM TRACKING OR FROM TK_FOIL)
     *--   Z_FOIL(IT)      : Z COORDINATE OF THE INTERSECTION OF TRACK IT
     *--   WITH THE FOIL CYLINDER (FROM TRACKING OR FROM TK_FOIL)
     *--   COS_DIR(3,IT)   : DIRECTION COSINES OF TRACK IT
     *--   (FROM TRACKING OR FROM TRACK FIT AND INTERSECTION WITH THE FOIL)
     *--   ASS_FOIL(IT)    : .TRUE. IF THE TRACK IT ORIGINATES FROM A FOIL
     *--   (.FALSE. OTHERWISE)
     *--   FOIL_NAM(IT)    : NAME OF THE FOIL ORIGIN OF TRACK IT
     *--   FOIL_MED(IT)    : MEDIUM NUMBER OF THE FOIL ORIGIN OF TRACK IT
     *--   XYZ_FOIL(3,IT)  : COORDINATES OF THE CENTER OF FOIL_NAM(IT)
     *--   X_SCINT(IT)     : X COORDINATE OF THE INTERSECTION OF TRACK IT
     *--   WITH THE SCINTILLATOR HIT
     *--   Y_SCINT(IT)     : Y COORDINATE OF THE INTERSECTION OF TRACK IT
     *--   WITH THE SCINTILLATOR HIT
     *--   Z_SCINT(IT)     : Z COORDINATE OF THE INTERSECTION OF TRACK IT
     *--   WITH THE SCINTILLATOR HIT
     *--   IND_SCINT(IT)   : ISC VALUE OF THE SCINTILLATOR ASSOCIATED TO TRACK IT
     *--   IMPACT(IT)      : IMPACT REGION OF THE TRACK ONTO THE SCINTILLATOR BLOCK
     */
    int           eventNumber_;
    
    int     runNumber_;  // event RUN number for data, for MC = -run 
                         // which conditions used for detector simulation
    int     date_;  // event date
    int     time_;  // duration of run in s RAW data, number MC generated for MC
    float   tau_sc_save_;  // scintillator decay constant

    /** KINEMATICS SECTION
     True MC information about particles generated. Stored only if reconstructed with special flag for nemor. Majority of reco files do not have it due to filesize issue.
     
     c     GENERATED DATA:
     c     NVNTU    NUMBER OF VERTICES
     c     XVNTU    X COORDINATE OF THE VERTEX
     c     YVNTU    Y COORDINATE OF THE VERTEX
     c     ZVNTU    Z COORDINATE OF THE VERTEX
     c     TOFVNTU  TIME OF CREATION OF VERTEX
     c     NTNTU    NUMBER OF TRACKS
     c     PXNTU    PX OF THE TRACK
     c     PYNTU    PY OF THE TRACK
     c     PZNTU    PZ OF THE TRACK
     c     TOFTNTU  TIME OF CREATION OF TRACK
     c     IVNTU    VERTEX OF ATTACHMENT
     c     IPNTU    GEANT PARTICLE TYPE
     c
     c     --- DSW, 18.08.10    The following is an extension for X-wall studies ---
     c
     c     SCXNTU   X COORDINATE OF SCINTILLATOR HIT
     c     SCYNTU   Y COORDINATE OF SCINTILLATOR HIT
     c     SCZNTU   Z COORDINATE OF SCINTILLATOR HIT
     c     NGGHITS  NUMBER OF GEIGR HITS LEFT BY THIS PARTICLE
     c     GGSIDE   GEIGER HIT SIDE
     c     GGROW    GEIGER HIT ROW
     c     GGCOL    GEIGER HIT COLUMN
     c     GGX      GEIGER HIT X
     c     GGY      GEIGER HIT Y
     c     GGZ      GEIGER HIT X
     
     **/

    bool          trueMC_flag_; // indicates if true MC present in the file
    int           nTrueVertices_;
    float         xOfTrueVertex_[7];        //[Nvntu]
    float         yOfTrueVertex_[7];        //[Nvntu]
    float         zOfTrueVertex_[7];        //[Nvntu]
    float         tOfTrueVertex_[7];      //[Nvntu]

    int           nTrueParticles_;
    float         xMomentum_[31];       //[Ntntu]
    float         yMomentum_[31];       //[Ntntu]
    float         zMomentum_[31];       //[Ntntu]
    float         tParticleGeneration_[31];     //[Ntntu]
    char          vertexOfOrigin_[31];       //[Ntntu]
    unsigned char geantParticleId_[31];       //[Ntntu]
};


#endif
