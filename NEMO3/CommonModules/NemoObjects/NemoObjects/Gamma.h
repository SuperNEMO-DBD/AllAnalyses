/*
 * Class        : Gamma
 * Description  : Definition of the object containing calorimeter information
 *                with all calibration and corrections applied to it
 *
 *  Created by Stefano Torre on 09/05/2012.
 */

#ifndef NEMO_GAMMA_H_
#define NEMO_GAMMA_H_

#include "Hereward/Edm/EventRecord.h"
#include "Hereward/SuperNemoProcessing/Constants.h"
#include "TBuffer.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoObjects/N3CalorimeterHit.h"

class Gamma {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    Gamma();
    Gamma(const Gamma& obj);
    Gamma& operator = (const Gamma& obj);
    Gamma(const N3CalorimeterHit& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~Gamma();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    int    rawHitId() const; // index of hit in the raw hit collection 
    void   setRawHitId(const int& aValue);

    int    calibHitId() const; // index of hit in the calibrated hit collection (calib.size() <= raw.size())
    void   setCalibHitId(const int& aValue);
    
    //Either center of block or face of PM, check GammaFinder flags
    CLHEP::Hep3Vector hitPosition() const;
    void   setHitPosition(const CLHEP::Hep3Vector& aValue);
    
    void   setEnergy(const double& aValue);
    void   setDEnergy(const double& aValue);

    double energy() const; //MeV, to get best data/MC agreement set approriate resolution flags in NemoMods/GammaFinder
    double dEnergy() const; //MeV

    void   setMeasTime(const double& aValue); // ns
    void   setDMeasTime(const double& aValue); //ns
    double measTime() const;
    double dMeasTime() const;

    // depending on flags in GammaFinder, this is either a value from ROOTANA or it is
    // the error on the gamma path from vertex to scintillator added in quadrature to a fitted parameter  
    void   setDPathLength(const double& aValue); 
    double dPathLength() const;

    //Temporary method for systematics study SDB 4/4/14
    void   setGeomError(const double& aValue); 
    double geomError() const;
 
    // addded 2/7/13 S.Blot 
    // See engineering drawings for details (DocDB 2738)
    void   setThickness(const double& aValue);
    double thickness() const;

    void   setWidth(const double& aValue);
    double blockWidth() const;

    void   setHeight(const double& aValue);
    double blockHeight() const;

    // IN = 0, EE = 1, EC = 2, L1-L4 = 3-6, respectively.
    void   setBlockType(const int& aValue);
    int blockType() const;

    // A fitted TOF parameter. Quantifies the time delay between gamma interaction in the scintillator, and the hit register
    // in the PMT. Physical interpretation is a combination of many factors such as geometry (angular dependences), scattering
    // inside the scintillator block, speed of light in scintillator < vacuum, scintillation time walk effects, ... (probably more)
    // See Bi207 1eNg channel calibration example module for how to use this.
    void   setScintToPMTTime(const double& aValue);
    double scintToPMTTime() const;

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
    int    rawHitId_;
    int    calibHitId_;

    //  nominal position of hte gamma on the scintillator
    CLHEP::Hep3Vector hitPosition_;
    double measTime_;
    double dMeasTime_;
    double energy_;
    double dEnergy_;
    double dPathLength_;
    double geomError_;
    double thickness_;
    double width_;
    double height_;
    double scintToPMTTime_;
    int    blockType_;
    
    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const Gamma& obj);

#ifndef __CINT__

inline int    Gamma::rawHitId() const { return rawHitId_; }

inline void   Gamma::setRawHitId(const int& aValue) { 
  rawHitId_ = aValue; 
}

inline int    Gamma::calibHitId() const { return calibHitId_; }

inline void   Gamma::setCalibHitId(const int& aValue) { 
  calibHitId_ = aValue; 
}

inline CLHEP::Hep3Vector Gamma::hitPosition() const {
  return hitPosition_; 
}

inline void   Gamma::setHitPosition(const CLHEP::Hep3Vector& aValue) { 
  hitPosition_ = aValue; 
}

inline void   Gamma::setEnergy(const double& aValue) { 
  energy_ = aValue; 
}

inline void   Gamma::setDEnergy(const double& aValue) { 
  dEnergy_ = aValue; 
}

inline double Gamma::energy() const { 
  return energy_; 
}

inline double Gamma::dEnergy() const { 
  return dEnergy_; 
}

inline void   Gamma::setMeasTime(const double& aValue) { 
  measTime_ = aValue; 
}

inline void   Gamma::setDMeasTime(const double& aValue) { 
  dMeasTime_ = aValue; 
}

inline double Gamma::measTime() const { 
  return measTime_; 
}

inline double Gamma::dMeasTime() const  { 
  return dMeasTime_; 
}

inline void   Gamma::setScintToPMTTime(const double& aValue) {
  scintToPMTTime_ = aValue;
}

inline double Gamma::scintToPMTTime() const {
  return scintToPMTTime_;
}

inline void   Gamma::setDPathLength(const double& aValue) {
  dPathLength_ = aValue;
}

inline double Gamma::dPathLength() const {
  return dPathLength_;
}

//*********//
//Temporary//
inline void   Gamma::setGeomError(const double& aValue) {
  geomError_ = aValue;
}

inline double Gamma::geomError() const {
  return geomError_;
}
//******//

inline void Gamma::setThickness(const double& aValue) {
  thickness_ = aValue;
}

inline double Gamma::thickness() const {
  return thickness_;
}

inline void Gamma::setWidth(const double& aValue) {
  width_ = aValue;
}

inline double Gamma::blockWidth() const {
  return width_;
}

inline void Gamma::setHeight(const double& aValue) {
  height_ = aValue;
}

inline double Gamma::blockHeight() const {
  return height_;
}

inline void Gamma::setBlockType(const int& aValue) {
  blockType_ = aValue;
}

inline int Gamma::blockType() const {
  return blockType_;
}

#endif

#endif
