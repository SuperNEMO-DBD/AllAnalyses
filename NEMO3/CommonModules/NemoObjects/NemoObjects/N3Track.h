//
//  N3Track.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#ifndef NEMO_N3TRACK_H_
#define NEMO_N3TRACK_H_

/**--
 *--   NBR_TKS         : NUMBER OF RECONSTRUCTED TRACKS
 *--   NBR_PTS(IT)     : NUMBER OF ASSOCIATED HITS ON TRACK IT
 *--   IND_POINTS(NP,IT) IGG VALUE FOR HIT NP ON TRACK IT
 *--   XC(IT)          : X COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
 *--   YC(IT)          : Y COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
 *--   ZC(IT)          : Z COORDINATE OF THE CENTER OF CURVATURE OF TRACK IT
 *--   RADC(IT)        : RADIUS OF CURVATURE OF TRACK IT
 *--   HC(IT)          : HELIX PITCH OF TRACK IT
 *--   EC(IT)          : ENERGY OF TRACK IT CALCULATED FROM THE CURVATURE
 *--   QC(IT)          : CHARGE OF TRACK IT CALCULATED FROM THE CURVATURE
 *--   PROB_RADC(IT)   : PROBABILITY OF CIRCLE FIT FOR TRACK IT
 *--                                               IN THE HORIZONTAL PLANE
 *--   PROB_HC(IT)     : PROBABILITY OF LINE FIT FOR TRACK IT
 *--                                               IN THE R*THETA PLANE
 *--   PROB_HELIX(IT)  : PROBABILITY OF THE HELIX FIT FOR TRACK IT
 *--   X_FOIL(IT)      : X COORDINATE OF THE INTERSECTION OF TRACK IT
 *--                                     WITH THE FOIL CYLINDER (FROM TRACKING)
 *--   Y_FOIL(IT)      : Y COORDINATE OF THE INTERSECTION OF TRACK IT
 *--                                     WITH THE FOIL CYLINDER (FROM TRACKING)
 *--   Z_FOIL(IT)      : Z COORDINATE OF THE INTERSECTION OF TRACK IT
 *--                                     WITH THE FOIL CYLINDER (FROM TRACKING)
 *--   COS_DIR(3,IT)   : DIRECTION COSINES OF TRACK IT
 *--                     (FROM TRACKING OR FROM TRACK FIT AND
 *--                                                 INTERSECTION WITH THE FOIL)
 *--   IND_SCINT(IT)   : ISC VALUE OF THE SCINTILLATOR ASSOCIATED TO TRACK IT
 *--   IMPACT(IT)      : IMPACT REGION OF THE TRACK ONTO THE SCINTILLATOR BLOCK
 *--   X_VERT          : X COORDINATE OF THE EVENT VERTEX
 *--   Y_VERT          : Y COORDINATE OF THE EVENT VERTEX
 *--   Z_VERT          : Z COORDINATE OF THE EVENT VERTEX
 **/

#include "Hereward/Edm/EventRecord.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "TBuffer.h"
#include "NemoObjects/TrackHelix.h"
#include <vector>

class N3Track : public TrackHelix {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    N3Track();
    N3Track(const N3Track& obj);
    N3Track& operator = (const N3Track& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~N3Track();
    
    //-------------------------------------------------------------------------
    // Getters 
    //-------------------------------------------------------------------------
    const std::vector<int>*  const geigerHitList()          const;
    
        
    CLHEP::Hep3Vector   intersectionOnFoil()  const;
    CLHEP::Hep3Vector   directionCosine()     const;
    CLHEP::Hep3Vector   intersectionOnCalo()                const;
    int                 indexOfScintillator()               const;
    int                 calorimeterBlockId()                const;
    int                 impactRegion()                      const;
    bool                corruptedCalo()       const;
    bool                corruptedGeiger()     const;

    //-------------------------------------------------------------------------
    // Setters 
    //-------------------------------------------------------------------------
    void setGeigerHitList(const std::vector<int> aValue);
    
    void setIntersectionOnFoil(const CLHEP::Hep3Vector aValue);
    void setIntersectionOnFoil(const double x, const double y, const double z);
    void setDirectionCosine(const CLHEP::Hep3Vector aValue);

    void setIntersectionOnCalo(const CLHEP::Hep3Vector aValue);
    void setIndexOfScintillator(const int aValue);
    void setImpactRegion(const int aValue);

    void setCorruptedCaloFlag(const bool aValue);
    void setCorruptedGeigerFlag(const bool aValue);
    
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
    std::vector<int>    geigerHitList_;
    
    CLHEP::Hep3Vector   intersectionOnFoil_;
    CLHEP::Hep3Vector   directionCosine_;    
    CLHEP::Hep3Vector   intersectionOnCalo_;
    int                 indexOfScintillator_;
    int                 impactRegion_;
    bool                corruptedCalo_;
    bool                corruptedGeiger_;

    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const N3Track& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------

inline const std::vector<int>*  const   N3Track::geigerHitList() const {
    return &geigerHitList_;
}

inline CLHEP::Hep3Vector N3Track::intersectionOnFoil() const {
    return intersectionOnFoil_;
}

inline CLHEP::Hep3Vector N3Track::directionCosine() const {
    return directionCosine_;
}

inline CLHEP::Hep3Vector N3Track::intersectionOnCalo() const {
    return intersectionOnCalo_;
}

inline int      N3Track::indexOfScintillator() const {
    return indexOfScintillator_;
}

inline int      N3Track::calorimeterBlockId() const {
    return indexOfScintillator_;
}

inline int   N3Track::impactRegion() const {
    return impactRegion_;
}

inline void N3Track::setGeigerHitList(const std::vector<int> aValue) {
    geigerHitList_ = aValue;
}

inline void N3Track::setIntersectionOnFoil(CLHEP::Hep3Vector aValue) {
    intersectionOnFoil_ = aValue;
}

inline void N3Track::
setIntersectionOnFoil(const double x, const double y, const double z) {
    intersectionOnFoil_ = CLHEP::Hep3Vector(x,y,z);
}

inline void N3Track::setDirectionCosine(const CLHEP::Hep3Vector aValue) {
    directionCosine_ = aValue;
}

inline void N3Track::setIntersectionOnCalo(const CLHEP::Hep3Vector aValue) {
    intersectionOnCalo_ = aValue;
}

inline void N3Track::setIndexOfScintillator(const int aValue) {
    indexOfScintillator_ = aValue;
}

inline void N3Track::setImpactRegion(const int aValue) {
    impactRegion_ = aValue;
}

inline void N3Track::setCorruptedGeigerFlag(const bool aValue) {
  corruptedGeiger_ = aValue;
}

inline bool N3Track::corruptedGeiger() const {
  return corruptedGeiger_;
}

inline void N3Track::setCorruptedCaloFlag(const bool aValue) {
  corruptedCalo_ = aValue;
}

inline bool N3Track::corruptedCalo() const {
  return corruptedCalo_;
}


#endif

#endif
