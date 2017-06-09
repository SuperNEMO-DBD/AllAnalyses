/*
 * Class        : Alpha
 * Description  : Definition of the object containing calorimeter information
 *                with all calibration and corrections applied to it
 *
 *  Created by Stefano Torre on 09/05/2012.
 */

#ifndef NEMO_ALPHA_H_
#define NEMO_ALPHA_H_

#include "Hereward/Edm/EventRecord.h"
#include "Hereward/SuperNemoProcessing/Constants.h"
#include "TBuffer.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "NemoObjects/N3CalorimeterHit.h"
#include "NemoObjects/TrackHelix.h"

class Alpha {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    Alpha();
    Alpha(const Alpha& obj);
    Alpha& operator = (const Alpha& obj);
    Alpha(const N3CalorimeterHit& obj);
    
    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~Alpha();
    
    //-------------------------------------------------------------------------
    // Getters and Setters
    //-------------------------------------------------------------------------
    const std::vector<int>*  const geigerHitList()          const;
    void   setGeigerHitList(const std::vector<int> aValue);

    int    trackId() const;
    void   setTrackId(const int aValue);

    int    nDelayedHits() const;
    void   setNDelayedHits(const int aValue);

    double time() const;
    void   setTime(const double aValue);

    int    side() const;
    void   setSide(const int aValue);

    int    lowestLayer() const;
    void   setLowestLayer(const int aValue);

    double maxDelayedTimeDiff() const;
    void   setMaxDelayedTimeDiff(const double aValue);

    bool   nearFoil() const;
    void   setNearFoil(const bool aValue);

    int    foilClosestHitId() const;
    void   setFoilClosestHitId(const int aValue);

    int    foilFurthestHitId() const;
    void   setFoilFurthestHitId(const int aValue);

    CLHEP::Hep3Vector foilClosestHitVector() const;
    void   setFoilClosestHitVector(const CLHEP::Hep3Vector aValue);

    CLHEP::Hep3Vector foilFurthestHitVector() const;
    void   setFoilFurthestHitVector(const CLHEP::Hep3Vector aValue);

    bool   nearWire() const;
    void   setNearWire(const bool aValue);

    int    wireClosestHitId() const;
    void   setWireClosestHitId(const int aValue);

    int    wireFurthestHitId() const;
    void   setWireFurthestHitId(const int aValue);

    CLHEP::Hep3Vector wireClosestHitVector() const;
    void   setWireClosestHitVector(const CLHEP::Hep3Vector aValue);

    CLHEP::Hep3Vector wireFurthestHitVector() const;
    void   setWireFurthestHitVector(const CLHEP::Hep3Vector aValue);

    CLHEP::Hep3Vector foilVertex() const;
    void   setFoilVertex(const CLHEP::Hep3Vector aValue);

    CLHEP::Hep3Vector trackVector() const;
    void   setTrackVector(const CLHEP::Hep3Vector aValue);

    bool intersectTheFoil() const;

    double lengthFromFoil() const;

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
    // Raw cluster information
    std::vector<int>    geigerHitList_;
    int    trackId_;
    int    nDelayedHits_;
    double time_;
    int    side_;
    int    lowestLayer_;
    double maxDelayedTimeDiff_;

    // Cluster info w.r.t. track
    bool   nearFoil_;
    int    foilClosestHitId_;
    int    foilFurthestHitId_;
    CLHEP::Hep3Vector foilClosestHitVector_;
    CLHEP::Hep3Vector foilFurthestHitVector_;
    bool   nearWire_;
    int    wireClosestHitId_;
    int    wireFurthestHitId_;
    CLHEP::Hep3Vector wireClosestHitVector_;
    CLHEP::Hep3Vector wireFurthestHitVector_;

    // Parameters from fitting straight line to cluster
    CLHEP::Hep3Vector foilVertex_;
    CLHEP::Hep3Vector trackVector_;

    static const Version_t version_ = 1;
    Version_t versionRead_;
};


//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const Alpha& obj);

#ifndef __CINT__

inline const std::vector<int>*  const Alpha::geigerHitList() const { return &geigerHitList_; }
inline void Alpha::setGeigerHitList(const std::vector<int> aValue) { geigerHitList_ = aValue;}

inline int    Alpha::trackId() const { return trackId_; }
inline void   Alpha::setTrackId(const int aValue) { trackId_ = aValue; }

inline int    Alpha::nDelayedHits() const { return nDelayedHits_; }
inline void   Alpha::setNDelayedHits(const int aValue) { nDelayedHits_ = aValue; }

inline double Alpha::time() const { return time_; }
inline void   Alpha::setTime(const double aValue) { time_ = aValue; }

inline int    Alpha::side() const { return side_; }
inline void   Alpha::setSide(const int aValue) { side_ = aValue; }

inline int    Alpha::lowestLayer() const { return lowestLayer_; }
inline void   Alpha::setLowestLayer(const int aValue) { lowestLayer_ = aValue; }

inline double Alpha::maxDelayedTimeDiff() const { return maxDelayedTimeDiff_; }
inline void   Alpha::setMaxDelayedTimeDiff(const double aValue) { maxDelayedTimeDiff_ = aValue; }

inline bool   Alpha::nearFoil() const { return nearFoil_; }
inline void   Alpha::setNearFoil(const bool aValue) { nearFoil_ = aValue; }

inline int    Alpha::foilClosestHitId() const { return foilClosestHitId_; }
inline void   Alpha::setFoilClosestHitId(const int aValue) { foilClosestHitId_ = aValue; }

inline int    Alpha::foilFurthestHitId() const { return foilFurthestHitId_; }
inline void   Alpha::setFoilFurthestHitId(const int aValue) { foilFurthestHitId_ = aValue; }

inline CLHEP::Hep3Vector Alpha::foilClosestHitVector() const { return foilClosestHitVector_; }
inline void Alpha::setFoilClosestHitVector(const CLHEP::Hep3Vector aValue) { foilClosestHitVector_ = aValue;}

inline CLHEP::Hep3Vector Alpha::foilFurthestHitVector() const { return foilFurthestHitVector_; }
inline void Alpha::setFoilFurthestHitVector(const CLHEP::Hep3Vector aValue) { foilFurthestHitVector_ = aValue;}

inline bool   Alpha::nearWire() const { return nearWire_; }
inline void   Alpha::setNearWire(const bool aValue) { nearWire_ = aValue; }

inline int    Alpha::wireClosestHitId() const { return wireClosestHitId_; }
inline void   Alpha::setWireClosestHitId(const int aValue) { wireClosestHitId_ = aValue; }

inline int    Alpha::wireFurthestHitId() const { return wireFurthestHitId_; }
inline void   Alpha::setWireFurthestHitId(const int aValue) { wireFurthestHitId_ = aValue; }

inline CLHEP::Hep3Vector Alpha::wireClosestHitVector() const { return wireClosestHitVector_; }
inline void Alpha::setWireClosestHitVector(const CLHEP::Hep3Vector aValue) { wireClosestHitVector_ = aValue;}

inline CLHEP::Hep3Vector Alpha::wireFurthestHitVector() const { return wireFurthestHitVector_; }
inline void Alpha::setWireFurthestHitVector(const CLHEP::Hep3Vector aValue) { wireFurthestHitVector_ = aValue;}

inline CLHEP::Hep3Vector Alpha::foilVertex() const { return foilVertex_; }
inline void Alpha::setFoilVertex(const CLHEP::Hep3Vector aValue) { foilVertex_ = aValue;}

inline CLHEP::Hep3Vector Alpha::trackVector() const { return trackVector_; }
inline void Alpha::setTrackVector(const CLHEP::Hep3Vector aValue) { trackVector_ = aValue;}

#endif

#endif
