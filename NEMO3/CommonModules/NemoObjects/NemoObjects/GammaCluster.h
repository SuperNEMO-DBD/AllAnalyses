//
//  GammaCluster.h
//
//  Created by Summer Blot on 16/04/13.
//
#ifndef NEMO_GAMMACLUSTER_H_
#define NEMO_GAMMACLUSTER_H_

#include "Hereward/Edm/EventRecord.h"
#include "Hereward/SuperNemoProcessing/Constants.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/Gamma.h"
#include "TBuffer.h"

class GammaCluster {
    
public:
    
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    GammaCluster();
    GammaCluster(const GammaCluster& obj);
    // GammaCluster(const std::vector<&> obj);
    GammaCluster& operator = (const GammaCluster& obj);

    //GammaCluster(const GammaCluster& rhs);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~GammaCluster();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    std::vector<Gamma> cluster() const; 
    void   setCluster(const std::vector<Gamma>& aValue);

    void   setEarliestHit(const Gamma& aValue);
    Gamma  earliestHit() const; // first hit in the cluster (most negative) RECOMMENDED that this is
                                // the hit used when calculating TOF hypothesese (as opposed to averaged values)

    void   setLatestHit(const Gamma& aValue); 
    Gamma  latestHit() const;// last hit in cluster

    //total energy of all hits in clsuter
    void   setEnergy(const double& aValue);
    double energy() const; // total energy of the cluster (sum of indiv. hits)

    //errors of indiv. hits added in quad.
    void   setDEnergy(const double& aValue);
    double dEnergy() const; // errors of each hit in cluster added in quadrature

    void     setTimeSpan(const double& aValue);
    double   timeSpan() const; // difference in time between the first and last hit in a cluster.  

    void     setClusterProb(const double& aValue); 
    double   clusterProb() const;// internal probability of all hits in a cluster. See Christophe Hugo's thesis for details.

    // Weighted avg time, weighted by either measured time error (default) or energy of each hit
    // NOT recommended for use in calculating internal/external probability.
    void     setMeasTime(const double& aValue);
    double   measTime() const;

    void     setDMeasTime(const double& aValue);
    double   dMeasTime() const;


    // Weighted avg position, weighted by either measured time error (default) or energy of each hit
    //**** NOT recommended for use in calculating internal/external probability.****   
    void     setHitPosition(const CLHEP::Hep3Vector& aValue);
    CLHEP::Hep3Vector  hitPosition() const;

    // Weighted avg ScintToPMT time, weighted by either measured time error (default) or energy of each hit
    //**** NOT recommended for use in calculating internal/external probability.****
    void   setScintToPMTTime(const double& aValue);
    double scintToPMTTime() const;

    // This value should represent the uncertainty on where the incident gamma entered the cluster.
    // For a single, isolated hit, this corresponds to the size of the block face. So for a cluster this should correspond to the 
    // spatial size of the cluster face. However due to messy cluster shapes, this is difficult to quantify.  So for now, it is just
    //  the weighted avg dPathLength, weighted by either measured time error (default) or energy of each hit/
    // ****NOT recommended for use in calculating internal/external probability.****
    void     setDPathLength(const double& aValue);
    double   dPathLength() const;

    // **IMPORTANT  not the same as for gammas!**//
    // IOBT = in, out, bottom and top
    // I(in) 0, O(out) = 1 (BOTH EE and EC), B(bottom) = 2, T(top) = 3
    void     setIOBT(const int& aValue);
    int      iobt() const;

    // goes from 0--> 3, for petal layers 1-->4
    // = -1 for IN, EE, and EC blocks
    void     setFCLL(const int& aValue);
    int      fcll() const;

    // give clusters ID numbers for bookeeping
    void     setClusterId(const int& aValue);
    int      clusterId() const;

    // If all indiv. PMTs in the cluster have good status, LD and HS flags, these are set to true.
    // If ONE hit in a cluster does not meet quality control requirements, then these flags are false.
    
    // Does each hit in cluster have calibHit.goodStatus()
    void     setGoodPMTStatuses(const bool& aValue);
    bool     goodPMTStatuses() const;

    // Does each hit in cluster have calibHit.ldFlag() < maxLDFlag (set by user, default == 0)
    void     setGoodLDFlags(const bool& aValue);
    bool     goodLDFlags() const;

    // Does each hit in cluster have calibHit.ldCorr() >0 (aka it exists)
    void     setHasLDCorrs(const bool& aValue);
    bool     hasLDCorrs() const;

    // Does each hit in cluster have calibHit.ldCorrErr() >0 (aka it exists)
    void     setHasLDCorrErrs(const bool& aValue);
    bool     hasLDCorrErrs() const;

    // Does each hit in cluster have calibHit.hsFlag() = 0 ( if N hits/cluster > 1 then HS = 10 also allowed)
    void     setGoodHSFlags(const bool& aValue);
    bool     goodHSFlags() const;

    // number of neighbouring calo clusters
    // can end up with neighbours if cutting on time span or energy of hits allowed into cluster.
    void     setNumNeighbours(const int& aValue);
    int      numNeighbours() const;

    //-------------------------------------------------------------------------
    // Print methods
    //-------------------------------------------------------------------------
    virtual void print(std::ostream &output = std::cout) const;

    //-------------------------------------------------------------------------
    // Classifiers
    //-------------------------------------------------------------------------
    std::string class_name() const;
    Version_t class_version() const {return version_; }

    //-------------------------------------------------------------------------
    // I/O Methods
    //-------------------------------------------------------------------------    
    //   void Streamer(TBuffer& iobuffer);    
    bool postread(EventRecord* p_record);
    void readFromBuffer(TBuffer& buf, Version_t version);
    void writeToBuffer(TBuffer& buf);

private:
    std::vector<Gamma> cluster_;
    ClassDef(GammaCluster, 1)
    double energy_;
    double dEnergy_;
    double timeSpan_;
    double measTime_;
    double dMeasTime_;
    double dPathLength_;
    double clusterProb_;
        
    Gamma earliestHit_;
    Gamma latestHit_;
    
    int   clusterId_;
    bool  goodPMTStatuses_;
    bool  goodLDFlags_;
    bool  hasLDCorrs_;
    bool  hasLDCorrErrs_;
    bool  goodHSFlags_;

    int   numNeighbours_;

    int   iobt_;
    int   fcll_;

    CLHEP::Hep3Vector hitPosition_;
    double scintToPMTTime_;

    static const Version_t version_ = 1;
    Version_t versionRead_;
};

std::ostream& operator << (std::ostream& os, const GammaCluster& obj);

#ifndef __CINT__

inline void   GammaCluster::setEnergy(const double& aValue) { 
  energy_ = aValue; 
}

inline double GammaCluster::energy() const { 
  return energy_; 
}

inline void   GammaCluster::setDEnergy(const double& aValue) { 
  dEnergy_ = aValue; 
}

inline double GammaCluster::dEnergy() const { 
  return dEnergy_;
}

inline void GammaCluster::setCluster(const std::vector<Gamma>& aValue ) {
  cluster_ = aValue;
}

inline std::vector<Gamma> GammaCluster::cluster() const {
  return cluster_;
}

inline void GammaCluster::setEarliestHit(const Gamma& aValue) {
  earliestHit_ = aValue;
}

inline Gamma GammaCluster::earliestHit() const {
  return earliestHit_;
}

inline void GammaCluster::setLatestHit(const Gamma& aValue) {
  latestHit_ = aValue;
}

inline Gamma GammaCluster::latestHit() const {
  return latestHit_;
}

inline double GammaCluster::timeSpan() const {
  return timeSpan_;
}

inline void GammaCluster::setTimeSpan(const double& aValue ) {
  timeSpan_ = aValue;
}

inline void GammaCluster::setMeasTime(const double& aValue ) {
  measTime_ = aValue;
}

inline double GammaCluster::measTime() const {
  return measTime_;
}

inline void GammaCluster::setDMeasTime(const double& aValue ) {
  dMeasTime_ = aValue;
}

inline double GammaCluster::dMeasTime() const {
  return dMeasTime_;
}

inline void GammaCluster::setHitPosition(const CLHEP::Hep3Vector& aValue ) {
  hitPosition_ = aValue;
}

inline CLHEP::Hep3Vector GammaCluster::hitPosition() const {
  return hitPosition_;
}

inline void GammaCluster::setScintToPMTTime(const double& aValue) {
  scintToPMTTime_ = aValue;
}

inline double GammaCluster::scintToPMTTime() const {
  return scintToPMTTime_;
}

inline void GammaCluster::setDPathLength(const double& aValue ) {
  dPathLength_ = aValue;
}

inline double GammaCluster::dPathLength() const {
  return dPathLength_;
}

inline void GammaCluster::setIOBT(const int& aValue ) {
  iobt_ = aValue;
}

inline int GammaCluster::iobt() const {
  return iobt_;
}

inline void GammaCluster::setFCLL(const int& aValue ) {
  fcll_ = aValue;
}

inline int GammaCluster::fcll() const {
  return fcll_;
}

inline void GammaCluster::setClusterId(const int& aValue ) {
  clusterId_ = aValue;
}

inline int GammaCluster::clusterId() const {
  return clusterId_;
}

inline void GammaCluster::setGoodPMTStatuses(const bool& aValue ) {
  goodPMTStatuses_ = aValue;
}

inline bool GammaCluster::goodPMTStatuses() const {
  return goodPMTStatuses_;
}

inline void GammaCluster::setGoodLDFlags(const bool& aValue ) {
  goodLDFlags_ = aValue;
}

inline bool GammaCluster::goodLDFlags() const {
  return goodLDFlags_;
}

inline void GammaCluster::setHasLDCorrs(const bool& aValue ) {
  hasLDCorrs_ = aValue;
}

inline bool GammaCluster::hasLDCorrs() const {
  return hasLDCorrs_;
}

inline void GammaCluster::setHasLDCorrErrs(const bool& aValue ) {
  hasLDCorrErrs_ = aValue;
}

inline bool GammaCluster::hasLDCorrErrs() const {
  return hasLDCorrErrs_;
}

inline void GammaCluster::setGoodHSFlags(const bool& aValue ) {
  goodHSFlags_ = aValue;
}

inline bool GammaCluster::goodHSFlags() const {
  return goodHSFlags_;
}

inline void GammaCluster::setNumNeighbours(const int& aValue ) {
  numNeighbours_ = aValue;
}

inline int GammaCluster::numNeighbours() const {
  return numNeighbours_;
}

inline void GammaCluster::setClusterProb(const double& aValue ) {
  clusterProb_ = aValue;
}

inline double GammaCluster::clusterProb() const {
  return clusterProb_;
}

#endif

#endif
