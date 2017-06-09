//
//  GammaTrack.h
//
//  Created by Summer Blot  26/06/13.
//
#ifndef NEMO_GAMMATRACK_H_
#define NEMO_GAMMATRACK_H_

#include "Hereward/Edm/EventRecord.h"
#include "Hereward/SuperNemoProcessing/Constants.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/Gamma.h"
#include "NemoObjects/GammaCluster.h"
#include "TBuffer.h"

class GammaTrack {
    
public:
    
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    GammaTrack();
    GammaTrack(const GammaTrack& obj);
    // GammaTrack(const std::vector<&> obj);
    GammaTrack& operator = (const GammaTrack& obj);

    //GammaTrack(const GammaTrack& rhs);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~GammaTrack();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    std::vector<Gamma> trackedGammas() const; 
    void   setTrackedGammas(const std::vector<Gamma>& aValue);

    std::vector<GammaCluster> clusters() const; 
    void   setClusters(const std::vector<GammaCluster>& aValue);
 
    void   setFirstHitPos(const Gamma& aValue);
    Gamma  firstHitPos() const;

    void   setEnergy(const double& aValue);
    double energy() const;

    void   setDEnergy(const double& aValue);
    double dEnergy() const;

    void   setGTLength(const double& aValue);
    double gtLength() const;

   //  double pathLength() const;
    // double dPathLength() const;

    void     setProb(const double& aValue);
    double   prob() const;

    void     setChisq(const double& aValue);
    double   chisq() const;

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
    std::vector<Gamma> trackedGammas_; // list of gammas connected by tracks. NOT complete cluster. 
    std::vector<GammaCluster> clusters_; // list of gammas connected by tracks. NOT complete cluster. 
    ClassDef(GammaTrack, 1)
    double energy_;
    double dEnergy_;
    double prob_;
    double chisq_;
    double gtLength_;
    double timeSpan_;
    double timeAvg_;
    double wTimeAvg_;

    Gamma firstHitPos_;

    static const Version_t version_ = 1;
    Version_t versionRead_;
};

std::ostream& operator << (std::ostream& os, const GammaTrack& obj);

#ifndef __CINT__

inline void   GammaTrack::setEnergy(const double& aValue) { 
  energy_ = aValue; 
}

inline void   GammaTrack::setDEnergy(const double& aValue) { 
  dEnergy_ = aValue; 
}

inline double GammaTrack::energy() const { 
  return energy_; 
}

inline double GammaTrack::dEnergy() const { 
  return dEnergy_;
}

inline void GammaTrack::setClusters(const std::vector<GammaCluster>& aValue ) {
  clusters_ = aValue;
}

inline std::vector<GammaCluster> GammaTrack::clusters() const {
  return clusters_;
}

inline void GammaTrack::setTrackedGammas(const std::vector<Gamma>& aValue ) {
  trackedGammas_ = aValue;
}

inline std::vector<Gamma> GammaTrack::trackedGammas() const {
  return trackedGammas_;
}

inline void GammaTrack::setFirstHitPos(const Gamma& aValue) {
  firstHitPos_ = aValue;
}

inline Gamma GammaTrack::firstHitPos() const {
  return firstHitPos_;
}

inline void GammaTrack::setProb(const double& aValue ) {
  prob_ = aValue;
}

inline double GammaTrack::prob() const {
  return prob_;
}

inline void GammaTrack::setChisq(const double& aValue ) {
  chisq_ = aValue;
}

inline double GammaTrack::chisq() const {
  return chisq_;
}

inline void GammaTrack::setGTLength(const double& aValue ) {
  gtLength_ = aValue;
}

inline double GammaTrack::gtLength() const {
  return gtLength_;
}

#endif

#endif
