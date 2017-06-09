//
//  AlphaFinder.h
//
//  Created by Stefano Torre on 22/05/12.
//  Heavily modified by James Mott on 15/01/13.  New clustering algorithm
//  implemented based on Vera Kovalenko's alpha search.
//

#ifndef NEMO_ALPHAFINDER_H_
#define NEMO_ALPHAFINDER_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoMods/NemoDataBaseManager.h"
#include "NemoMods/N3DbInterfaceModule.h"
#include "NemoObjects/N3TrackColl.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/AlphaColl.h"
#include <map>
#include <vector>

class AlphaFinder : public AppModule {
public:

    //-------------------------------------------------------------------------
    // Structs etc
    //-------------------------------------------------------------------------
    struct DelayedTime {
      DelayedTime(int a, double b, double c) { id = a; time = b; z = c; }
      int    id;
      double time;
      double z;
    };

    //-------------------------------------------------------------------------
    // Constructor and Destructor
    //-------------------------------------------------------------------------
    AlphaFinder(const std::string theName = "AlphaFinder",
	       const std::string theDecription = 
	       "Looks for alphas in the event");
    virtual ~AlphaFinder();

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

    // Set Clustering Parameters
    void setMaxTimeBetweenHits(const double aValue)    { maxTimeBetweenHits_    = aValue; }
    void setMaxDistBetweenHits(const double aValue)    { maxDistBetweenHits_    = aValue; }
    void setMinTimeOfDelayedHit(const double aValue)   { minTimeOfDelayedHit_   = aValue; } 
    void setMaxTimeOfDelayedHit(const double aValue)   { maxTimeOfDelayedHit_   = aValue; } 

    // Set Alpha Identification Parameters
    void setMinTimeOf1DelayedHit(const double aValue)  { minTimeOf1DelayedHit_  = aValue; }
    void setMinTimeOf2DelayedHits(const double aValue) { minTimeOf2DelayedHits_ = aValue; }
    void setMinTimeOf3DelayedHits(const double aValue) { minTimeOf3DelayedHits_ = aValue; }
    void setMinTimeOf4DelayedHits(const double aValue) { minTimeOf4DelayedHits_ = aValue; }
    void setMinClusterDistSearch(const double aValue)  { minClusterDistSearch_  = aValue; }
    void setMinClusterDistXYSearch(const double aValue){ minClusterDistXYSearch_= aValue; }
    void setMinClusterDistZSearch(const double aValue) { minClusterDistZSearch_ = aValue; }
    void setMinClusterDistVeto(const double aValue)    { minClusterDistVeto_    = aValue; }
    void setMinClusterDistXYVeto(const double aValue)  { minClusterDistXYVeto_  = aValue; }
    void setMinClusterDistZVeto(const double aValue)   { minClusterDistZVeto_   = aValue; }

    // Set flag to use veto criteria
    void setUseVetoCriteria(const bool aValue)         { useVetoCriteria_       = aValue; }

private:
    AppResult makeClusters(AppEvent *anEvent);
    bool goodAlphaCandidate(Alpha& alpha);
    void fitAlphaTrack(std::vector<double> x, std::vector<double>y,
		       double x_err, double y_err, double &A, double &B);
    CLHEP::Hep3Vector findAlphaFoilVertex(double x, double y, double z, 
					  double A_xy, double B_xy,
					  double A_xz, double B_xz);
    N3TrackColl_ch     theTrackColl_;
    N3GeigerHitColl_ch theGgColl_;
    std::vector<int> delayedHitIds_;
    std::vector<DelayedTime> delayedHitTimes_;
    //    std::vector<std::pair<int,double> > delayedHitTimes_;
    std::vector<std::vector<int> > delayedClusters_;
    
    // Clustering parameters
    double maxTimeBetweenHits_;
    double maxDistBetweenHits_;
    double minTimeOfDelayedHit_;
    double maxTimeOfDelayedHit_;

    // Alpha identification parameters - times to avoid refiring
    double minTimeOf1DelayedHit_;
    double minTimeOf2DelayedHits_;
    double minTimeOf3DelayedHits_;
    double minTimeOf4DelayedHits_;

    // Flag to decide whether to user is looking for alphas or trying to veto them.
    // The latter generally has wider search parameters.
    bool useVetoCriteria_;

    // Alpha identification parameters - Search for Alphas Criteria
    double minClusterDistSearch_;
    double minClusterDistXYSearch_;
    double minClusterDistZSearch_;

    // Alpha identification parameters - Veto Alphas Criteria
    double minClusterDistVeto_;
    double minClusterDistXYVeto_;
    double minClusterDistZVeto_;
    
};

#endif
