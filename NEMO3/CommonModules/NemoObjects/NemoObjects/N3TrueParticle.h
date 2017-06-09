//
//  N3TrueParticle.h
//
//  Created by Stefano Torre on 19/09/11.
//
#ifndef N3TRUEPARTICLE_H_
#define N3TRUEPARTICLE_H_

/** KINEMATICS SECTION
 N3True MC information about particles generated. Stored only if reconstructed with special flag for nemor. Majority of reco files do not have it due to filesize issue.
 
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

#include "Edm/EventRecord.h"
#include "CLHEP/Vector/ThreeVector.h"

class N3TrueParticle {
public:
    
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    N3TrueParticle();
    N3TrueParticle(const N3TrueParticle& obj);
    N3TrueParticle& operator = (const N3TrueParticle& obj);

    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~N3TrueParticle();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    CLHEP::Hep3Vector       momentum()                  const;
    double                  generationTime()            const;
    int                     indexOfAttachedVertex()     const;
    int                     geantParticleId()           const;
    CLHEP::Hep3Vector       entryPointInCalorimeter()   const;
    unsigned int            addressOfFirstHit()         const;
    unsigned int            numberOfGeigerHits()          const;
    
    void setMomentum(const CLHEP::Hep3Vector aValue);
    void setMomentum(const double px, const double py, const double pz);
    void setGenerationTime(const double aValue);
    void setIndexOfAttachedVertex(const int aValue);
    void setGeantParticleId(const int aValue);
    void setEntryPointInCalorimeter(const CLHEP::Hep3Vector aValue);
    void setEntryPointInCalorimeter(const double x, const double y, const double z);
    void setAddressOfFirstHit(const unsigned int aValue);
    void setNumberOfGeigerHits(const unsigned int aValue);
    
    //-------------------------------------------------------------------------
    // Print methods
    //--------------------------------------------------    -----------------------
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
    CLHEP::Hep3Vector       momentum_;
    double                  generationTime_;
    int                     indexOfAttachedVertex_;
    int                     geantParticleId_;
    CLHEP::Hep3Vector       entryPointInCalorimeter_;
    unsigned int            addressOfFirstHit_;
    unsigned int            numberOfGeigerHits_;
    static const Version_t  version_ = 1;
    Version_t               versionRead_; 
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const N3TrueParticle& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------


inline CLHEP::Hep3Vector N3TrueParticle::momentum() const {
    return momentum_;
}

inline double N3TrueParticle::generationTime() const {
    return generationTime_;
}

inline int N3TrueParticle::indexOfAttachedVertex() const {
    return indexOfAttachedVertex_;
}

inline int N3TrueParticle::geantParticleId() const {
    return geantParticleId_;
}

inline CLHEP::Hep3Vector N3TrueParticle::entryPointInCalorimeter() const {
    return entryPointInCalorimeter_;
}

inline unsigned int N3TrueParticle::addressOfFirstHit()         const {
    return addressOfFirstHit_;
}

inline unsigned int N3TrueParticle::numberOfGeigerHits()  const {
    return numberOfGeigerHits_;
}

inline void N3TrueParticle::setMomentum(const CLHEP::Hep3Vector aValue) {
    momentum_ = aValue;
}

inline void N3TrueParticle::setMomentum(const double px, const double py, const double pz) {
    momentum_ = CLHEP::Hep3Vector(px, py, pz);
}

inline void N3TrueParticle::setGenerationTime(const double aValue) {
    generationTime_ = aValue;
}

inline void N3TrueParticle::setIndexOfAttachedVertex(const int aValue) {
    indexOfAttachedVertex_ = aValue;
}

inline void N3TrueParticle::setGeantParticleId(const int aValue) {
    geantParticleId_ = aValue;
}

inline void N3TrueParticle::setEntryPointInCalorimeter(const CLHEP::Hep3Vector aValue) {
    entryPointInCalorimeter_ = aValue;
}

inline void N3TrueParticle::
setEntryPointInCalorimeter(const double x, const double y, const double z) {
    entryPointInCalorimeter_ = CLHEP::Hep3Vector(x,y,z);
}

inline void N3TrueParticle::setAddressOfFirstHit(const unsigned int aValue) {
    addressOfFirstHit_ = aValue;
}

inline void N3TrueParticle::setNumberOfGeigerHits(const unsigned int aValue) {
    numberOfGeigerHits_ = aValue;
}

#endif

#endif
