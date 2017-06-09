//
//  N3TrackSegment.h
//
//  Created by Stefano Torre on 15/02/12.
//

#ifndef NEMO_N3TRACKSEGMENT_H_
#define NEMO_N3TRACKSEGMENT_H_

#include "Hereward/Edm/EventRecord.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "TBuffer.h"
#include "NemoObjects/TrackHelix.h"
#include <vector>

class N3TrackSegment {
 public:
  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
  N3TrackSegment();
  N3TrackSegment(const N3TrackSegment& obj);
  N3TrackSegment& operator = (const N3TrackSegment& obj);
    
  //-------------------------------------------------------------------------
  // Destructors
  //-------------------------------------------------------------------------
  virtual ~N3TrackSegment();
    
  //-------------------------------------------------------------------------
  // Getters 
  //-------------------------------------------------------------------------
  int                     algorithm()             const {return algorithm_; }
  const std::vector<int>* const geigerHitList()   const;
  const TrackHelix*       const globalFit()       const;
  const TrackHelix*       const localFoilFit()    const;
  const TrackHelix*       const localCaloFit()    const;

  CLHEP::Hep3Vector       intersectionOnFoil(bool lcoal_fit = false) const;
  // bkwd compatibility:
  // 0 - global
  // 1 - foil
  // 2 - scintillator
  CLHEP::Hep3Vector       directionCosine(int fit_id = 0)    const;
  bool                    isAssociatedToFoil() const {return isAssociatedToFoil_;}
  CLHEP::Hep3Vector       foilCenter()         const;
    
  CLHEP::Hep3Vector       intersectionOnScint(bool lcoal_fit = false)const;
  int                     indexOfScintillator()const {return indexOfScintillator_;}
  int                     impactRegion()       const {return impactRegion_; }
  double                  distanceAlongTrack(CLHEP::Hep3Vector start,
					     CLHEP::Hep3Vector stop) const {
    return globalFit_.distanceAlongTrack(start, stop);
  }
  double sign() const {return globalFit_.sign(); }
    
  //-------------------------------------------------------------------------
  // Setters 
  //-------------------------------------------------------------------------
  void setAlgorithm(const int aValue)                 { algorithm_ = aValue; }
  void setGeigerHitList(const std::vector<int> aValue);
  void setGlobalFit(const TrackHelix aValue);
  void setLocalFoilFit(const TrackHelix aValue);
  void setLocalCaloFit(const TrackHelix aValue);
    
  void setIntersectionOnFoil(const CLHEP::Hep3Vector aValue); // bkwd compatibility
  void setIntersectionOnFoil_global(const CLHEP::Hep3Vector aValue);
  void setIntersectionOnFoil_foil(const CLHEP::Hep3Vector aValue);
  void setDirectionCosine(const CLHEP::Hep3Vector aValue); // bkwd compatibility
  void setDirectionCosine_global(const CLHEP::Hep3Vector aValue);
  void setDirectionCosine_foil(const CLHEP::Hep3Vector aValue);
  void setDirectionCosine_scint(const CLHEP::Hep3Vector aValue);
  void setIsAssociatedToFoil(bool aValue);
  void setFoilCenter(const CLHEP::Hep3Vector aValue);
    
  void setIntersectionOnScint(const CLHEP::Hep3Vector aValue); // bkwn compatibility
  void setIntersectionOnScint_global(const CLHEP::Hep3Vector aValue);
  void setIntersectionOnScint_scint(const CLHEP::Hep3Vector aValue);
  void setIndexOfScintillator(const int aValue);
  void setImpactRegion(const int aValue);

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
  // algorithms:
  // 0 - with ghost hits and cluster fit
  // 1 - w/out ghost hits and cluster fit
  // 2 - with ghost hits and single hit fit
  // 3 - w/out ghost hits and single hit fit
  int                algorithm_;
  std::vector<int>   geigerHitList_;
  TrackHelix         globalFit_;
  TrackHelix         localFoilFit_;
  TrackHelix         localCaloFit_;
    
  // information @ foil
  CLHEP::Hep3Vector  intersectionOnFoil_global_;
  CLHEP::Hep3Vector  intersectionOnFoil_foil_;
  CLHEP::Hep3Vector  directionCosine_global_;
  CLHEP::Hep3Vector  directionCosine_foil_;
  CLHEP::Hep3Vector  directionCosine_scint_;
  bool               isAssociatedToFoil_;
  CLHEP::Hep3Vector  foilCenter_;
    
  // information @ scint
  CLHEP::Hep3Vector  intersectionOnScint_global_;
  CLHEP::Hep3Vector  intersectionOnScint_scint_;
  int                indexOfScintillator_;
  int                impactRegion_;

  static const Version_t version_ = 1;
  Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const N3TrackSegment& obj);

#ifndef __CINT__
//-------------------------------------------------------------------------
// Getters and Setters
//-------------------------------------------------------------------------
inline const std::vector<int>* const N3TrackSegment::geigerHitList() const {
  return &geigerHitList_;
}

inline const TrackHelix*   const N3TrackSegment::globalFit() const {
  return &globalFit_;
}

inline const TrackHelix*   const N3TrackSegment::localFoilFit() const {
  return &localFoilFit_;
}
inline const TrackHelix*   const N3TrackSegment::localCaloFit() const {
  return &localCaloFit_;
}

inline CLHEP::Hep3Vector N3TrackSegment::intersectionOnFoil(bool local_fit) const {
  if (local_fit) 
    return intersectionOnFoil_foil_;
  else
    return intersectionOnFoil_global_;
}

inline CLHEP::Hep3Vector N3TrackSegment::directionCosine(int fit_id) const {
  switch (fit_id) {
  case 0:
    return directionCosine_global_;
    break;
  case 1:
    return directionCosine_foil_;
    break;
  case 2:
    return directionCosine_scint_;
    break;
  }
}

inline CLHEP::Hep3Vector N3TrackSegment::foilCenter() const {
  return foilCenter_;
}

inline CLHEP::Hep3Vector N3TrackSegment::intersectionOnScint(bool local_fit) const {
  if (local_fit)
    return intersectionOnScint_scint_;
  else
    return intersectionOnScint_global_;
}

inline void N3TrackSegment::setGeigerHitList(const std::vector<int> aValue) {
  geigerHitList_ = aValue;
}

inline void N3TrackSegment::setGlobalFit(const TrackHelix aValue) {
  globalFit_ = aValue;
}

inline void N3TrackSegment::setLocalFoilFit(const TrackHelix aValue) {
  localFoilFit_ = aValue;
}

inline void N3TrackSegment::setLocalCaloFit(const TrackHelix aValue) {
  localCaloFit_ = aValue;
}

inline void N3TrackSegment::setIntersectionOnFoil(const CLHEP::Hep3Vector aValue) {
  setIntersectionOnFoil_global(aValue);
}

inline void N3TrackSegment::setIntersectionOnFoil_global(const CLHEP::Hep3Vector aValue) {
  intersectionOnFoil_global_ = aValue;
}

inline void N3TrackSegment::setIntersectionOnFoil_foil(const CLHEP::Hep3Vector aValue) {
  intersectionOnFoil_foil_ = aValue;
}

inline void N3TrackSegment::setDirectionCosine(CLHEP::Hep3Vector aValue) {
  setDirectionCosine_global(aValue);
}

inline void N3TrackSegment::setDirectionCosine_global(CLHEP::Hep3Vector aValue) {
  directionCosine_global_ = aValue;
}

inline void N3TrackSegment::setDirectionCosine_foil(CLHEP::Hep3Vector aValue) {
  directionCosine_foil_ = aValue;
}

inline void N3TrackSegment::setDirectionCosine_scint(CLHEP::Hep3Vector aValue) {
  directionCosine_scint_ = aValue;
}

inline void N3TrackSegment::setIsAssociatedToFoil(bool aValue) {
  isAssociatedToFoil_ = aValue;
}

inline void N3TrackSegment::setFoilCenter(const CLHEP::Hep3Vector aValue) {
  foilCenter_ = aValue;
}

inline void N3TrackSegment::setIntersectionOnScint(const CLHEP::Hep3Vector aValue) {
  setIntersectionOnScint_global(aValue);
}

inline void N3TrackSegment::setIntersectionOnScint_global(const CLHEP::Hep3Vector aValue) {
  intersectionOnScint_global_ = aValue;
}

inline void N3TrackSegment::setIntersectionOnScint_scint(const CLHEP::Hep3Vector aValue) {
  intersectionOnScint_scint_ = aValue;
}

inline void N3TrackSegment::setIndexOfScintillator(const int aValue) {
  indexOfScintillator_ = aValue;
}

inline void N3TrackSegment::setImpactRegion(const int aValue) {
  impactRegion_ = aValue;
}

#endif 


#endif
