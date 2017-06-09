//
//  N3TrueVertex.h
//
//  Created by Stefano Torre on 19/09/11.
//
#ifndef N3TRUEVERTEX_H_
#define N3TRUEVERTEX_H_

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

class N3TrueVertex {
public:
    
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    N3TrueVertex();
    N3TrueVertex(const N3TrueVertex& obj);
    N3TrueVertex& operator = (const N3TrueVertex& obj);

    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~N3TrueVertex();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    CLHEP::Hep3Vector       position()                  const;
    double                  time()                      const;
    bool                    isVirtual()                 const;
    
    void setPosition(const CLHEP::Hep3Vector aValue);
    void setPosition(const double px, const double py, const double pz);
    void setTime(const double aValue);
    void setIsVirtual(const bool aValue);
    
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
    CLHEP::Hep3Vector       position_;
    double                  time_;
    bool                    isVirtual_;
    static const Version_t  version_ = 1;
    Version_t               versionRead_; 
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const N3TrueVertex& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------


inline CLHEP::Hep3Vector N3TrueVertex::position() const {
    return position_;
}

inline double N3TrueVertex::time() const {
    return time_;
}

inline bool N3TrueVertex::isVirtual() const {
    return isVirtual_;
}


inline void N3TrueVertex::setPosition(const CLHEP::Hep3Vector aValue) {
    position_ = aValue;
}

inline void N3TrueVertex::setPosition(const double px, const double py, const double pz) {
    position_ = CLHEP::Hep3Vector(px, py, pz);
}

inline void N3TrueVertex::setTime(const double aValue) {
    time_ = aValue;
}

inline void N3TrueVertex::setIsVirtual(const bool aValue) {
    isVirtual_ = aValue;
}

#endif

#endif
