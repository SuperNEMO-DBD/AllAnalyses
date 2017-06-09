//
//  NemorH10LocalTrackingInputMod.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on !4/01/13.
// 
//  Changes:
//
//  09/01/13 - Stefano Torre - Add information for local fit

#ifndef NEMO_NEMORH10LOCALTRACKINGINPUTMOD_H_
#define NEMO_NEMORH10LOCALTRACKINGINPUTMOD_H_
#include "Hereward/SuperNemoProcessing/AppNtupleInputModule.h"
#include "NemoMods/N3DbInterfaceModule.h"


// forward declaration of classes: let the compiler know that somewhere a class with
// this name has been defined
class CalorimeterHit;
class GeigerHit;
class TrueGeigerHit;

class NemorH10LocalTrackingInputMod : public AppNtupleInputModule {
public:
    //------------------------------------------------------------
    // Constructor and Destructor
    //------------------------------------------------------------
    NemorH10LocalTrackingInputMod(const std::string theName = "NemorH10LocalTrackingInputMod", 
                          const std::string theDescription = "");
    virtual ~NemorH10LocalTrackingInputMod();
    
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
    AppResult fillTrackingData(AppEvent* anEvent);
    AppResult fillLocalTrackingData(AppEvent* anEvent);
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
     *--   SC(11,ISC)  : Y COORDINATE OF THE FRONT FACE OF THE SCINTILLATOR HIT
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

    int           nTracks_;
    char          nFittedPoints_[10];                   //[Nbr_tks]
    unsigned char indexOfPoints_[10][200];              //[Nbr_tks]
    float         xCenterOfCurvature_[10];              //[Nbr_tks]
    float         yCenterOfCurvature_[10];              //[Nbr_tks]
    float         zCenterOfCurvature_[10];              //[Nbr_tks]
    float         radiusOfCurvature_[10];                //[Nbr_tks]
    float         helixPitch_[10];                      //[Nbr_tks]
    float         energyOfTrack_[10];                   //[Nbr_tks]
    float         Dec_[10];                             //[Nbr_tks]
    float         chargeOfTrack_[10];                   //[Nbr_tks]
    float         fitProbabilityOnHorizontalPlane_[10]; //[Nbr_tks]
    float         fitProbabilityOnRThetaPlane_[10];     //[Nbr_tks]
    float         fitProbabilityForHelix_[10];          //[Nbr_tks]
    float         xIntersectionOnFoil_[10];             //[Nbr_tks]
    float         yIntersectionOnFoil_[10];             //[Nbr_tks]
    float         zIntersectionOnFoil_[10];             //[Nbr_tks]
    float         directionCosine_[10][3];              //[Nbr_tks]
    float         xOfScintillator_[10];                 //[Mynbr_tks]
    float         yOfScintillator_[10];                 //[Mynbr_tks]
    float         zOfScintillator_[10];                 //[Mynbr_tks]
    char          scintillatorBlockId_[10];             //[Mynbr_tks] = IND_SCINT
    char          impactRegion_[10];                    //[Mynbr_tks] = IMPACT

    int           eventNumber_;
    float         xOfVertex_;                           // = X_VERT
    float         yOfVertex_;
    float         zOfVertex_;
    /**--
     *--   NBR_TKS         : NUMBER OF RECONSTRUCTED TRACKS
     *--   NBR_PTS(IT)     : NUMBER OF ASSOCIATED HITS ON TRACK IT
     *--   IND_POINTS(NP,IT) IGG VALUE FOR HIT NP ON TRACK IT
     *--   XC(IT)          : X COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
     *--   YC(IT)          : Y COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
     *--   ZC(IT)          : Z COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
     *--   RADC(IT)        : RADIUS OF CURVATURE OF TRACK IT
     *--   HC(IT)          : HELIX PITCH OF TRACK IT
     *--   EC(IT)          : ENERGY OF TRACK IT CALCULATED FROM THE CURVATURE
     *--   QC(IT)          : CHARGE OF TRACK IT CALCULATED FROM THE CURVATURE
     *--   PROB_RADC(IT)   : PROBABILITY OF CIRCLE FIT FOR TRACK IT
     *--                                               IN THE HORIZONTAL PLANE
     *--   PROB_HC(IT)     : PROBABILITY OF LINE FIT FOR TRACK IT
     *--                                               IN THE R*THETA PLANE
     *--   PROB_HELIX(IT)  : PROBABILITY OF THE HELIX FIT FOR TRACK IT
     *--   X_FOIL(IT)      : X COORDINATE OF THE INTERSECTION OF TRACK IT
     *--                                     WITH THE FOIL CYLINDER (FROM TRACKING)
     *--   Y_FOIL(IT)      : Y COORDINATE OF THE INTERSECTION OF TRACK IT
     *--                                     WITH THE FOIL CYLINDER (FROM TRACKING)
     *--   Z_FOIL(IT)      : Z COORDINATE OF THE INTERSECTION OF TRACK IT
     *--                                     WITH THE FOIL CYLINDER (FROM TRACKING)
     *--   COS_DIR(3,IT)   : DIRECTION COSINES OF TRACK IT
     *--                     (FROM TRACKING OR FROM TRACK FIT AND
     *--                                                 INTERSECTION WITH THE FOIL)
     *--   IND_SCINT(IT)   : ISC VALUE OF THE SCINTILLATOR ASSOCIATED TO TRACK IT
     *--   IMPACT(IT)      : IMPACT REGION OF THE TRACK ONTO THE SCINTILLATOR BLOCK
     *--   X_VERT          : X COORDINATE OF THE EVENT VERTEX
     *--   Y_VERT          : Y COORDINATE OF THE EVENT VERTEX
     *--   Z_VERT          : Z COORDINATE OF THE EVENT VERTEX
     **/
    
    // 09/01/2013: variables containing results fo local fits near the foil and 
    // scintillators wall

    float   xCenterOfCurvature_v_[10];       
    float   yCenterOfCurvature_v_[10];       
    float   zCenterOfCurvature_v_[10];       
    float   radiusOfCurvature_v_[10];     
    float   helixPitch_v_[10];         
    float   thetaMin_v_[10];           
    float   thetaMax_v_[10];           
    float   xIntersectionOnFoil_v_[10];   
    float   yIntersectionOnFoil_v_[10];   
    float   zIntersectionOnFoil_v_[10];   
    float   directionCosine_v_[10][3];   
    float   chargeOfTrack_v_[10];      

    float   xCenterOfCurvature_s_[10];   
    float   yCenterOfCurvature_s_[10];   
    float   zCenterOfCurvature_s_[10];   
    float   radiusOfCurvature_s_[10];     
    float   helixPitch_s_[10];        
    float   thetaMin_s_[10];          
    float   thetaMax_s_[10];          
    float   directionCosine_s_[10][3];   
    float   chargeOfTrack_s_[10];     
    float   xOfScintillator_s_[10];   
    float   yOfScintillator_s_[10];   
    float   zOfScintillator_s_[10];   

    int     runNumber_;  // event RUN number for data, for MC = -run 
                         // which conditions used for detector simulation
    int     date_;  // event date
    int     time_;  // duration of run in s RAW data, number MC generated for MC
    int     evntime_; // event timestamp in nemor format (hhmmss*1000)
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

    N3DbInterfaceModule* n3db_;
    int                  lastObsRun_;
    bool                 readTrueParticleInfo_;
};


#endif
