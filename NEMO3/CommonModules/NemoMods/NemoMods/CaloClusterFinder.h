//
//  CaloClusterFinder.h
//
//  Created by S. Blot
//
//  Please look through this header file and also NemoObjects/GammaCluster.h
//  to find comments about which methods are useful and which are DANGEROUS/obsolete.
//  
//  DocDB is emminent. -SDB 24/2/14

#ifndef NEMO_CALOCLUSTERFINDER_H_
#define NEMO_CALOCLUSTERFINDER_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/NemoDataBaseManager.h"
#include "NemoMods/N3DbInterfaceModule.h"
#include "NemoObjects/NemoObjects/Gamma.h"
#include "NemoObjects/NemoObjects/GammaCluster.h"

#include "NemoObjects/GammaClusterColl.h"
#include "NemoObjects/CalibCaloHitColl.h"

#include "NemoObjects/GammaColl.h"
#include "NemoObjects/N3TrackColl.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/N3CalorimeterHitColl.h"

#include <map>
#include <vector>
//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class CaloClusterFinder : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructor and Destructor
    //-------------------------------------------------------------------------
    CaloClusterFinder(const std::string theName = "CaloClusterFinder",
	       const std::string theDecription = 
	       "Looks for gamma in the event");
    virtual ~CaloClusterFinder();

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
    
    // It is not recommended to cut on this probability due to data/MC disagreement - S.D.B. 24/2/14
    void setCutOnClusterProbability(const bool aValue){ cutOnClusterProbability_ = aValue;}
    void setMinAllowedClusterProb(const double aValue)    { minAllowedClusterProb_    = aValue; }
 
    // default weighting uses measured time error. Use this method to change to weighting by Energy
    void setWeightAvgByEnergy(const bool aValue)    { avgWeightedByEnergy_    = aValue; }

    // It is not recommended to lower this threshold to data/MC disagreement - S.D.B. 24/2/14
    void setMaxTimeDiff_(const double aValue)    { maxTimeDiff_    = aValue; }

    // for debugging purposes, prints out a lot of messages
    void setDebug(const int aValue)    { debug    = aValue; }    

    // Allows hits outside of the TDC range 1750-3250 to be considered for clustering. - S.D.B. 24/2/14
    void setAllowNoiseInCluster(const bool aValue) { allowNoiseInCluster_ = aValue; }
   
    //Set the LD flag conditions allowed in cluster. Default is LD == 0 
    void setMaxLDFlag(const int aValue) { maxLDFlag_ = aValue; }

    //Set the HS flag conditions allowed in cluster. Default is HS == 0 
    // void setMaxHSFlag(const int aValue) { maxHSFlag_ = aValue; }

    //Set the HS flag conditions allowed in cluster. Default is HS == 0 
    //    void setAllowedHSFlags(const int aValue) { allowedHSFlags_.push_back(aValue); }
   
private:

    GammaColl_ch gColl;
    N3TrackColl_ch theTrackColl;
    N3CalorimeterHitColl_ch n3Calohits;
    CalibCaloHitColl_ch caloHits;
    N3CalorimeterHitColl::N3CalorimeterHitList rawCaloHitList;

    int debug;   

    std::vector<Gamma> gammaHolder;
    std::vector<Gamma> tmpHolder;
    std::vector<GammaCluster> clusters;  
    std::vector<int> blocksWithTrack;
    bool by_time(const Gamma &hit1, const Gamma &hit2); // sorts hits by time.
    // bool by_energy(const Gamma& hit2, const Gamma& hit2); // sorts hits by energy

    // bool checkPMTQuality(int calibHitID);

    bool     checkSamePetalLayer(int i, int j); 
    //     checks if L1-L4 blocks are in the same layer before clustering

    int      checkForNeighbouringClusters(GammaCluster &theCluster );
    //    only used if employing time span or cluster prob cuts 

    void     findMeanPosition(GammaCluster &theCluster); 
    //    weighted by measured time error (default) or energy (set flag)
    void     findMeanTime(GammaCluster &theCluster ); 
    //    same as mean position

    bool     calculateClusterProb(std::vector<Gamma> gammaVec, double &prob);
    //    calculated as: (t1-t2 + d21) / sqrt( (dt1*dt1) + (dt2*dt2) ) 
    //    where t1,t2 are the measured times of neighbouring hits and d21 is the 
    //    distance between these blocks.
    //
    //     It is currently not recommended to cut on this value due to data/MC 
    //     disagreement. (SDB 24/2/14)
    //
 
    bool     checkIfClustered(int aRawHitID); 
    //    checks if the current hit candidate has been added to another cluster already
    
    bool tooManyInCluster; // no more than 20 hits are allowed in a single cluster because that would just be cray
 
    bool cutOnClusterProbability_; // default = false.

    bool avgWeightedByEnergy_; // default = false

    bool clustered;

    int nInCluster; // number of hits in a cluster

    double maxTimeDiff_;// maximum time allowed between neighbouring hits for clustering. default = 100 ns because otherwise 
                        // you end up treating data and MC differently. 
    double minAllowedClusterProb_; // default = 0.001 but this cut should never actually beused due to data/MC disagreement.

    bool allowNoiseInCluster_; // Allows hits outside of the TDC range 1750-3250 to be considered for clustering.
                               // Note that this should ONLY be used for assessing systematic errors

    //   bool allowBadPMTStatusInCluster_; // Allows PMTs with bad status to be clustered. You probably never want to do this, but at least you have the option now.
    // bool allowMissingLDCorrInCluster_; // Allows PMTs with missing LD corrections to be clustered. Not recommended for mainstream analyses
    // bool allowMissingLDCorrErrInCluster_; // Allows PMTs with missing LD correction errors to be clustered. Again, not recommended.

    int maxLDFlag_; // maximum LD flags allowed in clusters. 
    // int maxHSFlag_; // remove
    // std::vector<int> allowedHSFlags_; // HS flags that are allowed in clusters. HS = 0, 10 are default allowed values.
};

#endif
