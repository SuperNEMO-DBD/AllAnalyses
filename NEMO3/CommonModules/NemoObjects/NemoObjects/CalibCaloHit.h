/*
 * Class        : CalibCaloHit
 * Description  : Definition of the object containing calorimeter information
 *                with all calibration and corrections applied to it
 *
 *  Created by Stefano Torre on 25/04/2012.
 */

#ifndef NEMO_CALIBCALOHIT_H_
#define NEMO_CALIBCALOHIT_H_

#include "Hereward/Edm/EventRecord.h"
#include "TBuffer.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoObjects/N3CalorimeterHit.h"

class CalibCaloHit {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    CalibCaloHit();
    CalibCaloHit(const CalibCaloHit& obj);
    CalibCaloHit& operator = (const CalibCaloHit& obj);
    CalibCaloHit(const N3CalorimeterHit& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~CalibCaloHit();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    int    status() const;
    int    pmtNumber() const;
    int    hitId() const;
    bool   overThresholdFlag() const;
    int    sectorNumber() const;
    int    iobt() const;
    int    fcll() const;
    int    blockNumber() const;    
    CLHEP::Hep3Vector blockCenter() const;
    double energyDeposit() const;
    double fwhm() const; 
    bool   goodFlag() const;
    int    leFlag() const;
    int    ldFlag() const;
    double ldCorr() const;
    double ldCorrErr() const;
    int    hsFlag() const;
    double hitTime() const;
    double gammaScintillationTime() const;
    double electronScintillationTime() const;
    double gammaTimeError() const;
    double electronTimeError() const;
    double alpha() const;
    double alphaEr() const;

    void setStatus(const int aValue);
    void setPmtNumber(const int aValue);
    void setHitId(const int aValue);
    void setOverThresholdFlag(const double aValue);
    void setSectorNumber(const int aValue);
    void setIobt(const int aValue);
    void setFcll(const int aValue);
    void setBlockNumber(const int aValue);
    void setBlockCenter(const CLHEP::Hep3Vector aValue);
    void setBlockCenter(const double x, const double y, const double z);
    void setEnergyDeposit(const double aValue);
    void setFwhm(const double aValue);
    void setGoodFlag(const bool aValue);
    void setLeFlag(const int aValue);
    void setLdFlag(const int aValue);
    void setLdCorr(const double aValue);
    void setLdCorrErr(const double aValue);
    void setHsFlag(const int aValue);
    void setHitTime(const double aValue);
    void setGammaScintillationTime(const double aValue);
    void setElectronScintillationTime(const double aValue);
    void setGammaTimeError(const double aValue);
    void setElectronTimeError(const double aValue);
    void setAlpha(const double aValue);
    void setAlphaError(const double aValue);

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
    int    status_;
    int    pmtNumber_;
    int    hitId_;
    bool   overThresholdFlag_;
    int    sectorNumber_;
    int    iobt_;
    int    fcll_;
    int    blockNumber_;
    bool   goodFlag_;
    int    leFlag_;
    int    ldFlag_;
    double ldCorr_;
    double ldCorrErr_;
    int    hsFlag_;
    CLHEP::Hep3Vector blockCenter_;
    double energyDeposit_;
    double fwhm_;
    double hitTime_;
    double gammaScintillationTime_;
    double electronScintillationTime_;
    double gammaTimeError_;
    double electronTimeError_;
    double alpha_;
    double alphaEr_;

    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const CalibCaloHit& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------
inline int CalibCaloHit::status() const {
    return status_;
}

inline int CalibCaloHit::pmtNumber() const {
    return pmtNumber_;
}

inline int CalibCaloHit::hitId() const {
    return hitId_;
}

inline bool CalibCaloHit::overThresholdFlag() const {
    return overThresholdFlag_;
}

inline int CalibCaloHit::sectorNumber() const {
    return sectorNumber_;
}

inline int CalibCaloHit::iobt() const {
    return iobt_;
}

inline int CalibCaloHit::fcll() const {
    return fcll_;
}

inline int CalibCaloHit::blockNumber() const {
    return blockNumber_;
}

inline CLHEP::Hep3Vector CalibCaloHit::blockCenter() const {
    return blockCenter_;
}

inline double CalibCaloHit::energyDeposit() const {
    return energyDeposit_;
}

inline double CalibCaloHit::fwhm() const {
  return fwhm_;
}

inline bool CalibCaloHit::goodFlag() const {
  return goodFlag_;
}

inline int CalibCaloHit::leFlag() const {
  return leFlag_;
}

inline int CalibCaloHit::ldFlag() const {
  return ldFlag_;
}

inline double CalibCaloHit::ldCorr() const {
  return ldCorr_;
}

inline double CalibCaloHit::ldCorrErr() const {
  return ldCorrErr_;
}

inline int CalibCaloHit::hsFlag() const {
  return hsFlag_;
}

inline double CalibCaloHit::hitTime() const {
  return hitTime_;
}

inline double CalibCaloHit::gammaScintillationTime() const {
  return gammaScintillationTime_;
}

inline double CalibCaloHit::electronScintillationTime() const {
  return electronScintillationTime_;
}

inline double CalibCaloHit::gammaTimeError() const {
  return gammaTimeError_;
}

inline double CalibCaloHit::electronTimeError() const {
  return electronTimeError_;
}

inline double CalibCaloHit::alpha() const {
  return alpha_;
}

inline double CalibCaloHit::alphaEr() const {
  return alphaEr_;
}

inline void CalibCaloHit::setStatus(const int aValue) {
    status_ = aValue;
}

inline void CalibCaloHit::setPmtNumber(const int aValue) {
    pmtNumber_ = aValue;
}

inline void CalibCaloHit::setHitId(const int aValue) {
    hitId_ = aValue;
}

inline void CalibCaloHit::setOverThresholdFlag(const double aValue) {
    overThresholdFlag_ = aValue;
}

inline void CalibCaloHit::setSectorNumber(const int aValue) {
    sectorNumber_ = aValue;
}

inline void CalibCaloHit::setIobt(const int aValue) {
    iobt_ = aValue;
}

inline void CalibCaloHit::setFcll(const int aValue) {
    fcll_ = aValue;
}

inline void CalibCaloHit::setBlockNumber(const int aValue) {
    blockNumber_ = aValue;
}

inline void CalibCaloHit::setBlockCenter(const CLHEP::Hep3Vector aValue) {
    blockCenter_ = aValue;
}

inline void CalibCaloHit::
setBlockCenter(const double x, const double y, const double z) {
    setBlockCenter(CLHEP::Hep3Vector(x,y,z));
}

inline void CalibCaloHit::setEnergyDeposit(const double aValue) {
    energyDeposit_ = aValue;
}

inline void CalibCaloHit::setFwhm(const double aValue) {
    fwhm_ = aValue;
}

inline void CalibCaloHit::setGoodFlag(const bool aValue) {
  goodFlag_ = aValue;
}

inline void CalibCaloHit::setLeFlag(const int aValue) {
  leFlag_ = aValue;
}

inline void CalibCaloHit::setLdFlag(const int aValue) {
  ldFlag_ = aValue;
}

inline void CalibCaloHit::setLdCorr(const double aValue) {
  ldCorr_ = aValue;
}

inline void CalibCaloHit::setLdCorrErr(const double aValue) {
  ldCorrErr_ = aValue;
}

inline void CalibCaloHit::setHsFlag(const int aValue) {
  hsFlag_ = aValue;
}

inline void CalibCaloHit::setHitTime(const double aValue) {
  hitTime_ = aValue;
}

inline void CalibCaloHit::setGammaScintillationTime(const double aValue) {
  gammaScintillationTime_ = aValue;
}

inline void CalibCaloHit::setElectronScintillationTime(const double aValue) {
  electronScintillationTime_ = aValue;
}

inline void CalibCaloHit::setGammaTimeError(const double aValue) {
  gammaTimeError_ = aValue;
}

inline void CalibCaloHit::setElectronTimeError(const double aValue) {
  electronTimeError_ = aValue;
}

inline void CalibCaloHit::setAlpha(const double aValue) {
  alpha_ = aValue;
}

inline void CalibCaloHit::setAlphaError(const double aValue) {
  alphaEr_ = aValue;
}

#endif

#endif
