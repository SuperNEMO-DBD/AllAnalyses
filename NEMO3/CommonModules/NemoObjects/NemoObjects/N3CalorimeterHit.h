/*
 * Class        : N3CalorimeterHit
 * Description  : Definition of the object containing the data of the 
 *                N3Calorimeter hit after the readout
 *
 *  Created by Stefano Torre on 02/07/11.
 *  Copyright 2011 Univesity College London. All rights reserved.
 */
#ifndef NEMO_N3CALORIMETERHIT_H_
#define NEMO_N3CALORIMETERHIT_H_

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

#include "Hereward/Edm/EventRecord.h"
#include "TBuffer.h"
#include "CLHEP/Vector/ThreeVector.h"

class N3CalorimeterHit {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    N3CalorimeterHit();
    N3CalorimeterHit(const N3CalorimeterHit& obj);
    N3CalorimeterHit& operator = (const N3CalorimeterHit& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~N3CalorimeterHit();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    bool operator == (const N3CalorimeterHit& obj) const;
    bool operator != (const N3CalorimeterHit& obj) const;

    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    int status() const;
    int sectorNumber() const;
    int iobtFlag() const;
    int fcll() const;
    int blockNumber() const;
    double adcCounter() const;
    double tdcCounter() const;
    bool overThresholdFlag() const;
    CLHEP::Hep3Vector blockCenter() const;
    double energyDeposit() const;
    int pmtNumber() const;
    bool isNoisy() const;

    void setStatus(const int aValue);
    void setSectorNumber(const int aValue);
    void setIobtFlag(const int aValue);
    void setFcll(const int aValue);
    void setBlockNumber(const int aValue);
    void setAdcCounter(const double aValue);
    void setTdcCounter(const double aValue);
    void setOverThresholdFlag(const double aValue);
    void setBlockCenter(const CLHEP::Hep3Vector aValue);
    void setBlockCenter(const double x, const double y, const double z);
    void setEnergyDeposit(const double aValue);
    
    //-------------------------------------------------------------------------
    // Accessors
    //-------------------------------------------------------------------------
    int blockSectorId() const;
    int blockLayerId() const;
    int checkNeighbour(const N3CalorimeterHit& other) const ;
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
    int status_;
    int sectorNumber_;
    int iobtFlag_;
    int fcll_;
    int blockNumber_;
    double adcCounter_;
    double tdcCounter_;
    bool overThresholdFlag_;
    CLHEP::Hep3Vector blockCenter_;
    double energyDeposit_;
    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const N3CalorimeterHit& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------
inline int N3CalorimeterHit::status() const {
    return status_;
}

inline int N3CalorimeterHit::sectorNumber() const {
    return sectorNumber_;
}

inline int N3CalorimeterHit::iobtFlag() const {
    return iobtFlag_;
}

inline int N3CalorimeterHit::fcll() const {
    return fcll_;
}

inline int N3CalorimeterHit::blockNumber() const {
    return blockNumber_;
}

inline double N3CalorimeterHit::adcCounter() const {
    return adcCounter_;
}

inline double N3CalorimeterHit::tdcCounter() const {
    return tdcCounter_;
}

inline bool N3CalorimeterHit::overThresholdFlag() const {
    return overThresholdFlag_;
}

inline CLHEP::Hep3Vector N3CalorimeterHit::blockCenter() const {
    return blockCenter_;
}

inline double N3CalorimeterHit::energyDeposit() const {
    return energyDeposit_;
}

inline void N3CalorimeterHit::setStatus(const int aValue) {
    status_ = aValue;
}

inline void N3CalorimeterHit::setSectorNumber(const int aValue) {
    sectorNumber_ = aValue;
}

inline void N3CalorimeterHit::setIobtFlag(const int aValue) {
    iobtFlag_ = aValue;
}

inline void N3CalorimeterHit::setFcll(const int aValue) {
    fcll_ = aValue;
}

inline void N3CalorimeterHit::setBlockNumber(const int aValue) {
    blockNumber_ = aValue;
}

inline void N3CalorimeterHit::setAdcCounter(const double aValue) {
    adcCounter_= aValue;
}

inline void N3CalorimeterHit::setTdcCounter(const double aValue) {
    tdcCounter_ = aValue;
}

inline void N3CalorimeterHit::setOverThresholdFlag(const double aValue) {
    overThresholdFlag_ = aValue;
}

inline void N3CalorimeterHit::setBlockCenter(const CLHEP::Hep3Vector aValue) {
    blockCenter_ = aValue;
}

inline void N3CalorimeterHit::
setBlockCenter(const double x, const double y, const double z) {
    setBlockCenter(CLHEP::Hep3Vector(x,y,z));
}

inline void N3CalorimeterHit::setEnergyDeposit(const double aValue) {
    energyDeposit_ = aValue;
}

inline bool N3CalorimeterHit::operator == (const N3CalorimeterHit& obj) const {
  return (sectorNumber() == obj.sectorNumber() and
	  iobtFlag()     == obj.iobtFlag() and
	  fcll()         == obj.fcll() and
	  blockNumber()  == obj.blockNumber());
}

inline bool N3CalorimeterHit::isNoisy() const {
  return ((status() % 10) >= 2);
}

inline bool N3CalorimeterHit::operator != (const N3CalorimeterHit& obj) const {
  return ! operator ==(obj);
}

#endif

#endif
