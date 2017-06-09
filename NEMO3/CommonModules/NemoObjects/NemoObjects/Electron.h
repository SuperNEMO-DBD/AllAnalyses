/*
 * Class        : Electron
 * Description  : Definition of the object containing calorimeter information
 *                with all calibration and corrections applied to it
 *
 *  Created by Stefano Torre on 09/05/2012.
 */

#ifndef NEMO_ELECTRON_H_
#define NEMO_ELECTRON_H_

#include "Hereward/Edm/EventRecord.h"
#include "Hereward/SuperNemoProcessing/Constants.h"
#include "TBuffer.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoObjects/N3CalorimeterHit.h"
#include "NemoObjects/TrackHelix.h"

class Electron {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    Electron();
    Electron(const Electron& obj);
    Electron& operator = (const Electron& obj);
    Electron(const N3CalorimeterHit& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~Electron();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    int    hitId() const;
    int    trackId() const;
    int    firstGeigerHit() const;
    void   setHitId(const int& aValue);
    void   setTrackId(const int& aValue);
    void   setFirstGeigerHit(const int& aValue);
    
    int    impactRegion() const;
    void   setImpactRegion(const int& aValue);
    bool   intersectTheFoil() const;
    void   setIntersectTheFoil(const bool& aValue);

    CLHEP::Hep3Vector vertex() const;
    void   setVertex(const CLHEP::Hep3Vector& aValue);
    
    CLHEP::Hep3Vector caloIP() const;
    void   setCaloIP(const CLHEP::Hep3Vector& aValue);

    void   setEnergy(const double& aValue);
    void   setDEnergy(const double& aValue);
    void   setPathLength(const double& aValue);
    void   setEnergyLoss(const double& aValue);

    double energy(bool useCorrected = false) const;
    double dEnergy() const;
    double pathLength() const;
    double energyLoss() const;
    
    double beta(bool useCorrected = false)    const ;
    double dBeta(bool useCorrected = false)   const ;
    double dBeta_dE(bool useCorrected = false) const;
    double gamma(bool useCorrected = false)   const ;

    void   setMeasTime(const double& aValue);
    void   setDMeasTime(const double& aValue);
    double measTime() const;
    double dMeasTime() const;
    double thTof(bool useCorrected = false) const ;
    double dThTof(bool useCorrected = false) const;

    // Extra time to PMT from scintillator face (added by JEM 04/12/13)
    void   setScintToPMTTime(const double& aValue);
    double scintToPMTTime() const ;

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
    void Streamer(TBuffer& iobuffer);    
    bool postread(EventRecord* p_record);
    void readFromBuffer(TBuffer& buf, Version_t version);
    void writeToBuffer(TBuffer& buf);
    
private:
    int    hitId_;
    int    trackId_;

    // hit nearest to the foil
    int    firstGeigerHit_;

    // Foil intersection information
    bool   intersectTheFoil_;
    
    // Calo intersection information
    int    impactRegion_;
    CLHEP::Hep3Vector caloIP_;

    //  Vertex of origin of the electron
    CLHEP::Hep3Vector vertex_;

    double measTime_;
    double dMeasTime_;
    double scintToPMTTime_;    // JEM 04/12/13
    double energy_;
    double dEnergy_;
    double pathLength_;
    double energyLoss_;

    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const Electron& obj);

#ifndef __CINT__
inline double Electron::gamma(bool useCorrected) const {
  return (physics::mElectron + energy(useCorrected))/physics::mElectron;
}

inline double Electron::beta(bool useCorrected) const {
  return sqrt(1 - pow(gamma(useCorrected), -2));
}

inline double Electron::dBeta_dE(bool useCorrected) const {
return (1 / beta(useCorrected)) * 
  pow(physics::mElectron, 2) /
  pow((energy(useCorrected) + physics::mElectron), 3);
}

inline double Electron::dBeta(bool useCorrected) const {
  return dBeta_dE(useCorrected) * dEnergy();
}

inline double Electron::thTof(bool useCorrected) const {
  return pathLength() / (beta(useCorrected) * physics::c / 10);
}

inline double Electron::dThTof(bool useCorrected) const {
  return thTof(useCorrected) / beta(useCorrected) * dBeta(useCorrected);
}

inline int    Electron::hitId() const { return hitId_; }
inline int    Electron::trackId() const { return trackId_; }
inline int    Electron::firstGeigerHit() const { 
  return firstGeigerHit_; 
}

inline void   Electron::setHitId(const int& aValue) { 
  hitId_ = aValue; 
}

inline void   Electron::setTrackId(const int& aValue) { 
  trackId_ = aValue; 
}
inline void   Electron::setFirstGeigerHit(const int& aValue) { 
  firstGeigerHit_ = aValue; 
}

inline int    Electron::impactRegion() const { 
  return impactRegion_; 
}
inline void   Electron::setImpactRegion(const int& aValue) { 
  impactRegion_ = aValue; 
}
inline bool   Electron::intersectTheFoil() const { 
  return intersectTheFoil_; 
}
inline void   Electron::setIntersectTheFoil(const bool& aValue) { 
  intersectTheFoil_ = aValue;
}

inline CLHEP::Hep3Vector Electron::vertex() const {
  return vertex_; 
}

inline void   Electron::setVertex(const CLHEP::Hep3Vector& aValue) { 
  vertex_ = aValue; 
}

inline CLHEP::Hep3Vector Electron::caloIP() const {
  return caloIP_; 
}

inline void   Electron::setCaloIP(const CLHEP::Hep3Vector& aValue) { 
  caloIP_ = aValue; 
}


inline void   Electron::setEnergy(const double& aValue) { 
  energy_ = aValue; 
}

inline void   Electron::setEnergyLoss(const double& aValue) { 
  energyLoss_ = aValue; 
}

inline void   Electron::setDEnergy(const double& aValue) { 
  dEnergy_ = aValue; 
}

inline void   Electron::setPathLength(const double& aValue) { 
  pathLength_ = aValue; 
}

inline double Electron::energy(bool useCorrected) const { 
  return (useCorrected)? energy_ + energyLoss_ :  energy_; 
}

inline double Electron::energyLoss() const { 
  return energyLoss_; 
}

inline double Electron::dEnergy() const { 
  return dEnergy_; 
}

inline double Electron::pathLength() const { 
  return pathLength_; 
}

inline void   Electron::setMeasTime(const double& aValue) { 
  measTime_ = aValue; 
}

inline void   Electron::setDMeasTime(const double& aValue) { 
  dMeasTime_ = aValue; 
}

inline double Electron::measTime() const { 
  return measTime_; 
}

inline double Electron::dMeasTime() const  { 
  return dMeasTime_; 
}

inline void   Electron::setScintToPMTTime(const double& aValue) { 
  scintToPMTTime_ = aValue; 
}

inline double Electron::scintToPMTTime() const { 
  return scintToPMTTime_; 
}

#endif

#endif
