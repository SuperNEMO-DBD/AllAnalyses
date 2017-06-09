/*
 * Class        : GeigerHit
 * Description  : Definition of the object containing the data of the Geiger hit
 *                after the readout
 *
 *  Created by Stefano Torre on 02/07/11.
 *  Copyright 2011 Univesity College London. All rights reserved.
 */
#ifndef NEMO_N3GEIGERHIT_H_
#define NEMO_N3GEIGERHIT_H_

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

#include "Hereward/Edm/EventRecord.h"
#include "TBuffer.h"
#include "CLHEP/Vector/ThreeVector.h"

class N3GeigerHit {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    N3GeigerHit();
    N3GeigerHit(const N3GeigerHit& obj);
    N3GeigerHit& operator = (const N3GeigerHit& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~N3GeigerHit();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    int status() const;
    int sectorNumber() const;
    int side() const;    
    int layer() const;
    int cellNumber() const;    
    long fastTdcContent() const;
    long slowTdcContent() const;
    long bottomTdcContent() const;
    long topTdcContent() const;
    double z() const;
    double zError() const;
    double weightReciprocal() const;
    CLHEP::Hep3Vector anodePosition() const;
    
    void setStatus(const int aValue);
    void setSectorNumber(const int aValue);
    void setSide(const int aValue);
    void setLayer(const int aValue);
    void setCellNumber(const int aValue);
    void setFastTdcContent(const long aValue);
    void setSlowTdcContent(const long aValue);
    void setBottomTdcContent(const long aValue);
    void setTopTdcContent(const long aValue);
    void setZ(const double aValue);
    void setZError(const double aValue);
    void setAnodeInformation(const double aValue);
    void setWeightReciprocal(const double aValue);
    void setAnodePosition(const CLHEP::Hep3Vector aValue);
    void setAnodePosition(const double x, const double y);

    bool isDelayed() const;
    bool isPrompt()  const;
    bool isNoise()   const;
    double driftDistance() const;
    double alphaTime() const;
    double anodeInformation() const;
    
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
    int side_;
    int layer_;
    int cellNumber_;
    long fastTdcContent_;
    long slowTdcContent_;
    long bottomTdcContent_;
    long topTdcContent_;
    double z_;
    double zError_;
    double anodeInformation_;
    double weightReciprocal_;
    CLHEP::Hep3Vector anodePosition_;
    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const N3GeigerHit& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------
inline int N3GeigerHit::status() const {
    return status_;
}

inline int N3GeigerHit::sectorNumber() const {
    return sectorNumber_;
}

inline int N3GeigerHit::side() const {
    return side_;
}

inline int N3GeigerHit::layer() const {
    return layer_;
}

inline int N3GeigerHit::cellNumber() const {
    return cellNumber_;
}

inline long N3GeigerHit::fastTdcContent() const {
    return fastTdcContent_;
}

inline long N3GeigerHit::slowTdcContent() const {
    return slowTdcContent_;
}

inline long N3GeigerHit::bottomTdcContent() const {
    return bottomTdcContent_;
}

inline long N3GeigerHit::topTdcContent() const {
    return topTdcContent_;
}

inline double N3GeigerHit::z() const {
    return z_;
}

inline double N3GeigerHit::zError() const {
    return zError_;
}

inline double N3GeigerHit::weightReciprocal() const {
    return weightReciprocal_;
}

inline CLHEP::Hep3Vector N3GeigerHit::anodePosition() const {
    return anodePosition_;
}

inline void N3GeigerHit::setStatus(const int aValue) {
    status_ = aValue;
}

inline void N3GeigerHit::setSectorNumber(const int aValue) {
    sectorNumber_ = aValue;
}

inline void N3GeigerHit::setSide(const int aValue) {
    side_ = aValue;
}

inline void N3GeigerHit::setLayer(const int aValue) {
    layer_ = aValue;
}

inline void N3GeigerHit::setCellNumber(const int aValue) {
    cellNumber_ = aValue;
}

inline void N3GeigerHit::setFastTdcContent(const long aValue) {
    fastTdcContent_ = aValue;
}

inline void N3GeigerHit::setSlowTdcContent(const long aValue) {
    slowTdcContent_ = aValue;
}

inline void N3GeigerHit::setBottomTdcContent(const long aValue) {
    bottomTdcContent_ = aValue;
}

inline void N3GeigerHit::setTopTdcContent(const long aValue) {
    topTdcContent_ = aValue;
}

inline void N3GeigerHit::setZ(const double aValue) {
    z_ = aValue;
}

inline void N3GeigerHit::setZError(const double aValue) {
    zError_ = aValue;
}

inline void N3GeigerHit::setAnodeInformation(const double aValue) {
    anodeInformation_ = aValue;
}

inline void N3GeigerHit::setWeightReciprocal(const double aValue) {
    weightReciprocal_ = aValue;
}

inline void N3GeigerHit::setAnodePosition(const CLHEP::Hep3Vector aValue) {
    anodePosition_ = aValue;
}

inline void N3GeigerHit::
setAnodePosition(const double x, const double y) {
    setAnodePosition(CLHEP::Hep3Vector(x,y,0));
}

#endif

#endif
